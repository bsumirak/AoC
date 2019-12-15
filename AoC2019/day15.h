/*
 * day13.h
 *
 *  Created on: 2019-12-15
 *      Author: mbreit
 */

#include "classes/intCodeMachine.h"

#include <stack>



template <>
void executeDay<15>(const std::string& fn)
{
	std::vector<int64_t> opCode;

	// read program
	{
		std::ifstream infile(fn.c_str());
		int64_t id;
		while (infile >> id)
			opCode.push_back(id);
	}

	const std::size_t mapSize = 45;


	// part a
	IntCodeMachine<int64_t> droid(opCode);
	droid.setMemorySize(100000);
	std::vector<int64_t> input(1);
	std::vector<int64_t> output;

	std::pair<int, int> startPos = std::make_pair(mapSize/2, mapSize/2);
	std::pair<int, int> curPos = startPos;
	std::pair<int, int> nextPos;
	std::pair<int, int> oxSys;

	std::vector<std::vector<int> > roomState(mapSize, std::vector<int>(mapSize, -1));
	roomState[curPos.second][curPos.first] = 1;

	std::stack<int> stack;
	stack.push(0);
	bool backtracking = false;

	// explore the map
	while (!stack.empty())
	{
		int& dir = stack.top();

		// if backtracking, step back
		if (backtracking)
		{
			switch (dir)
			{
				case 1:
					input[0] = 2;
					++curPos.second;
					break;
				case 2:
					input[0] = 1;
					--curPos.second;
					break;
				case 3:
					input[0] = 4;
					++curPos.first;
					break;
				case 4:
					input[0] = 3;
					--curPos.first;
					break;
			}
			output.clear();
			droid.execute(input, output);
		}

		// test next dir
		++dir;

		// all directions tested
		if (dir > 4)
		{
			stack.pop();
			backtracking = true;
			continue;
		}

		backtracking = false;

		// start stepping the droid
		bool unexplored = false;
		for (; dir <= 4; ++dir)
		{
			if (dir == 1)
				nextPos = std::make_pair(curPos.first, curPos.second-1);
			else if (dir == 2)
				nextPos = std::make_pair(curPos.first, curPos.second+1);
			else if (dir == 3)
				nextPos = std::make_pair(curPos.first-1, curPos.second);
			else if (dir == 4)
				nextPos = std::make_pair(curPos.first+1, curPos.second);

			unexplored = roomState[nextPos.second][nextPos.first] == -1;
			if (unexplored)
				break;
		}

		// no way to go
		if (!unexplored)
			continue;

		// do test
		input[0] = dir;
		output.clear();
		droid.execute(input, output);
		roomState[nextPos.second][nextPos.first] = output[0];

		// go there if possible
		if (output[0] == 1 || output[0] == 2)
		{
			// safety first
			switch (dir)
			{
				case 1:
					if (curPos.second == 0)
					{
						std::cout << "crossing northern border" << std::endl;
						throw std::runtime_error("");
					}
					--curPos.second;
					break;
				case 2:
					if (curPos.second == 1000)
					{
						std::cout << "crossing southern border" << std::endl;
						throw std::runtime_error("");
					}
					++curPos.second;
					break;
				case 3:
					if (curPos.first == 0)
					{
						std::cout << "crossing western border" << std::endl;
						throw std::runtime_error("");
					}
					--curPos.first;
					break;
				case 4:
					if (curPos.first == 1000)
					{
						std::cout << "crossing eastern border" << std::endl;
						throw std::runtime_error("");
					}
					++curPos.first;
					break;
			}

			curPos = nextPos;
			stack.push(0);

			// save possibly found oxygen system
			if (output[0] == 2)
				oxSys = curPos;
		}
	}

	// print map
#if 0
	for (std::size_t r = 0; r < mapSize; ++r)
	{
		for (std::size_t c = 0; c < mapSize; ++c)
		{
			switch (roomState[r][c])
			{
				case -1: std::cout << '?'; break;
				case 0: std::cout << '#'; break;
				case 1: std::cout << ' '; break;
				case 2: std::cout << 'x'; break;
			}
		}
		std::cout << std::endl;
	}
#endif

	// now find shortest path to oxygen system
	std::vector<std::vector<bool> > visited(mapSize, std::vector<bool>(mapSize, false));
	visited[startPos.second][startPos.first] = true;

	struct Path
	{
		Path(int _x, int _y, int _l) :
			x(_x), y(_y), l(_l) {}

		int x;
		int y;
		int l;
	};

	std::queue<Path> q;
	if (roomState[startPos.second-1][startPos.second] > 0)
		q.push(Path(startPos.second, startPos.second-1, 1));
	if (roomState[startPos.second+1][startPos.second] > 0)
		q.push(Path(startPos.second, startPos.second+1, 1));
	if (roomState[startPos.second][startPos.second-1] > 0)
		q.push(Path(startPos.second-1, startPos.second, 1));
	if (roomState[startPos.second][startPos.second+1] > 0)
		q.push(Path(startPos.second+1, startPos.second, 1));

	int sola = 0;
	while (!q.empty())
	{
		Path p = q.front();
		q.pop();

		if (visited[p.y][p.x])
			continue;

		visited[p.y][p.x] = true;

		if (p.x == oxSys.first && p.y == oxSys.second)
		{
			sola = p.l;
			break;
		}

		if (roomState[p.y-1][p.x] > 0 && !visited[p.y-1][p.x])
			q.push(Path(p.x, p.y-1, p.l+1));
		if (roomState[p.y+1][p.x] > 0 && !visited[p.y+1][p.x])
			q.push(Path(p.x, p.y+1, p.l+1));
		if (roomState[p.y][p.x-1] > 0 && !visited[p.y][p.x-1])
			q.push(Path(p.x-1, p.y, p.l+1));
		if (roomState[p.y][p.x+1] > 0 && !visited[p.y][p.x+1])
			q.push(Path(p.x+1, p.y, p.l+1));
	}


	// part b
	while (!q.empty())
		q.pop();

	{
		std::vector<std::vector<bool> > swap(mapSize, std::vector<bool>(mapSize, false));
		swap.swap(visited);
	}
	visited[oxSys.second][oxSys.first] = true;

	if (roomState[oxSys.second-1][oxSys.first] > 0)
		q.push(Path(oxSys.first, oxSys.second-1, 1));
	if (roomState[oxSys.second+1][oxSys.first] > 0)
		q.push(Path(oxSys.first, oxSys.second+1, 1));
	if (roomState[oxSys.second][oxSys.first-1] > 0)
		q.push(Path(oxSys.first-1, oxSys.second, 1));
	if (roomState[oxSys.second][oxSys.first+1] > 0)
		q.push(Path(oxSys.first+1, oxSys.second, 1));

	int solb = 0;
	while (!q.empty())
	{
		Path p = q.front();
		q.pop();

		if (visited[p.y][p.x])
			continue;

		solb = p.l;
		visited[p.y][p.x] = true;

		if (roomState[p.y-1][p.x] > 0 && !visited[p.y-1][p.x])
			q.push(Path(p.x, p.y-1, p.l+1));
		if (roomState[p.y+1][p.x] > 0 && !visited[p.y+1][p.x])
			q.push(Path(p.x, p.y+1, p.l+1));
		if (roomState[p.y][p.x-1] > 0 && !visited[p.y][p.x-1])
			q.push(Path(p.x-1, p.y, p.l+1));
		if (roomState[p.y][p.x+1] > 0 && !visited[p.y][p.x+1])
			q.push(Path(p.x+1, p.y, p.l+1));
	}

	writeSolution(sola, solb);
}


