/*
 * day17.h
 *
 *  Created on: 2023-12-17
 *      Author: mbreit
 */


template <>
void executeDay<17>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	
	std::vector<std::string> map;
	std::string line;
	while (infile >> line)
		map.emplace_back(std::move(line));

	
	// part a	
	struct State
	{
		State(unsigned _r, unsigned _c, unsigned _dir, unsigned _cnt, unsigned _heatLoss) :
		r(_r), c(_c), dir(_dir), cnt(_cnt), heatLoss(_heatLoss) {}
		
		unsigned r = 0;
		unsigned c = 0;
		unsigned dir = 0;
		unsigned cnt = 0;
		unsigned heatLoss = 0;
	};
	
	auto movePossible = [&](unsigned r, unsigned c, unsigned d)
	{
		switch (d)
		{
			case 0: return c + 1 < map[r].size();
			case 1: return r > 0;
			case 2: return c > 0;
			case 3: return r + 1 < map.size();
			default: return false;
		}
	};
	auto nextState = [&](State s)
	{
		++s.cnt;
		switch (s.dir)
		{
			case 0: ++s.c; break;
			case 1: --s.r; break;
			case 2: --s.c; break;
			case 3: ++s.r; break;
		}
		s.heatLoss += map[s.r][s.c] - '0';
		return s;
	};

	
	const auto findMinHeatLoss = [&](unsigned minStraight, unsigned maxStraight)
	{
		const unsigned sz = 4u * maxStraight;
		unsigned ret = std::numeric_limits<unsigned>::max();
		std::vector<unsigned> initMin(sz, std::numeric_limits<unsigned>::max());
		std::vector<std::vector<std::vector<unsigned>>> minLoss(map.size(),
			std::vector<std::vector<unsigned>>(map[0].size(), initMin));
		std::queue<State> q;
		q.push(State{0, 0, 0, 0, 0});
		while (!q.empty())
		{
			State state = q.front();
			q.pop();
		
			if (state.r + 1 == map.size() && state.c + 1 == map[state.r].size() && state.cnt > minStraight)
			{
				ret = std::min(ret, state.heatLoss);
				continue;
			}
			

			if (state.cnt < maxStraight && movePossible(state.r, state.c, state.dir))
			{
				auto next = nextState(state);
				if (next.heatLoss < minLoss[next.r][next.c][maxStraight * next.dir + next.cnt - 1])
				{
					minLoss[next.r][next.c][maxStraight * next.dir + next.cnt - 1] = next.heatLoss;
					q.push(next);
				}
			}
		
			state.dir = (state.dir + 1u) % 4u;
			if ((state.cnt == 0 || state.cnt > minStraight) && movePossible(state.r, state.c, state.dir))
			{
				state.cnt = 0;
				auto next = nextState(state);
				if (next.heatLoss < minLoss[next.r][next.c][maxStraight * next.dir + next.cnt - 1])
				{
					minLoss[next.r][next.c][maxStraight * next.dir + next.cnt - 1] = next.heatLoss;
					q.push(next);
				}
			}
		
			state.dir = (state.dir + 2u) % 4u;
			if ((state.cnt == 0 || state.cnt > minStraight) && movePossible(state.r, state.c, state.dir))
			{
				state.cnt = 0;
				auto next = nextState(state);
				if (next.heatLoss < minLoss[next.r][next.c][maxStraight * next.dir + next.cnt - 1])
				{
					minLoss[next.r][next.c][maxStraight * next.dir + next.cnt - 1] = next.heatLoss;
					q.push(next);
				}
			}
		}
		
		return ret;
	};
	
	unsigned resA = findMinHeatLoss(0, 3);
	unsigned resB = findMinHeatLoss(3, 10);
	
	writeSolution(resA, resB);
}


