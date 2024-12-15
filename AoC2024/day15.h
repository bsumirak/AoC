/*
 * day15.h
 *
 *  Created on: 2024-12-15
 *      Author: mbreit
 */


template <>
void executeDay<15>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());
	
	std::vector<std::string> map;
	std::vector<std::string> map2;
	std::array<unsigned, 2> startPos{0, 0};

	std::string line;
	std::string line2;
	while (std::getline(infile, line))
	{
		if (line.empty())
			break;
		const auto it = std::find(line.begin(), line.end(), '@');
		if (it != line.end())
		{
			startPos = {(unsigned)map.size(), (unsigned)std::distance(line.begin(), it)};
			*it = '.';
		}

		line2.clear();
		for (const auto c : line)
			line2 += c == 'O' ? "[]" : std::string(2, c);

		map.push_back(line);
		map2.push_back(line2);
	}
	const auto nr = map.size();
	const auto nc = map[0].size();

	std::string mvmts;
	while (std::getline(infile, line))
		mvmts += line;

	// part a
	auto pos = startPos;
	for (const char c : mvmts)
	{
		auto p = pos;
		unsigned cnt = 0;
		while (true)
		{
			switch (c)
			{
				case '>': ++p[1]; break;
				case '<': --p[1]; break;
				case '^': --p[0]; break;
				case 'v': ++p[0]; break;
			}
			++cnt;

			if (map[p[0]][p[1]] == '.')
				break;
			if (map[p[0]][p[1]] == '#')
				break;
		}
		if (map[p[0]][p[1]] == '#')
			continue;

		switch (c)
		{
			case '>': ++pos[1]; break;
			case '<': --pos[1]; break;
			case '^': --pos[0]; break;
			case 'v': ++pos[0]; break;
		}

		if (cnt > 1u)
		{
			map[pos[0]][pos[1]] = '.';
			map[p[0]][p[1]] = 'O';
		}
	}

	uint64_t resA = 0;
	for (size_t r = 0; r < nr; ++r)
	{
		for (size_t c = 0; c < nc; ++c)
		{
			if (map[r][c] == 'O')
				resA += 100u * r + c;
		}
	}


	// part b
	pos = {startPos[0], 2u * startPos[1]};
	for (const char c : mvmts)
	{
		std::vector<bool> added(2*nr*nc, false);
		std::vector<std::array<unsigned, 2>> boxes;
		std::queue<std::array<unsigned, 2>> q;
		q.push(pos);

		bool canMove = true;
		while (!q.empty())
		{
			auto p = q.front();
			q.pop();
			switch (c)
			{
				case '>': ++p[1]; break;
				case '<': --p[1]; break;
				case '^': --p[0]; break;
				case 'v': ++p[0]; break;
			}

			if (map2[p[0]][p[1]] == '.')
				continue;
			if (map2[p[0]][p[1]] == '#')
			{
				canMove = false;
				break;
			}

			if (!added[2*p[0]*nc + p[1]])
			{
				boxes.push_back(p);
				q.push(p);
				added[2*p[0]*nc + p[1]] = true;
			}
			if (c == 'v' || c == '^')
			{
				if (map2[p[0]][p[1]] == '[')
				{
					if (!added[2*p[0]*nc + p[1] + 1u])
					{
						q.push({p[0], p[1] + 1u});
						boxes.push_back({p[0], p[1] + 1u});
						added[2*p[0]*nc + p[1] + 1u] = true;
					}
				}
				else if (map2[p[0]][p[1]] == ']')
				{
					if (!added[2*p[0]*nc + p[1] - 1u])
					{
						q.push({p[0], p[1] - 1u});
						boxes.push_back({p[0], p[1] - 1u});
						added[2*p[0]*nc + p[1] - 1u] = true;
					}
				}
			}
		}

		if (!canMove)
			continue;

		switch (c)
		{
			case '>': ++pos[1]; break;
			case '<': --pos[1]; break;
			case '^': --pos[0]; break;
			case 'v': ++pos[0]; break;
		}

		for (auto it = boxes.rbegin(); it != boxes.rend(); ++it)
		{
			switch (c)
			{
				case '>': map2[(*it)[0]][(*it)[1] + 1u] = map2[(*it)[0]][(*it)[1]]; break;
				case '<': map2[(*it)[0]][(*it)[1] - 1u] = map2[(*it)[0]][(*it)[1]]; break;
				case '^': map2[(*it)[0] - 1u][(*it)[1]] = map2[(*it)[0]][(*it)[1]]; break;
				case 'v': map2[(*it)[0] + 1u][(*it)[1]] = map2[(*it)[0]][(*it)[1]]; break;
			}
			map2[(*it)[0]][(*it)[1]] = '.';
		}
	}

	uint64_t resB = 0;
	for (size_t r = 0; r < nr; ++r)
	{
		for (size_t c = 0; c < 2*nc; ++c)
		{
			if (map2[r][c] == '[')
				resB += 100u * r + c;
		}
	}


	writeSolution(resA, resB);
}

