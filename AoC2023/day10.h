/*
 * day10.h
 *
 *  Created on: 2023-12-10
 *      Author: mbreit
 */

template <>
void executeDay<10>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	
	unsigned r = 0;
	unsigned c = 0;
	std::string line;
	std::vector<std::string> map;
	while (std::getline(infile, line))
	{
		const auto it = std::find(line.begin(), line.end(), 'S');
		if (it != line.end())
		{
			r = map.size();
			c = std::distance(line.begin(), it);
		}
		map.emplace_back(std::move(line));
	}
	
	// part a
	unsigned prevDir = 0;
	const auto r0 = r;
	const auto c0 = c;
	unsigned sConnectsTo = 0;
	if (c0 + 1 < map[r0].size() && (map[r0][c0 + 1] == '-' || map[r0][c0 + 1] == 'J' || map[r0][c0 + 1] == '7'))
		sConnectsTo |= 1u;	
	if (r0 > 0 && (map[r0 - 1][c0] == '|' || map[r0 - 1][c0] == '7' || map[r0 - 1][c0] == 'F'))
		sConnectsTo |= 2u;
	if (c0 > 0 && (map[r0][c0 - 1] == '-' || map[r0][c0 - 1] == 'F' || map[r0][c0 - 1] == 'L'))
		sConnectsTo |= 4u;
	if (r0 + 1 < map.size() && (map[r0 + 1][c0] == '|' || map[r0 + 1][c0] == 'J' || map[r0 + 1][c0] == 'L'))
		sConnectsTo |= 8u;
	
	switch (sConnectsTo)
	{
		case 3u:
		case 5u:
		case 7u:
			map[r0][c0] = sConnectsTo == 3u ? 'L' : sConnectsTo == 5u ? '-' : 'F';
			++c;
			prevDir = 0;
			break;
		case 6u:
		case 10u:
			map[r0][c0] = sConnectsTo == 6u ? 'J' : '|';
			--r;
			prevDir = 1;
			break;
		case 12u:
			map[r0][c0] = '7';
			--c;
			prevDir = 2;
			break;
		default:
			std::cout << "impossible start situation" << std::endl;
			return;
	}

	std::vector<std::vector<bool>> inLoop(map.size(), std::vector<bool>(map[0].size(), false));
	inLoop[r0][c0] = true;
	
	unsigned len = 1;
	while (r != r0 || c != c0)
	{
		const char cur = map[r][c];
		inLoop[r][c] = true;
	
		switch (prevDir)
		{
			case 0:
				if (cur == '-')
					++c;
				else if (cur == '7')
				{
					++r;
					prevDir = 3;
				}
				else if (cur == 'J')
				{
					--r;
					prevDir = 1;
				}
				else return;
				break;
			case 1:
				if (cur == '|')
					--r;
				else if (cur == '7')
				{
					--c;
					prevDir = 2;
				}
				else if (cur == 'F')
				{
					++c;
					prevDir = 0;
				}
				else return;
				break;
			case 2:
				if (cur == '-')
					--c;
				else if (cur == 'L')
				{
					--r;
					prevDir = 1;
				}
				else if (cur == 'F')
				{
					++r;
					prevDir = 3;
				}
				else return;
				break;
			case 3:
				if (cur == '|')
					++r;
				else if (cur == 'J')
				{
					--c;
					prevDir = 2;
				}
				else if (cur == 'L')
				{
					++c;
					prevDir = 0;
				}
				else return;
				break;
		}
		
		++len;
	}
	size_t resA = len / 2;
	
	
	// part b
	unsigned resB = 0;
	for (size_t r = 0; r < map.size(); ++r)
	{
		const auto& row = map[r];
		unsigned crossCnt = 0;
		char lastBorderEntry = '|';
		for (size_t c = 0; c < row.size(); ++c)
		{
			if (!inLoop[r][c] && crossCnt % 2 == 1)
				++resB;
			else if (inLoop[r][c])
			{
				if (row[c] == '|')
					++crossCnt;
				else if (row[c] == 'F' || row[c] == 'L')
					lastBorderEntry = row[c];
				else if (row[c] == 'J' && lastBorderEntry == 'F')
					++crossCnt;
				else if (row[c] == '7' && lastBorderEntry == 'L')
					++crossCnt;
			}
		}
	}
	
	
	writeSolution(resA, resB);
}


