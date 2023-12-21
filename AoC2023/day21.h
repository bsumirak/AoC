/*
 * day21.h
 *
 *  Created on: 2023-12-21
 *      Author: mbreit
 */

template <>
void executeDay<21>(const std::string& fn)
{
	// parse input
	std::ifstream infile(fn.c_str());
	
	std::vector<std::string> map;
	std::string line;
	while (infile >> line)
		map.emplace_back(std::move(line));

	const size_t sz = map.size();	


	auto countPossibilities = [&](std::array<size_t, 2> startPos, size_t numSteps)
	{
		char curr = 'o';
		char next = 'O';
		auto m = map;
		m[startPos[0]][startPos[1]] = curr;
	
		uint64_t ret = 0;
		for (size_t k = 0; k < numSteps; ++k)
		{
			for (size_t r = 0; r < sz; ++r)
			{
				for (size_t c = 0; c < sz; ++c)
				{
					if (m[r][c] != curr)
						continue;
					
					m[r][c] = '.';
					if (c + 1 < sz && m[r][c+1] == '.')
					{
						if (k == numSteps - 1)
							++ret;
						m[r][c+1] = next;
					}
					if (c > 0 && m[r][c-1] == '.')
					{
						if (k == numSteps - 1)
							++ret;
						m[r][c-1] = next;
					}
					if (r + 1 < sz && m[r+1][c] == '.')
					{
						if (k == numSteps - 1)
							++ret;
						m[r+1][c] = next;
					}
					if (r > 0 && m[r-1][c] == '.')
					{
						if (k == numSteps - 1)
							++ret;
						m[r-1][c] = next;
					}
				}
			}
			std::swap(curr, next);
		}
		
		return ret;
	};

	
	// part a
	std::array<size_t, 2> pos;
	for (size_t r = 0; r < map.size(); ++r)
	{
		for (size_t c = 0; c < map[0].size(); ++c)
		{
			if (map[r][c] == 'S')
			{
				pos = {r, c};
				map[r][c] = '.';
				break;
			}
		}
	}
	uint64_t resA = countPossibilities(pos, 64);	
	
	
	// part b
	const uint64_t numSteps = 26501365u;
	const uint64_t n = (numSteps - 65u) / 131u;
	
	uint64_t resB = (n - 1) * (n - 1) * countPossibilities(pos, 131);
	resB += n * n * countPossibilities(pos, 130);

	resB += n * countPossibilities({0, 0}, 64) + (n - 1) * countPossibilities({0, 0}, 195);
	resB += n * countPossibilities({0, 130}, 64) + (n - 1) * countPossibilities({0, 130}, 195);
	resB += n * countPossibilities({130, 130}, 64) + (n - 1) * countPossibilities({130, 130}, 195);
	resB += n * countPossibilities({130, 0}, 64) + (n - 1) * countPossibilities({130, 0}, 195);
	
	resB += countPossibilities({0, 65}, 130);
	resB += countPossibilities({65, 130}, 130);
	resB += countPossibilities({130, 65}, 130);
	resB += countPossibilities({65, 0}, 130);
	
	writeSolution(resA, resB);
}


