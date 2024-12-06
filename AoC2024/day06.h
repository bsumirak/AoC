/*
 * day06.h
 *
 *  Created on: 2024-12-06
 *      Author: mbreit
 */

template <>
void executeDay<6>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::vector<std::string> map;
	std::string line;
	while (std::getline(infile, line))
		map.push_back(line);
	const auto nr = map.size();
	const auto nc = map[0].size();

	// find start position
	size_t gr = nr;
	size_t gc = nc;
	for (size_t r = 0; r < nr; ++r)
	{
		for (size_t c = 0; c < nc; ++c)
		{
			if (map[r][c] == '^')
			{
				gr = r;
				gc = c;
				map[r][c] = '0';
				break;
			}
		}
		if (gr != nr)
			break;
	}


	const auto walk = [nr, nc](std::vector<std::string>& map, size_t gr, size_t gc)
	{
		unsigned numPassed = 1u;
		unsigned gd = 0u;

		while (!((gr == 0 && gd == 0) || (gr == nr - 1 && gd == 2)
			|| (gc == 0 && gd == 3) || (gc == nc - 1 && gd == 1)))
		{
			switch (gd)
			{
				case 0:
				{
					auto& c = map[gr - 1][gc];
					if (c == '#')
					{
						gd = 1;
						continue;
					}
					if (c == '.')
						++numPassed;
					if (c == '0' + (char)gd)
						return 0u;
					c = '0' + (char)gd;
					--gr;
					break;
				}
				case 1:
				{
					auto& c = map[gr][gc + 1];
					if (c == '#')
					{
						gd = 2;
						continue;
					}
					if (c == '.')
						++numPassed;
					if (c == '0' + (char)gd)
						return 0u;
					c = '0' + (char)gd;
					++gc;
					break;
				}
				case 2:
				{
					auto& c = map[gr + 1][gc];
					if (c == '#')
					{
						gd = 3;
						continue;
					}
					if (c == '.')
						++numPassed;
					if (c == '0' + (char)gd)
						return 0u;
					c = '0' + (char)gd;
					++gr;
					break;
				}
				case 3:
				{
					auto& c = map[gr][gc - 1];
					if (c == '#')
					{
						gd = 0;
						continue;
					}
					if (c == '.')
						++numPassed;
					if (c == '0' + (char)gd)
						return 0u;
					c = '0' + (char)gd;
					--gc;
					break;
				}
			}
		}

		return numPassed;
	};

	// part a
	auto mapCpyA = map;
	const auto resA = walk(mapCpyA, gr, gc);

	// part b
	unsigned resB = 0u;
	auto mapCpyB = map;
	for (size_t r = 0; r < nr; ++r)
	{
		for (size_t c = 0; c < nc; ++c)
		{
			if (mapCpyA[r][c] == '.' || mapCpyA[r][c] == '#' || (r == gr && c == gc))
				continue;

			mapCpyB = map;
			mapCpyB[r][c] = '#';
			if (walk(mapCpyB, gr, gc) == 0u)
				++resB;
		}
	}


	writeSolution(resA, resB);
}

