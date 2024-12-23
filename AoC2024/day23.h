/*
 * day23.h
 *
 *  Created on: 2024-12-23
 *      Author: mbreit
 */


void recurse23b(const std::array<std::vector<unsigned>, 26u*26u>& lan, std::set<unsigned>& clique,
	const std::vector<unsigned>& cands, size_t pos, std::set<unsigned>& maxClique)
{
	for (size_t k = pos; k < cands.size(); ++k)
	{
		auto cand = cands[k];
		bool allConn = true;
		for (auto mem : clique)
		{
			if (std::find(lan[cand].begin(), lan[cand].end(), mem) == lan[cand].end())
			{
				allConn = false;
				break;
			}
		}
		if (!allConn)
			continue;

		clique.insert(cand);
		recurse23b(lan, clique, cands, pos + 1u, maxClique);
		clique.erase(cand);
	}

	if (clique.size() > maxClique.size())
		maxClique = clique;
}


template <>
void executeDay<23>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::array<std::vector<unsigned>, 26u*26u> lan;

	std::string line;
	while (std::getline(infile, line))
	{
		std::regex re("([a-z]*)-([a-z]*)");
		std::smatch match;
		if (!std::regex_match(line, match, re))
			std::cout << "no match" << std::endl;

		const auto m1 = match.str(1);
		const auto m2 = match.str(2);

		lan[(m1[0] - 'a') * 26u + m1[1] - 'a'].push_back((m2[0] - 'a') * 26u + m2[1] - 'a');
		lan[(m2[0] - 'a') * 26u + m2[1] - 'a'].push_back((m1[0] - 'a') * 26u + m1[1] - 'a');
	}

	// part a
	uint64_t resA = 0u;
	for (unsigned k = 19u*26u; k < 20u*26u; ++k)
	{
		for (auto c : lan[k])
		{
			if (c == k || (c >= 19u*26u && c < k))
				continue;

			for (auto c1 : lan[c])
			{
				if (c1 == k || c1 <= c || (c1 >= 19u*26u && (c1 < k || (c >= 19u*26u && c < 20u * 26u && c1 < c))))
					continue;

				const auto it = std::find(lan[c1].begin(), lan[c1].end(), k);
				if (it != lan[c1].end())
					++resA;
			}
		}
	}

	// part b
	std::set<unsigned> maxClique;
	for (unsigned k = 0u; k < 26u*26u; ++k)
	{
		std::set<unsigned> clique = {k};
		recurse23b(lan, clique, lan[k], 0u, maxClique);
	}

	std::string resB = "";
	for (auto mem : maxClique)
		resB += std::string(1, 'a' + mem / 26u) + std::string(1, 'a' + mem % 26u) + ",";
	resB.resize(resB.size() - 1u);


	writeSolution(resA, resB);
}

