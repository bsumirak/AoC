/*
 * day16.h
 *
 *  Created on: 2024-12-16
 *      Author: mbreit
 */

void recurse16(std::vector<std::array<unsigned, 4>> vv, std::vector<bool>& partOfBest,
	const std::vector<std::array<unsigned, 4>>& minPass, const unsigned best,
	const std::vector<std::string>& map, const std::array<unsigned, 2>& endPos,
	unsigned nr, unsigned nc)
{
	const auto v = vv.back();

	if (v[3] > minPass[v[0] * nc + v[1]][v[2]] || v[3] > best)
		return;

	if (v[0] == endPos[0] && v[1] == endPos[1])
	{
		for (auto& w : vv)
			partOfBest[w[0] * nc + w[1]] = true;

		return;
	}

	switch (v[2])
	{
		case 0u:
			if (v[1] < nc - 1u && map[v[0]][v[1] + 1u] == '.')
			{
				auto w = v;
				w[1] += 1u;
				w[3] += 1u;
				vv.push_back(w);
				recurse16(vv, partOfBest, minPass, best, map, endPos, nr, nc);
				vv.resize(vv.size() - 1u);
			}
			if (v[0] > 0u && map[v[0] - 1u][v[1]] == '.')
			{
				auto w = v;
				w[0] -= 1u;
				w[2] = 1u;
				w[3] += 1001u;
				vv.push_back(w);
				recurse16(vv, partOfBest, minPass, best, map, endPos, nr, nc);
				vv.resize(vv.size() - 1u);
			}
			if (v[0] < nr - 1u && map[v[0] + 1u][v[1]] == '.')
			{
				auto w = v;
				w[0] += 1u;
				w[2] = 3u;
				w[3] += 1001u;
				vv.push_back(w);
				recurse16(vv, partOfBest, minPass, best, map, endPos, nr, nc);
				vv.resize(vv.size() - 1u);
			}
			break;
		case 1u:
			if (v[0] > 0u && map[v[0] - 1u][v[1]] == '.')
			{
				auto w = v;
				w[0] -= 1u;
				w[3] += 1u;
				vv.push_back(w);
				recurse16(vv, partOfBest, minPass, best, map, endPos, nr, nc);
				vv.resize(vv.size() - 1u);
			}
			if (v[1] > 0u && map[v[0]][v[1] - 1u] == '.')
			{
				auto w = v;
				w[1] -= 1u;
				w[2] = 2u;
				w[3] += 1001u;
				vv.push_back(w);
				recurse16(vv, partOfBest, minPass, best, map, endPos, nr, nc);
				vv.resize(vv.size() - 1u);
			}
			if (v[1] < nc - 1u && map[v[0]][v[1] + 1u] == '.')
			{
				auto w = v;
				w[1] += 1u;
				w[2] = 0u;
				w[3] += 1001u;
				vv.push_back(w);
				recurse16(vv, partOfBest, minPass, best, map, endPos, nr, nc);
				vv.resize(vv.size() - 1u);
			}
			break;
		case 2u:
			if (v[1] > 0u && map[v[0]][v[1] - 1u] == '.')
			{
				auto w = v;
				w[1] -= 1u;
				w[3] += 1u;
				vv.push_back(w);
				recurse16(vv, partOfBest, minPass, best, map, endPos, nr, nc);
				vv.resize(vv.size() - 1u);
			}
			if (v[0] > 0u && map[v[0] - 1u][v[1]] == '.')
			{
				auto w = v;
				w[0] -= 1u;
				w[2] = 1u;
				w[3] += 1001u;
				vv.push_back(w);
				recurse16(vv, partOfBest, minPass, best, map, endPos, nr, nc);
				vv.resize(vv.size() - 1u);
			}
			if (v[0] < nr - 1u && map[v[0] + 1u][v[1]] == '.')
			{
				auto w = v;
				w[0] += 1u;
				w[2] = 3u;
				w[3] += 1001u;
				vv.push_back(w);
				recurse16(vv, partOfBest, minPass, best, map, endPos, nr, nc);
				vv.resize(vv.size() - 1u);
			}
			break;
		case 3u:
			if (v[0] < nr - 1u && map[v[0] + 1u][v[1]] == '.')
			{
				auto w = v;
				w[0] += 1u;
				w[3] += 1u;
				vv.push_back(w);
				recurse16(vv, partOfBest, minPass, best, map, endPos, nr, nc);
				vv.resize(vv.size() - 1u);
			}
			if (v[1] > 0u && map[v[0]][v[1] - 1u] == '.')
			{
				auto w = v;
				w[1] -= 1u;
				w[2] = 2u;
				w[3] += 1001u;
				vv.push_back(w);
				recurse16(vv, partOfBest, minPass, best, map, endPos, nr, nc);
				vv.resize(vv.size() - 1u);
			}
			if (v[1] < nc - 1u && map[v[0]][v[1] + 1u] == '.')
			{
				auto w = v;
				w[1] += 1u;
				w[2] = 0u;
				w[3] += 1001u;
				vv.push_back(w);
				recurse16(vv, partOfBest, minPass, best, map, endPos, nr, nc);
				vv.resize(vv.size() - 1u);
			}
			break;
	}
}


template <>
void executeDay<16>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	uint64_t resB = 0u;

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
	const auto nr = map.size();
	const auto nc = map[0].size();

	const auto mx = std::numeric_limits<unsigned>::max();
	unsigned resA = mx;
	std::vector<std::array<unsigned, 4>> passed(nr*nc, std::array<unsigned, 4>{mx, mx, mx, mx});
	std::queue<std::array<unsigned, 4>> q;
	q.push({startPos[0], startPos[1], 0u, 0u});
	while (!q.empty())
	{
		auto v = q.front();
		q.pop();

		if (v[3] > passed[v[0] * nc + v[1]][v[2]] || v[3] > resA)
			continue;
		passed[v[0] * nc + v[1]][v[2]] = v[3];

		if (v[0] == endPos[0] && v[1] == endPos[1])
		{
			resA = v[3];
			continue;
		}

		switch (v[2])
		{
			case 0u:
				if (v[1] < nc - 1u && map[v[0]][v[1] + 1u] == '.')
				{
					auto w = v;
					w[1] += 1u;
					w[3] += 1u;
					q.push(w);
				}
				if (v[0] > 0u && map[v[0] - 1u][v[1]] == '.')
				{
					auto w = v;
					w[0] -= 1u;
					w[2] = 1u;
					w[3] += 1001u;
					q.push(w);
				}
				if (v[0] < nr - 1u && map[v[0] + 1u][v[1]] == '.')
				{
					auto w = v;
					w[0] += 1u;
					w[2] = 3u;
					w[3] += 1001u;
					q.push(w);
				}
				break;
			case 1u:
				if (v[0] > 0u && map[v[0] - 1u][v[1]] == '.')
				{
					auto w = v;
					w[0] -= 1u;
					w[3] += 1u;
					q.push(w);
				}
				if (v[1] > 0u && map[v[0]][v[1] - 1u] == '.')
				{
					auto w = v;
					w[1] -= 1u;
					w[2] = 2u;
					w[3] += 1001u;
					q.push(w);
				}
				if (v[1] < nc - 1u && map[v[0]][v[1] + 1u] == '.')
				{
					auto w = v;
					w[1] += 1u;
					w[2] = 0u;
					w[3] += 1001u;
					q.push(w);
				}
				break;
			case 2u:
				if (v[1] > 0u && map[v[0]][v[1] - 1u] == '.')
				{
					auto w = v;
					w[1] -= 1u;
					w[3] += 1u;
					q.push(w);
				}
				if (v[0] > 0u && map[v[0] - 1u][v[1]] == '.')
				{
					auto w = v;
					w[0] -= 1u;
					w[2] = 1u;
					w[3] += 1001u;
					q.push(w);
				}
				if (v[0] < nr - 1u && map[v[0] + 1u][v[1]] == '.')
				{
					auto w = v;
					w[0] += 1u;
					w[2] = 3u;
					w[3] += 1001u;
					q.push(w);
				}
				break;
			case 3u:
				if (v[0] < nr - 1u && map[v[0] + 1u][v[1]] == '.')
				{
					auto w = v;
					w[0] += 1u;
					w[3] += 1u;
					q.push(w);
				}
				if (v[1] > 0u && map[v[0]][v[1] - 1u] == '.')
				{
					auto w = v;
					w[1] -= 1u;
					w[2] = 2u;
					w[3] += 1001u;
					q.push(w);
				}
				if (v[1] < nc - 1u && map[v[0]][v[1] + 1u] == '.')
				{
					auto w = v;
					w[1] += 1u;
					w[2] = 0u;
					w[3] += 1001u;
					q.push(w);
				}
				break;
		}
	}

	std::vector<std::array<unsigned, 4>> path;
	path.push_back(std::array<unsigned, 4>{startPos[0], startPos[1], 0u, 0u});
	std::vector<bool> partOfBest(nr*nc, false);
	recurse16(path, partOfBest, passed, resA, map, endPos, nr, nc);

	for (auto b : partOfBest)
		if (b)
			++resB;


	writeSolution(resA, resB);
}

