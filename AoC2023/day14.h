/*
 * day14.h
 *
 *  Created on: 2023-12-14
 *      Author: mbreit
 */


template <>
void executeDay<14>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	
	std::vector<std::string> map;
	std::string line;
	while (infile >> line)
		map.emplace_back(std::move(line));

	
	// part a
	const auto tiltNorth = [](std::vector<std::string>& map)
	{
		for (size_t c = 0; c < map[0].size(); ++c)
		{
			size_t minPos = -1;
			size_t cnt = 0;
			for (size_t r = 0; r < map.size(); ++r)
			{
				if (map[r][c] == '#')
				{
					for (size_t k = 0; k < cnt; ++k)
						map[minPos + 1 + k][c] = 'O';
					minPos = r;
					cnt = 0; 
				}
				else if (map[r][c] == 'O')
				{
					++cnt;
					map[r][c] = '.';
				}
			}
			for (size_t k = 0; k < cnt; ++k)
				map[minPos + 1 + k][c] = 'O';
		}
	};

	const auto loadOnNorth = [](const std::vector<std::string>& map)
	{
		size_t ret = 0;
		for (size_t c = 0; c < map[0].size(); ++c)
			for (size_t r = 0; r < map.size(); ++r)
				if (map[r][c] == 'O')
					ret += map.size() - r;
		return ret;
	};
		
	auto mapCp = map;
	tiltNorth(mapCp);
	size_t resA = loadOnNorth(mapCp);
	
	
	// part b
	
	const auto tiltWest = [](std::vector<std::string>& map)
	{
		for (size_t r = 0; r < map.size(); ++r)
		{
			size_t minPos = -1;
			size_t cnt = 0;
			for (size_t c = 0; c < map[0].size(); ++c)
			{
				if (map[r][c] == '#')
				{
					for (size_t k = 0; k < cnt; ++k)
						map[r][minPos + 1 + k] = 'O';
					minPos = c;
					cnt = 0; 
				}
				else if (map[r][c] == 'O')
				{
					++cnt;
					map[r][c] = '.';
				}
			}
			for (size_t k = 0; k < cnt; ++k)
				map[r][minPos + 1 + k] = 'O';
		}
	};

	const auto tiltSouth = [](std::vector<std::string>& map)
	{
		for (size_t c = 0; c < map[0].size(); ++c)
		{
			size_t minPos = map.size();
			size_t cnt = 0;
			for (size_t r = map.size(); r > 0; --r)
			{
				if (map[r-1][c] == '#')
				{
					for (size_t k = 0; k < cnt; ++k)
						map[minPos - 1 - k][c] = 'O';
					minPos = r - 1;
					cnt = 0; 
				}
				else if (map[r-1][c] == 'O')
				{
					++cnt;
					map[r-1][c] = '.';
				}
			}
			for (size_t k = 0; k < cnt; ++k)
				map[minPos - 1 - k][c] = 'O';
		}
	};

	const auto tiltEast = [](std::vector<std::string>& map)
	{
		for (size_t r = 0; r < map.size(); ++r)
		{
			size_t minPos = map[r].size();
			size_t cnt = 0;
			for (size_t c = map[0].size(); c > 0; --c)
			{
				if (map[r][c - 1] == '#')
				{
					for (size_t k = 0; k < cnt; ++k)
						map[r][minPos - 1 - k] = 'O';
					minPos = c - 1;
					cnt = 0; 
				}
				else if (map[r][c - 1] == 'O')
				{
					++cnt;
					map[r][c - 1] = '.';
				}
			}
			for (size_t k = 0; k < cnt; ++k)
				map[r][minPos - 1 - k] = 'O';
		}
	};


	size_t resB = 0;
	std::vector<std::vector<std::string>> mem;
	mem.push_back(map);
	for (size_t i = 0; i < 1000000000; ++i)
	{
		tiltNorth(map);
		tiltWest(map);
		tiltSouth(map);
		tiltEast(map);

		size_t k = 0;
		for (; k < mem.size(); ++k)
		{
			const auto& prevMap = mem[k];
			if (map == prevMap)
				break;				
		}
	
		if (k < mem.size())
		{
			size_t cycleLen = i + 1 - k;
			size_t endInd = (1000000000 - k) % cycleLen + k;
			resB = loadOnNorth(mem[endInd]);
			break;
		}
	
		mem.push_back(map);
	}


	writeSolution(resA, resB);
}


