/*
 * day16.h
 *
 *  Created on: 2023-12-16
 *      Author: mbreit
 */


template <>
void executeDay<16>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	
	std::vector<std::string> map;
	std::string line;
	while (infile >> line)
		map.emplace_back(std::move(line));

	
	const auto countEnergizedTiles = [&](std::array<size_t, 3> startCfg)
	{
		unsigned cnt = 0;
		std::vector<std::vector<unsigned>> lightMap(map.size(), std::vector<unsigned>(map[0].size(), 0));
		std::queue<std::array<size_t, 3>> q;
		q.push(startCfg);
	
		while (!q.empty())
		{
			const auto& rcd = q.front();
			const unsigned r = rcd[0];
			const unsigned c = rcd[1];
			const unsigned d = rcd[2];
			q.pop();
		
			if (lightMap[r][c] & (1u << d))
				continue;

			if (!lightMap[r][c])
				++cnt;
				
			lightMap[r][c] |= 1u << d;
			const char ch = map[r][c];
			switch (d)
			{
				case 0:
					if (c + 1 < map[r].size() && (ch == '.' || ch == '-'))
						q.push({r, c + 1, 0});
					if ((r > 0) && (ch == '|' || ch == '/'))
						q.push({r - 1, c, 1});
					if (r + 1 < map.size() && (ch == '|' || ch == '\\'))
						q.push({r + 1, c, 3});
					break;
				case 1:
					if (r > 0 && (ch == '.' || ch == '|'))
						q.push({r - 1, c, 1});
					if ((c > 0) && (ch == '-' || ch == '\\'))
						q.push({r, c - 1, 2});
					if (c + 1 < map[r].size() && (ch == '-' || ch == '/'))
						q.push({r, c + 1, 0});
					break;
				case 2:
					if (c > 0 && (ch == '.' || ch == '-'))
						q.push({r, c - 1, 2});
					if ((r > 0) && (ch == '|' || ch == '\\'))
						q.push({r - 1, c, 1});
					if (r + 1 < map.size() && (ch == '|' || ch == '/'))
						q.push({r + 1, c, 3});
					break;
				case 3:
					if (r + 1 < map.size() && (ch == '.' || ch == '|'))
						q.push({r + 1, c, 3});
					if ((c > 0) && (ch == '-' || ch == '/'))
						q.push({r, c - 1, 2});
					if (c + 1 < map[r].size() && (ch == '-' || ch == '\\'))
						q.push({r, c + 1, 0});
					break;
			}
		}
		
		return cnt;
	};
	
	// part a
	unsigned resA = countEnergizedTiles({0, 0, 0});

	
	// part b	
	unsigned resB = 0;
	for (unsigned r = 0; r < map.size(); ++r)
	{
		resB = std::max(resB, countEnergizedTiles({r, 0, 0}));
		resB = std::max(resB, countEnergizedTiles({r, map[r].size() - 1, 2}));
	}
	for (unsigned c = 0; c < map[0].size(); ++c)
	{
		resB = std::max(resB, countEnergizedTiles({0, c, 3}));
		resB = std::max(resB, countEnergizedTiles({map.size() - 1, c, 1}));
	}

	
	writeSolution(resA, resB);
}


