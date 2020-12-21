/*
 * day21.h
 *
 *  Created on: 2020-12-21
 *      Author: mbreit
 */


template <>
void executeDay<21>(const std::string& fn)
{
	// read input
	struct Data
	{
		std::vector<std::string> ingr;
		std::vector<std::string> allg;
	};
	std::set<std::string> ingr;
	std::set<std::string> allg;
	std::vector<Data> data;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		while (std::getline(infile, line))
		{
			std::istringstream iss(line);
			data.resize(data.size() + 1);
			Data& d = data.back();

			std::string s;
			std::vector<std::string>* v = &d.ingr;
			std::set<std::string>* w = &ingr;
			while (iss >> s)
			{
				if (s == "contains")
				{
					v = &d.allg;
					w = &allg;
					iss >> s;
				}
				v->push_back(s);
				w->insert(s);
			}
		}
		infile.close();
	}



	std::vector<std::string> safe;
	std::map<std::string, std::set<std::string> > danger;
	std::size_t resA = 0;
	for (const std::string& i : ingr)
	{
		std::set<std::string> poss = allg;

		for (const Data& d : data)
		{
			if (std::find(d.ingr.begin(), d.ingr.end(), i) != d.ingr.end())
				continue;

			for (const std::string& a : d.allg)
				poss.erase(a);
		}
		if (!poss.size())
			safe.push_back(i);
		else
			danger[i] = poss;
	}


	// part a
	for (const auto& s: safe)
		for (const Data& d : data)
			if (std::find(d.ingr.begin(), d.ingr.end(), s) != d.ingr.end())
				++resA;


	// part b
	bool finished = false;
	while (!finished)
	{
		finished = true;
		for (auto& m : danger)
		{
			if (m.second.size() == 1)
			{
				for (auto& m1 : danger)
				{
					if (m1.first != m.first)
						m1.second.erase(*m.second.begin());
				}
			}
			else
				finished = false;
		}
	}
	std::map<std::string, std::string> reverseMap;
	for (auto& m : danger)
		reverseMap[*m.second.begin()] = m.first;

	std::string resB = "";
	for (auto& s : reverseMap)
		resB.append(s.second).append(",");
	resB = resB.substr(0, resB.size()-1);


	writeSolution(resA, resB);
}


