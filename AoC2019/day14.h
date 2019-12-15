/*
 * day14.h
 *
 *  Created on: 14.12.2017
 *      Author: mbreit
 */

struct Reaction
{
	std::vector<std::string> name;
	std::vector<int64_t> quantity;
};


struct Educt
{
	Educt (std::string n, int64_t q) :
		name(n), quantity(q) {};

	std::string name;
	int64_t quantity;
};


int64_t requiredOre
(
	int64_t fuel,
	const std::map<std::string, Reaction>& reactionMap,
	const std::map<std::string, std::set<std::string> >& _edOf
)
{
	std::map<std::string, std::set<std::string> > edOf(_edOf);

	std::map<std::string, int64_t> reqAmount;
	auto it = reactionMap.begin();
	auto itEnd = reactionMap.end();
	for (; it != itEnd; ++it)
		reqAmount[it->first] = 0;

	reqAmount["FUEL"] = fuel;

	while (true)
	{
		auto ite = edOf.begin();
		while (ite != edOf.end() && (ite->second.size() || !reqAmount[ite->first]))
			++ite;

		if (ite == edOf.end())
			break;

		const std::string& prod = ite->first;

		if (prod == "ORE")
			break;

		//std::cout << "required amout of " << prod << ": " << reqAmount[prod] << std::endl;
		auto itr = reactionMap.find(prod);
		int64_t amount = reqAmount[prod] / itr->second.quantity.back();
		if (reqAmount[prod] % itr->second.quantity.back())
			++amount;

		//std::cout << "amount: " << reqAmount[prod] << " " << itr->second.quantity.back() << std::endl;

		for (std::size_t i = 0; i < itr->second.name.size() - 1; ++i)
			reqAmount[itr->second.name[i]] += amount * itr->second.quantity[i];

		reqAmount[prod] = 0;

		ite = edOf.begin();
		auto iteEnd = edOf.end();
		for (; ite != iteEnd; ++ite)
		{
			auto itp = ite->second.find(prod);
			if (itp != ite->second.end())
				ite->second.erase(itp);
		}
	}

	return reqAmount["ORE"];
}



template <>
void executeDay<14>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::string line;
	std::map<std::string, Reaction> reactionMap;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		Reaction ed;
		int tmp;
		while (iss >> tmp)
		{
			ed.name.resize(ed.name.size() + 1);
			ed.quantity.resize(ed.quantity.size() + 1);
			ed.quantity.back() = tmp;
			iss >> ed.name.back();
		}
		if (reactionMap.find(ed.name.back()) != reactionMap.end())
		{
			std::cout << "bflkgj" << std::endl;
			throw std::runtime_error("");
		}
		reactionMap[ed.name.back()] = ed;
	}

	// build depender list
	std::map<std::string, std::set<std::string> > edOf;
	auto it = reactionMap.begin();
	auto itEnd = reactionMap.end();
	for (; it != itEnd; ++it)
	{
		const std::vector<std::string>& eds = it->second.name;
		const std::size_t nEds = eds.size() - 1;
		for (std::size_t e = 0; e < nEds; ++e)
			edOf[eds[e]].insert(it->first);
	}
	edOf["FUEL"];


	// part a
	int64_t sola = requiredOre(1, reactionMap, edOf);


	// part b
	int64_t ore(1000000000000);
	int64_t prop = ore / int64_t(sola);
	int64_t guess = prop;
	while (requiredOre(guess, reactionMap, edOf) <= ore)
		guess += prop;

	// in no mood to implement the bisection myself :)
	std::vector<int64_t> check(prop+1);
	for (std::size_t i = 0; i < (std::size_t) prop+1; ++i)
		check[i] = guess - prop + i;

	auto cmpFct = [&] (const int64_t& fuelA, const int64_t& fuelB) -> bool
	{
		// little hack :)
		if (fuelA == ore)
			return fuelA < requiredOre(fuelB, reactionMap, edOf);
		if (fuelB == ore)
			return requiredOre(fuelA, reactionMap, edOf) < fuelB;
		return requiredOre(fuelA, reactionMap, edOf) < requiredOre(fuelB, reactionMap, edOf);
	};

	auto solb = std::upper_bound(check.begin(), check.end(), ore, cmpFct);


	writeSolution(sola, *solb-1);
}


