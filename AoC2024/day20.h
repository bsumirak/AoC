/*
 * day20.h
 *
 *  Created on: 2024-12-20
 *      Author: mbreit
 */


template <>
void executeDay<20>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::vector<std::string> map;
	std::array<unsigned, 2> startPos{0, 0};
	std::array<unsigned, 2> endPos{0, 0};

	std::string line;
	while (std::getline(infile, line))
	{
		auto it = std::find(line.begin(), line.end(), 'S');
		if (it != line.end())
		{
			startPos = {(unsigned)map.size(), (unsigned)std::distance(line.begin(), it)};
			*it = '.';
		}
		it = std::find(line.begin(), line.end(), 'E');
		if (it != line.end())
		{
			endPos = {(unsigned)map.size(), (unsigned)std::distance(line.begin(), it)};
			*it = '.';
		}
		map.push_back(line);
	}
	const unsigned nr = map.size();
	const unsigned nc = map[0].size();


	std::vector<unsigned> visited(nr*nc, std::numeric_limits<unsigned>::max());
	std::queue<std::array<unsigned, 2>> q;
	q.push({startPos[0] * nc + startPos[1], 0});
	while (!q.empty())
	{
		const auto [p, n] = q.front();
		q.pop();
		const auto r = p / nc;
		const auto c = p % nc;

		if (visited[p] <= n)
			continue;
		visited[p] = n;

		if (r == endPos[0] && c == endPos[1])
			break;

		if (r > 0u && map[r - 1u][c] == '.')
			q.push({(r - 1u) * nc + c, n + 1u});
		if (r < nr - 1u && map[r + 1u][c] == '.')
			q.push({(r + 1u) * nc + c, n + 1u});
		if (c > 0u && map[r][c - 1u] == '.')
			q.push({r * nc + c - 1u, n + 1u});
		if (c < nc - 1u && map[r][c + 1u] == '.')
			q.push({r * nc + c + 1u, n + 1u});
	}


	const auto countShortcuts = [&](unsigned k)
	{
		unsigned ret = 0u;
		for (unsigned r = 0; r < nr; ++r)
		{
			for (unsigned c = 0; c < nc; ++c)
			{
				if (map[r][c] != '.')
					continue;

				for (unsigned rr = std::max(k, r) - k; rr <= std::min(nr - 1u, r + k); ++rr)
				{
					const auto vert = k - (unsigned)std::abs((int)rr - (int)r);
					for (unsigned cc = std::max(vert, c) - vert; cc <= std::min(nc - 1u, c + vert); ++cc)
					{
						const auto horiz = (unsigned)std::abs((int)cc - (int)c);
						const auto num = (k - vert) + horiz;
						if (num > k)
							std::cout << "blub" << std::endl;
						if (map[rr][cc] == '.' && visited[rr * nc + cc] + 100u + num <= visited[r * nc + c])
							++ret;
					}
				}
			}
		}
		return ret;
	};

	auto resA = countShortcuts(2u);
	auto resB = countShortcuts(20u);


	writeSolution(resA, resB);
}

