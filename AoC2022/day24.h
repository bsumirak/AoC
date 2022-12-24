/*
 * day24.h
 *
 *  Created on: 2022-12-24
 *      Author: mbreit
 */


template <>
void executeDay<24>(const std::string& fn)
{
	// read input
	std::vector<unsigned> map;
	unsigned nRows = 0;
	unsigned nCols = 0;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		while (std::getline(infile, line))
		{
			++nRows;
			std::istringstream iss(line);
			char c;
			while (iss >> c)
			{
				if (c == '.')
					map.push_back(0u);
				else if (c == '#')
					map.push_back(1u);
				else if (c == '>')
					map.push_back(2u);
				else if (c == '^')
					map.push_back(4u);
				else if (c == '<')
					map.push_back(8u);
				else if (c == 'v')
					map.push_back(16u);
			}
		}
		infile.close();
	}
	nCols = map.size() / nRows;

	std::vector<unsigned> newMap = map;
	auto moveBlizzardsFwd = [&]()
	{
		for (unsigned y = 1; y < nRows - 1; ++y)
			for (unsigned x = 1; x < nCols - 1; ++x)
				newMap[y * nCols + x] = 0;

		for (unsigned y = 1; y < nRows - 1; ++y)
		{
			for (unsigned x = 1; x < nCols - 1; ++x)
			{
				auto& curr = map[y * nCols + x];
				if (curr & (1u << 1u)) // blz right
				{
					if (x == nCols - 2)
						newMap[y * nCols + 1] |= (1u << 1u);
					else
						newMap[y * nCols + x + 1] |= (1u << 1u);
				}
				if (curr & (1u << 2u)) // blz up
				{
					if (y == 1)
						newMap[(nRows - 2) * nCols + x] |= (1u << 2u);
					else
						newMap[(y - 1) * nCols + x] |= (1u << 2u);
				}
				if (curr & (1u << 3u)) // blz left
				{
					if (x == 1)
						newMap[y * nCols + nCols - 2] |= (1u << 3u);
					else
						newMap[y * nCols + x - 1] |= (1u << 3u);
				}
				if (curr & (1u << 4u)) // blz down
				{
					if (y == nRows - 2)
						newMap[1 * nCols + x] |= (1u << 4u);
					else
						newMap[(y + 1) * nCols + x] |= (1u << 4u);
				}
			}
		}
		map.swap(newMap);
	};

	unsigned resA = 0;
	unsigned resB = 0;

	unsigned sy = 0;
	unsigned sx = 0;
	while (sx < nCols && map[sy * nCols + sx] == 1u)
		++sx;

	std::vector<bool> passed;
	std::array<unsigned, 3> initPos{sx, sy, 0};

	std::queue<std::array<unsigned, 3>> q;
	q.push(initPos);
	unsigned state = 0;
	unsigned it = 0;
	while (!q.empty())
	{
		auto p = q.front();
		q.pop();

		auto& x = p[0];
		auto& y = p[1];
		auto& t = p[2];

		if (t == it)
		{
			++it;
			moveBlizzardsFwd();
			passed = std::vector<bool>(map.size(), false);
		}

		if (y == nRows - 1 && state == 0)
		{
			resA = t;
			++state;
			while (!q.empty())
				q.pop();
		}
		else if (y == 0 && state == 1)
		{
			++state;
			while (!q.empty())
				q.pop();
		}
		else if (y == nRows - 1 && state == 2)
		{
			while (!q.empty())
				q.pop();
			resB = t;
			break;
		}

		if (passed[y * nCols + x])
			continue;
		passed[y * nCols + x] = true;

		if (map[y * nCols + x + 1] == 0)
			q.push(std::array<unsigned, 3>{x + 1, y, t + 1});
		if (y < nRows - 1 && map[(y + 1) * nCols + x] == 0)
			q.push(std::array<unsigned, 3>{x, y + 1, t + 1});
		if (map[y * nCols + x] == 0)
			q.push(std::array<unsigned, 3>{x, y, t + 1});
		if (y > 0 && map[(y - 1) * nCols + x] == 0)
			q.push(std::array<unsigned, 3>{x, y - 1, t + 1});
		if (map[y * nCols + x - 1] == 0)
			q.push(std::array<unsigned, 3>{x - 1, y, t + 1});
	}


	writeSolution(resA, resB);
}


