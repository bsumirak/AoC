/*
 * day05.h
 *
 *  Created on: 2023-12-05
 *      Author: mbreit
 */

template <>
void executeDay<5>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	uint64_t resA = 0;
	uint64_t resB = 0;
	
	std::string line;
	std::getline(infile, line);
	std::istringstream iss(line);
	std::string s;
	iss >> s;
	
	uint64_t u;
	std::vector<uint64_t> seeds;
	while (iss >> u)
		seeds.push_back(u);
	
	std::vector<std::vector<std::array<uint64_t, 3>>> maps;
	
	while (std::getline(infile, line))
	{
		if (line.empty())
		{
			maps.emplace_back();
			std::getline(infile, line);
			continue;
		}
		
		auto& map = maps.back();
		map.emplace_back();
		auto& triple = map.back();
		
		std::istringstream iss(line);
		iss >> triple[0];
		iss >> triple[1];
		iss >> triple[2];
	}
	
	for (auto& map : maps)
		std::sort(map.begin(), map.end(), [](const std::array<uint64_t, 3>& t1, const std::array<uint64_t, 3>& t2)
		{return t1[1] < t2[1];});
	
	
	// part a
	uint64_t minLoc = -1;
	for (const auto& seed : seeds)
	{
		uint64_t curVal = seed;
		for (const auto& map : maps)
		{
			for (const auto& triple : map)
			{
				if (curVal >= triple[1] && curVal < triple[1] + triple[2])
				{
					curVal = triple[0] + curVal - triple[1];
					break;
				}
			}
		}
		
		minLoc = std::min(minLoc, curVal);
	}
	
	resA = minLoc;
	
	// part b
	std::stack<std::array<uint64_t, 3>> stack;
	for (size_t k = 0; k < seeds.size(); k += 2)
	{
		stack.push({seeds[k], seeds[k+1], 0});
		while (!stack.empty())
		{
			auto cur = stack.top();
			auto start = cur[0];
			auto len = cur[1];
			const auto lvl = cur[2];
			stack.pop();
			if (lvl == maps.size())
			{
				minLoc = std::min(minLoc, start);
				continue;
			}
			
			bool processed = false;
			const auto& map = maps[lvl];
			for (const auto& triple : map)
			{
				const auto rangeStart = triple[0];
				const auto domStart = triple[1];
				const auto size = triple[2];
				
				if (start + len <= domStart)
				{
					stack.push({start, len, lvl + 1});
					processed = true;
					break;
				}
				
				if (start >= domStart + size)
					continue;
				
				if (start < domStart)
				{
					stack.push({start, domStart - start, lvl + 1});
					if (start + len <= domStart + size)
					{
						stack.push({rangeStart, start + len - domStart, lvl + 1});
						processed = true;
						break;
					}
					else
					{
						stack.push({rangeStart, size, lvl + 1});
						len = start + len - (domStart + size);
						start = domStart + size;
					}
				}
				else
				{
					if (start + len <= domStart + size)
					{
						stack.push({rangeStart + start - domStart, len, lvl + 1});
						processed = true;
						break;
					}
					else
					{
						stack.push({rangeStart + start - domStart, domStart + size - start, lvl + 1});
						len = start + len - (domStart + size);
						start = domStart + size;
					}
				}
			}
			if (!processed)
				stack.push({start, len, lvl + 1});
		}
	}

	resB = minLoc;
	
	writeSolution(resA, resB);
}


