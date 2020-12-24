/*
 * day24.h
 *
 *  Created on: 2020-12-24
 *      Author: mbreit
 */


template <>
void executeDay<24>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());
	std::string line;

	std::map<std::pair<int, int>, bool> m;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		unsigned d;


		std::pair<int, int> c;
		while (iss >> d)
		{
			switch (d)
			{
				case 0: c.first += 1; break;
				case 1: c.second += 1; break;
				case 2: c.first -= 1; c.second += 1; break;
				case 3: c.first -= 1; break;
				case 4: c.second -= 1; break;
				case 5: c.first += 1; c.second -= 1; break;
			}
		}
		if (m.find(c) == m.end())
			m[c] = true;
		else
			m[c] = !m[c];
	}
	infile.close();


	// part a
	std::size_t resA = 0;
	for (auto e : m)
		if (e.second)
			++resA;


	// part b
	std::vector<std::vector<bool> > floor(300, std::vector<bool>(300, false));
	auto floorCpy = floor;
	for (auto e : m)
		if (e.second)
			floor[e.first.first + 150][e.first.second+150] = true;

	for (size_t i = 0; i < 100; ++i)
	{
		for (size_t x = 1; x < 299; ++x)
		{
			for (size_t y = 1; y < 299; ++y)
			{
				int cntB = 0;

				size_t nx = x;
				size_t ny = y;
				nx += 1;
				if (floor[nx][ny])
					++cntB;

				nx -= 1;
				ny += 1;
				if (floor[nx][ny])
					++cntB;

				nx -= 1;
				if (floor[nx][ny])
					++cntB;

				ny -= 1;
				if (floor[nx][ny])
					++cntB;

				nx += 1;
				ny -= 1;
				if (floor[nx][ny])
					++cntB;

				nx += 1;
				if (floor[nx][ny])
					++cntB;

				floorCpy[x][y] = floor[x][y];
				if (floor[x][y] && (cntB == 0 || cntB > 2))
					floorCpy[x][y] = false;
				else if (!floor[x][y] && cntB == 2)
					floorCpy[x][y] = true;
			}
		}
		floor.swap(floorCpy);
	}


	std::size_t resB = 0;
	for (size_t x = 1; x < 299; ++x)
		for (size_t y = 1; y < 299; ++y)
			if (floor[x][y])
				++resB;


	writeSolution(resA, resB);
}


