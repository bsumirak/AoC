/*
 * day11.h
 *
 *  Created on: 2023-12-11
 *      Author: mbreit
 */

template <>
void executeDay<11>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	
	std::vector<std::string> skyMap;
	std::string s;
	while (infile >> s)
		skyMap.emplace_back(std::move(s));


	uint64_t resA = 0;
	uint64_t resB = 0;
	std::vector<size_t> emptyRows;
	std::vector<size_t> emptyCols;
	for (size_t r = 0; r < skyMap.size(); ++r)
	{
		if (std::find(skyMap[r].begin(), skyMap[r].end(), '#') == skyMap[r].end())
			emptyRows.push_back(r);
	}
	for (size_t c = 0; c < skyMap[0].size(); ++c)
	{
		bool hasGalaxy = false;
		for (const auto& row : skyMap)
		{
			if (row[c] == '#')
			{
				hasGalaxy = true;
				break;
			}
		}
		if (!hasGalaxy)
			emptyCols.push_back(c);
	}
	
	for (size_t r = 0; r < skyMap.size(); ++r)
	{
		if (std::find(emptyRows.begin(), emptyRows.end(), r) != emptyRows.end())
			continue;

		auto lbr = std::lower_bound(emptyRows.begin(), emptyRows.end(), r);

		for (size_t c = 0; c < skyMap[0].size(); ++c)
		{
			if (skyMap[r][c] != '#')
				continue;
			
			for (size_t r1 = r; r1 < skyMap.size(); ++r1)
			{
				if (std::find(emptyRows.begin(), emptyRows.end(), r1) != emptyRows.end())
					continue;
					
				for (size_t c1 = r1 == r ? c : 0; c1 < skyMap[0].size(); ++c1)
				{
					if (skyMap[r1][c1] != '#')
						continue;

					resA += r1 - r + abs((int)c - (int)c1);
					resB += r1 - r + abs((int)c - (int)c1);
					
					auto ubr = std::upper_bound(emptyRows.begin(), emptyRows.end(), r1);
					resA += std::distance(lbr, ubr);
					resB += 999999 * std::distance(lbr, ubr);
					
					auto lbc = std::lower_bound(emptyCols.begin(), emptyCols.end(), std::min(c, c1));
					auto ubc = std::lower_bound(emptyCols.begin(), emptyCols.end(), std::max(c, c1));
					resA += std::distance(lbc, ubc);			
					resB += 999999 * std::distance(lbc, ubc);			
				}
			}
		}
	}
	
	writeSolution(resA, resB);
}


