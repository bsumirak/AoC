/*
 * day23.h
 *
 *  Created on: 2023-12-23
 *      Author: mbreit
 */


void recurse23a(const std::vector<std::string>& map, std::set<std::array<size_t, 2>>& path,
	std::array<size_t, 2> pos, const std::array<size_t, 2>& tgt, unsigned len, unsigned& maxLen)
{
	if (pos == tgt)
	{
		maxLen = std::max(maxLen, len);
		return;
	}
	
	auto insRes = path.insert(pos);
	if (!insRes.second)
		return;
	
	if (map[pos[0]][pos[1]] == '<')
	{
		std::array<size_t, 2> nextPos{pos[0], pos[1] - 1};
		recurse23a(map, path, nextPos, tgt, len + 1, maxLen);
	}
	else if (map[pos[0]][pos[1]] == '>')
	{
		std::array<size_t, 2> nextPos{pos[0], pos[1] + 1};
		recurse23a(map, path, nextPos, tgt, len + 1, maxLen);
	}
	else if (map[pos[0]][pos[1]] == 'v')
	{
		std::array<size_t, 2> nextPos{pos[0] + 1, pos[1]};
		recurse23a(map, path, nextPos, tgt, len + 1, maxLen);
	}
	else if (map[pos[0]][pos[1]] == '^')
	{
		std::array<size_t, 2> nextPos{pos[0] - 1, pos[1]};
		recurse23a(map, path, nextPos, tgt, len + 1, maxLen);
	}
	else
	{
		if (pos[1] + 1 < map[pos[0]].size() && map[pos[0]][pos[1] + 1] != '#')
		{
			std::array<size_t, 2> nextPos{pos[0], pos[1] + 1};
			recurse23a(map, path, nextPos, tgt, len + 1, maxLen);
		}
		if (pos[1] > 0 && map[pos[0]][pos[1] - 1] != '#')
		{
			std::array<size_t, 2> nextPos{pos[0], pos[1] - 1};
			recurse23a(map, path, nextPos, tgt, len + 1, maxLen);
		}
		if (pos[0] + 1 < map.size() && map[pos[0] + 1][pos[1]] != '#')
		{
			std::array<size_t, 2> nextPos{pos[0] + 1, pos[1]};
			recurse23a(map, path, nextPos, tgt, len + 1, maxLen);
		}
		if (pos[0] > 0 && map[pos[0] - 1][pos[1]] != '#')
		{
			std::array<size_t, 2> nextPos{pos[0] - 1, pos[1]};
			recurse23a(map, path, nextPos, tgt, len + 1, maxLen);
		}
	}
	
	path.erase(path.find(pos));
}



struct Node23
{
	bool visited = false;
	std::vector<unsigned> len;
	std::vector<std::shared_ptr<Node23>> children;
};


std::array<std::shared_ptr<Node23>, 2> makeForkGraph23(const std::vector<std::string>& map,
	const std::array<size_t, 2>& start, const std::array<size_t, 2>& goal)
{
	std::map<std::array<size_t, 2>, std::shared_ptr<Node23>> forkMap;
	for (size_t r = 0; r < map.size(); ++r)
	{
		for (size_t c = 0; c < map[r].size(); ++c)
		{
			if (map[r][c] == '#')
				continue;
			
			size_t cnt = 0;
			if (r + 1 < map.size() && map[r + 1][c] != '#')
				++cnt;
			if (r > 0 && map[r - 1][c] != '#')
				++cnt;
			if (c + 1 < map[r].size() && map[r][c + 1] != '#')
				++cnt;
			if (c > 0 && map[r][c - 1] != '#')
				++cnt;
			
			if (cnt > 2)
				forkMap[{r, c}] = std::make_shared<Node23>();
		}
	}

	forkMap[start] = std::make_shared<Node23>();
	forkMap[goal] = std::make_shared<Node23>();
	
	for (auto& mapPair : forkMap)
	{
		auto continueToNextFork = [&](std::array<size_t, 2> currPos, std::array<size_t, 2> prevPos)
		{
			unsigned len = 0;
			
			while (true)
			{
				size_t r = currPos[0];
				size_t c = currPos[1];
				if (r + 1 < map.size() && map[r + 1][c] != '#' && (r + 1 != prevPos[0] || c != prevPos[1]))
				{
					++len;
					prevPos = currPos;
					currPos[0] = r + 1;
				}
				else if (r > 0 && map[r - 1][c] != '#' && (r - 1 != prevPos[0] || c != prevPos[1]))
				{
					++len;
					prevPos = currPos;
					currPos[0] = r - 1;
				}
				else if (c + 1 < map[r].size() && map[r][c + 1] != '#' && (c + 1 != prevPos[1] || r != prevPos[0]))
				{
					++len;
					prevPos = currPos;
					currPos[1] = c + 1;
				}
				else if (c > 0 && map[r][c - 1] != '#' && (c - 1 != prevPos[1] || r != prevPos[0]))
				{
					++len;
					prevPos = currPos;
					currPos[1] = c - 1;
				}
				else
					return std::make_pair(std::shared_ptr<Node23>(), len);
				
				auto it = forkMap.find(currPos);
				if (it != forkMap.end())
					return std::make_pair(it->second, len);
			}
		};
		
		const auto& pos = mapPair.first;
		size_t r = pos[0];
		size_t c = pos[1];
		if (r + 1 < map.size() && map[r + 1][c] != '#')
		{
			auto p = continueToNextFork(std::array<size_t, 2>{r + 1, c}, pos);
			if (p.first)
			{
				mapPair.second->children.push_back(p.first);
				mapPair.second->len.push_back(p.second + 1);
			}
		}
		if (r > 0 && map[r - 1][c] != '#')
		{
			auto p = continueToNextFork(std::array<size_t, 2>{r - 1, c}, pos);
			if (p.first)
			{
				mapPair.second->children.push_back(p.first);
				mapPair.second->len.push_back(p.second + 1);
			}
		}
		if (c + 1 < map[r].size() && map[r][c + 1] != '#')
		{
			auto p = continueToNextFork(std::array<size_t, 2>{r, c + 1}, pos);
			if (p.first)
			{
				mapPair.second->children.push_back(p.first);
				mapPair.second->len.push_back(p.second + 1);
			}
		}
		if (c > 0 && map[r][c - 1] != '#')
		{
			auto p = continueToNextFork(std::array<size_t, 2>{r, c - 1}, pos);
			if (p.first)
			{
				mapPair.second->children.push_back(p.first);
				mapPair.second->len.push_back(p.second + 1);
			}
		}
	}
	
	return std::array<std::shared_ptr<Node23>, 2>{forkMap[start], forkMap[goal]};
}


void recurse23b(std::shared_ptr<Node23> node, std::shared_ptr<Node23> tgt, unsigned len, unsigned& maxLen)
{
	if (node == tgt)
	{
		maxLen = std::max(maxLen, len);
		return;
	}
	
	node->visited = true;
	for (size_t k = 0; k < node->children.size(); ++k)
		if (!node->children[k]->visited)
			recurse23b(node->children[k], tgt, len + node->len[k], maxLen);
	node->visited = false;
}


template <>
void executeDay<23>(const std::string& fn)
{
	// parse input
	std::ifstream infile(fn.c_str());
	
	std::vector<std::string> map;
	std::string s;
	while (infile >> s)
		map.emplace_back(std::move(s));


	// part a
	size_t colStart = std::distance(map[0].begin(), std::find(map[0].begin(), map[0].end(), '.'));
	size_t colGoal = std::distance(map.back().begin(), std::find(map.back().begin(), map.back().end(), '.'));
	std::array<size_t, 2> start{0, colStart};
	std::array<size_t, 2> goal{map.size() - 1, colGoal};
	
	unsigned resA = 0;
	std::set<std::array<size_t, 2>> path;
	recurse23a(map, path, start, goal, 0, resA);

	
	// part b
	auto startGoal = makeForkGraph23(map, start, goal);
	
	unsigned resB = 0;
	recurse23b(startGoal[0], startGoal[1], 0, resB);

	
	writeSolution(resA, resB);
}


