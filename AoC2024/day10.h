/*
 * day10.h
 *
 *  Created on: 2024-12-10
 *      Author: mbreit
 */

template <>
void executeDay<10>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::vector<std::string> map;

	uint64_t resA = 0;
	uint64_t resB = 0;

	std::string line;
	while (std::getline(infile, line))
		map.push_back(line);
	const unsigned nr = map.size();
	const unsigned nc = map[0].size();

	std::vector<unsigned> beenThere(nr*nc, 0u);

	for (size_t r = 0; r < nr; ++r)
	{
		for (size_t c = 0; c < nc; ++c)
		{
			if (map[r][c] != '0')
				continue;

			const auto code = r * nc + c;
			std::queue<std::array<size_t, 2>>q;
			q.push({r, c});
			while(!q.empty())
			{
				auto pos = q.front();
				q.pop();

				if (map[pos[0]][pos[1]] == '9')
				{
					if (beenThere[pos[0]*nc + pos[1]] != code)
					{
						++resA;
						beenThere[pos[0]*nc + pos[1]] = code;
					}
					++resB;
					continue;
				}

				const auto curr = map[pos[0]][pos[1]] - '0';
				if (pos[0] > 0u && map[pos[0] - 1u][pos[1]] - '0' == curr + 1)
					q.push({pos[0] - 1u, pos[1]});
				if (pos[0] < nr - 1 && map[pos[0] + 1u][pos[1]] - '0' == curr + 1)
					q.push({pos[0] + 1u, pos[1]});
				if (pos[1] > 0u && map[pos[0]][pos[1] - 1u] - '0' == curr + 1)
					q.push({pos[0], pos[1] - 1u});
				if (pos[1] < nc - 1 && map[pos[0]][pos[1] + 1u] - '0' == curr + 1)
					q.push({pos[0], pos[1] + 1u});
			}
		}
	}


	writeSolution(resA, resB);
}


