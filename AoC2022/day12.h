/*
 * day12.h
 *
 *  Created on: 2022-12-12
 *      Author: mbreit
 */


template <>
void executeDay<12>(const std::string& fn)
{
	// read input
	size_t start;
	size_t tgt;
	std::string map(41*83, 'a');
	{
		std::ifstream infile(fn.c_str());
		size_t i = 0;
		while (infile >> map[i])
		{
			if (map[i] == 'S')
			{
				start = i;
				map[i] = 'a';
			}
			else if (map[i] == 'E')
			{
				tgt = i;
				map[i] = 'z';
			}
			++i;
		}
		infile.close();
	}

	// part a
	auto findShortestWay = [&](size_t start)
	{
		std::vector<bool> passed(map.size(), false);
		std::queue<std::pair<size_t, unsigned>> q;
		q.push(std::make_pair(start, 0));
		while (!q.empty())
		{
			auto& pp = q.front();
			auto pos = pp.first;
			auto prio = pp.second;
			q.pop();

			if (pos == tgt)
				return prio;

			if (passed[pos])
				continue;

			passed[pos] = true;

			if (pos / 83 > 0 && map[pos - 83] <= map[pos] + 1 && !passed[pos - 83])
				q.push(std::make_pair(pos - 83, prio + 1));
			if (pos / 83 < 40 && map[pos + 83] <= map[pos] + 1 && !passed[pos + 83])
				q.push(std::make_pair(pos + 83, prio + 1));
			if (pos % 83 > 0 && map[pos - 1] <= map[pos] + 1 && !passed[pos - 1])
				q.push(std::make_pair(pos - 1, prio + 1));
			if (pos % 83 < 82 && map[pos + 1] <= map[pos] + 1 && !passed[pos + 1])
				q.push(std::make_pair(pos + 1, prio + 1));
		}
		return std::numeric_limits<unsigned>::max();
	};
	unsigned resA = findShortestWay(start);

	// part b
	auto findShortestWayBack = [&](size_t start)
	{
		std::vector<bool> passed(map.size(), false);
		std::queue<std::pair<size_t, unsigned>> q;
		q.push(std::make_pair(start, 0));
		while (!q.empty())
		{
			auto& pp = q.front();
			auto pos = pp.first;
			auto prio = pp.second;
			q.pop();

			if (map[pos] == 'a')
				return prio;

			if (passed[pos])
				continue;

			passed[pos] = true;

			if (pos / 83 > 0 && map[pos - 83] >= map[pos] - 1 && !passed[pos - 83])
				q.push(std::make_pair(pos - 83, prio + 1));
			if (pos / 83 < 40 && map[pos + 83] >= map[pos] - 1 && !passed[pos + 83])
				q.push(std::make_pair(pos + 83, prio + 1));
			if (pos % 83 > 0 && map[pos - 1] >= map[pos] - 1 && !passed[pos - 1])
				q.push(std::make_pair(pos - 1, prio + 1));
			if (pos % 83 < 82 && map[pos + 1] >= map[pos] - 1 && !passed[pos + 1])
				q.push(std::make_pair(pos + 1, prio + 1));
		}
		return std::numeric_limits<unsigned>::max();
	};
	unsigned resB = findShortestWayBack(tgt);

	writeSolution(resA, resB);
}


