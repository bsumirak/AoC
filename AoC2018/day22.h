/*
 * day22.h
 *
 *  Created on: 22.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<22>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::map<std::pair<int, int>, bool> mem;

	std::string line;
	int row = 0;
	int col = 0;
	while (std::getline(infile, line))
	{
		for (col = 0; col < (int) line.size(); ++col)
			if (line[col] == '#')
				mem[std::make_pair(row, col)] = true;
			else
				mem[std::make_pair(row, col)] = false;

		++row;
	}

	col = row / 2;
	row = col;

	int dir = 0;
	int infCnt = 0;
	std::pair<int, int> entry = std::make_pair(row, col);
	for (int i = 0; i < 10000; ++i)
	{
		if (mem[entry])
			dir = (dir+1)%4;
		else
		{
			dir = (dir+3)%4;
			++infCnt;
		}
		mem[entry] = !mem[entry];

		switch (dir)
		{
			case 0: entry.first -= 1; break;
			case 1: entry.second += 1; break;
			case 2: entry.first += 1; break;
			case 3: entry.second -= 1; break;
			default: std::cout << "bad direction " << dir << std::endl; throw;
		}
	}


	std::map<std::pair<int, int>, int> mem2;

	row = 0;
	col = 0;
	std::ifstream infile2(fn.c_str());
	while (std::getline(infile2, line))
	{
		for (col = 0; col < (int) line.size(); ++col)
			if (line[col] == '#')
				mem2[std::make_pair(row, col)] = 3;
			else
				mem2[std::make_pair(row, col)] = 0;

		++row;
	}

	col = row / 2;
	row = col;

	dir = 0;
	int infCnt2 = 0;
	entry = std::make_pair(row, col);
	for (int i = 0; i < 10000000; ++i)
	{
		if (mem2[entry] == 3)
		{
			dir = (dir+1)%4;
			mem2[entry] = 1;
		}
		else if (mem2[entry] == 0)
		{
			dir = (dir+3)%4;
			mem2[entry] = 2;
		}
		else if (mem2[entry] == 1)
		{
			dir = (dir+2)%4;
			mem2[entry] = 0;
		}
		else if (mem2[entry] == 2)
		{
			mem2[entry] = 3;
			++infCnt2;
		}

		switch (dir)
		{
			case 0: entry.first -= 1; break;
			case 1: entry.second += 1; break;
			case 2: entry.first += 1; break;
			case 3: entry.second -= 1; break;
			default: std::cout << "bad direction " << dir << std::endl; throw;
		}
	}

	writeSolution(infCnt, infCnt2);
}


