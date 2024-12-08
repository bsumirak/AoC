/*
 * day08.h
 *
 *  Created on: 2024-12-08
 *      Author: mbreit
 */

template <>
void executeDay<8>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::vector<std::string> map;
	
	std::string line;
	while (std::getline(infile, line))
		map.push_back(line);
	const unsigned nr = map.size();
	const unsigned nc = map[0].size();

	std::map<char, std::vector<unsigned>> ant;
	for (size_t r = 0; r < nr; ++r)
	{
		for (size_t c = 0; c < nc; ++c)
		{
			if (map[r][c] != '.')
				ant[map[r][c]].push_back(r * nc + c);
		}
	}

	std::set<unsigned> ana;
	std::set<unsigned> anb;
	for (auto& as : ant)
	{
		const size_t num = as.second.size();
		for (size_t a1 = 0; a1 < num; ++a1)
		{
			auto r1 = as.second[a1] / nc;
			auto c1 = as.second[a1] % nc;
			for (size_t a2 = a1 + 1u; a2 < num; ++a2)
			{
				auto r2 = as.second[a2] / nc;
				auto c2 = as.second[a2] % nc;

				auto rd = (int)r2 - (int)r1;
				auto cd = (int)c2 - (int)c1;

				// part a
				if (r2 + rd < nr && c2 + cd < nc)
					ana.insert((r2 + rd) * nc + c2 + cd);
				if (r1 - rd < nr && c1 - cd < nc)
					ana.insert((r1 - rd) * nc + c1 - cd);

				// part b
				for (unsigned k = 0u; r2 + k*rd < nr && c2 + k*cd < nc; ++k)
					anb.insert((r2 + k*rd) * nc + c2 + k*cd);
				for (unsigned k = 0u; r1 - k*rd < nr && c1 - k*cd < nc; ++k)
					anb.insert((r1 - k*rd) * nc + c1 - k*cd);
			}
		}
	}

	const auto resA = ana.size();
	const auto resB = anb.size();

	writeSolution(resA, resB);
}


