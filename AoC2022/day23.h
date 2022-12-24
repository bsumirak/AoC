/*
 * day23.h
 *
 *  Created on: 2022-12-23
 *      Author: mbreit
 */


template <>
void executeDay<23>(const std::string& fn)
{
	// read input
	const unsigned inputDim = 70;
	const unsigned maxRounds = 2000;
	const unsigned sz = 2 * maxRounds + inputDim;
	unsigned cnt = 0;
	unsigned numElves = 0;
	std::vector<unsigned> map(sz * sz, 5u);
	{
		std::ifstream infile(fn.c_str());
		char c;
		while (infile >> c)
		{
			if (c == '#')
			{
				map[(cnt / inputDim + maxRounds) * sz + (cnt % inputDim) + maxRounds] = 0u;
				++numElves;
			}
			++cnt;
		}
		infile.close();
	}


	unsigned resA = 0;
	unsigned resB = 0;
	for (unsigned r = 0; r < maxRounds; ++r)
	{
		for (unsigned k = 0; k < sz*sz; ++k)
		{
			if (map[k] >= 5u)
				continue;

			if (map[k - sz - 1] >= 5u && map[k - sz] >= 5u && map[k - sz + 1] >= 5u
				&& map[k - 1] >= 5u && map[k + 1] >= 5u
				&& map[k + sz - 1] >= 5u && map[k + sz] >= 5u && map[k + sz + 1] >= 5u)
			{
				map[k] = 4u;
				continue;
			}

			for (unsigned d = 0; d < 4u; ++d)
			{
				if ((r + d) % 4u == 0)
				{
					if (map[k - sz - 1] >= 5u && map[k - sz] >= 5u && map[k - sz + 1] >= 5u)
					{
						map[k] = 0u;
						++map[k - sz];
						break;
					}
				}

				else if ((r + d) % 4u == 1)
				{
					if (map[k + sz + 1] >= 5u && map[k + sz] >= 5u && map[k + sz - 1] >= 5u)
					{
						map[k] = 1u;
						++map[k + sz];
						break;
					}
				}
				else if ((r + d) % 4u == 2)
				{
					if (map[k - sz - 1] >= 5u && map[k - 1] >= 5u && map[k + sz - 1] >= 5u)
					{
						map[k] = 2u;
						++map[k - 1];
						break;
					}
				}
				else if ((r + d) % 4u == 3)
				{
					if (map[k - sz + 1] >= 5u && map[k + 1] >= 5u && map[k + sz + 1] >= 5u)
					{
						map[k] = 3u;
						++map[k + 1];
						break;
					}
				}
			}
		}

		bool oneMoves = false;
		for (unsigned k = 0; k < sz*sz; ++k)
		{
			if (map[k] >= 5u)
				continue;

			unsigned choice = map[k];
			if (choice == 0)
			{
				if (map[k - sz] == 6u)
				{
					map[k - sz] = 10u;
					map[k] = 5u;
					oneMoves = true;
				}
			}
			else if (choice == 1)
			{
				if (map[k + sz] == 6u)
				{
					map[k + sz] = 10u;
					map[k] = 5u;
					oneMoves = true;
				}
			}
			else if (choice == 2)
			{
				if (map[k - 1] == 6u)
				{
					map[k - 1] = 10u;
					map[k] = 5u;
					oneMoves = true;
				}
			}
			else if (choice == 3)
			{
				if (map[k + 1] == 6u)
				{
					map[k + 1] = 10u;
					map[k] = 5u;
					oneMoves = true;
				}
			}
		}

		for (unsigned k = 0; k < sz*sz; ++k)
		{
			if (map[k] >= 5u && map[k] <= 9u)
				map[k] = 5u;
			else if (map[k] == 10u)
				map[k] = 0;
		}

		/*
		for (unsigned y = 0; y < 26; ++y)
		{
			for (unsigned x = 0; x < 26; ++x)
				std::cout << (map[sz * y + x] < 5u ? '#' : '.');
			std::cout << std::endl;
		}
		std::cout << std::endl;
		*/

		if (r == 9)
		{
			unsigned minX = sz;
			unsigned maxX = 0;
			unsigned minY = sz;
			unsigned maxY= 0;
			for (unsigned k = 0; k < sz*sz; ++k)
			{
				if (map[k] == 5u)
					continue;

				unsigned x = k % sz;
				unsigned y = k / sz;

				minX = std::min(minX, x);
				maxX = std::max(maxX, x);
				minY = std::min(minY, y);
				maxY = std::max(maxY, y);
			}
			resA = (maxX - minX + 1u) * (maxY - minY + 1) - numElves;
		}

		if (!oneMoves)
		{
			resB = r + 1;
			break;
		}
	}


	writeSolution(resA, resB);
}


