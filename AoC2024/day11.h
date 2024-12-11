/*
 * day11.h
 *
 *  Created on: 2024-12-11
 *      Author: mbreit
 */

template <>
void executeDay<11>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::map<uint64_t, uint64_t> map;

	uint64_t u;
	while (infile >> u)
		map[u] = 1u;

	const auto updateMap = [](std::map<uint64_t, uint64_t>& map)
	{
		std::map<uint64_t, uint64_t> map2;
		for (auto& [v, w] : map)
		{
			if (v == 0u)
			{
				map2[1u] += w;
				continue;
			}
			const auto digits = (unsigned)std::ceil(std::log10(v + 1));
			if (digits % 2u == 0u)
			{
				const unsigned div = std::pow(10u, digits / 2u);
				map2[v / div] += w;
				map2[v % div] += w;
				continue;
			}
			map2[v * 2024u] += w;
		}
		map.swap(map2);
	};

	// part a
	for (unsigned k = 0; k < 25u; ++k)
		updateMap(map);
	uint64_t resA = 0u;
	for (auto& [v, w] : map)
		resA += w;

	// part b
	for (unsigned k = 25; k < 75u; ++k)
		updateMap(map);
	uint64_t resB = 0u;
	for (auto& [v, w] : map)
		resB += w;


	writeSolution(resA, resB);
}

