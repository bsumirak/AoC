/*
 * day12.h
 *
 *  Created on: 2024-12-12
 *      Author: mbreit
 */

template <>
void executeDay<12>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::vector<std::string> map;

	std::string line;
	while (std::getline(infile, line))
		map.push_back(line);
	const auto nr = map.size();
	const auto nc = map[0].size();

	uint64_t resA = 0u;
	uint64_t resB = 0u;
	std::vector<bool> visited(nr*nc, false);

	for (size_t r = 0; r < nr; ++r)
	{
		for (size_t c = 0; c < nc; ++c)
		{
			if (visited[nc*r + c])
				continue;

			unsigned area = 0u;
			unsigned perim = 0u;
			unsigned perimB = 0u;

			const char ch = map[r][c];

			std::queue<std::array<size_t, 2>> q;
			q.push({r, c});
			while (!q.empty())
			{
				const auto [rr, cc] = q.front();
				q.pop();

				if (visited[nc*rr + cc])
					continue;
				visited[nc*rr + cc] = true;

				++area;

				if (rr > 0u && map[rr - 1u][cc] == ch)
					q.push({rr - 1u, cc});
				else
				{
					++perim;
					if (cc == nc - 1u || map[rr][cc + 1u] != ch // to the left of an outside corner
						|| (rr > 0u && cc < nc - 1u && map[rr - 1u][cc + 1u] == ch)) // to the right of an inside corner 
						++perimB;
				}
				if (rr < nr - 1u && map[rr + 1u][cc] == ch)
					q.push({rr + 1u, cc});
				else
				{
					++perim;
					if (cc == 0u || map[rr][cc - 1u] != ch || (rr < nr - 1u && cc > 0u && map[rr + 1u][cc - 1u] == ch))
						++perimB;
				}
				if (cc > 0u && map[rr][cc - 1u] == ch)
					q.push({rr, cc - 1u});
				else
				{
					++perim;
					if (rr == 0u || map[rr - 1u][cc] != ch || (cc > 0u && rr > 0u && map[rr - 1u][cc - 1u] == ch))
						++perimB;
				}
				if (cc < nc - 1u && map[rr][cc + 1u] == ch)
					q.push({rr, cc + 1u});
				else
				{
					++perim;
					if (rr == nr - 1u || map[rr + 1u][cc] != ch || (cc < nc - 1u && rr < nr - 1u && map[rr + 1u][cc + 1u] == ch))
						++perimB;
				}
			}

			resA += area * perim;
			resB += area * perimB;
		}
	}

	writeSolution(resA, resB);
}


