/*
 * day17.h
 *
 *  Created on: 2018-12-25
 *      Author: mbreit
 */



template <>
void executeDay<17>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());

	std::vector<std::pair<int, std::pair<int, int> > > hVeins;
	std::vector<std::pair<int, std::pair<int, int> > > vVeins;

	int minX = std::numeric_limits<int>::max();
	int maxX = std::numeric_limits<int>::min();
	int minY = std::numeric_limits<int>::max();
	int maxY = std::numeric_limits<int>::min();

	char tmp;
	while (infile >> tmp)
	{
		std::pair<int, std::pair<int, int> >* vein = NULL;
		if (tmp == 'x')
		{
			vVeins.resize(vVeins.size() + 1);
			vein = &vVeins.back();
		}
		else
		{
			hVeins.resize(hVeins.size() + 1);
			vein = &hVeins.back();
		}

		infile >> vein->first;
		infile >> vein->second.first;
		infile >> vein->second.second;

		if (tmp == 'x')
		{
			minX = std::min(minX, vein->first-1);
			maxX = std::max(maxX, vein->first+1);
			minY = std::min(minY, vein->second.first);
			maxY = std::max(maxY, vein->second.second);
		}
		else
		{
			minY = std::min(minY, vein->first);
			maxY = std::max(maxY, vein->first);
			minX = std::min(minX, vein->second.first-1);
			maxX = std::max(maxX, vein->second.second+1);
		}
	}

	// create scan field
	const size_t nCols = maxX-minX+1;
	const size_t nRows = maxY-minY+1;
	std::vector<std::string> scan(nRows);
	for (size_t i = 0; i < nRows; ++i)
		scan[i] = std::string(nCols, ' ');

	for (size_t i = 0; i < hVeins.size(); ++i)
	{
		std::string& row = scan[hVeins[i].first - minY];
		const int colStart = hVeins[i].second.first - minX;
		const int colEnd = hVeins[i].second.second - minX;
		for (size_t j = colStart; j <= colEnd; ++j)
			row[j] = '#';
	}
	for (size_t i = 0; i < vVeins.size(); ++i)
	{
		const size_t col = vVeins[i].first - minX;
		const int rowStart = vVeins[i].second.first - minY;
		const int rowEnd = vVeins[i].second.second - minY;
		for (size_t j = rowStart; j <= rowEnd; ++j)
			scan[j][col] = '#';
	}

	scan[0][500-minX] = '|';
	size_t cnt = 1;
	size_t cnt2 = 0;
	std::pair<int, int>* root = new std::pair<int, int>(500, minY);
	std::stack<std::pair<int, int>*> stack;
	stack.push(root);
	while (!stack.empty())
	{
		std::pair<int, int>* c = stack.top();
		stack.pop();

		int& x = c->first;
		int& y = c->second;

		while (y < maxY && scan[y+1-minY][x-minX] == ' ')
		{
			scan[y+1-minY][x-minX] = '|';
			++cnt;
			++y;
		}

		if (y == maxY || scan[y+1-minY][x-minX] == '|')
		{
			delete c;
			continue;
		}

		while (true)
		{
			int xl = x;
			while (xl > minX && scan[y-minY][xl-1-minX] != '#' && (scan[y+1-minY][xl-1-minX] == '#' || scan[y+1-minY][xl-1-minX] == '~'))
			{
				if (scan[y-minY][xl-1-minX] == ' ')
				{
					scan[y-minY][xl-1-minX] = '|';
					++cnt;
				};
				--xl;
			}
			int xr = x;
			while (xr < maxX && scan[y-minY][xr+1-minX] != '#' && (scan[y+1-minY][xr+1-minX] == '#' || scan[y+1-minY][xr+1-minX] == '~'))
			{
				if (scan[y-minY][xr+1-minX] == ' ')
				{
					scan[y-minY][xr+1-minX] = '|';
					++cnt;
				}
				++xr;
			}

			bool leftTrap = false;
			if (scan[y-minY][xl-1-minX] == '#')
				leftTrap = true;
			bool rightTrap = false;
			if (scan[y-minY][xr+1-minX] == '#')
				rightTrap = true;
			if (leftTrap && rightTrap)
			{
				for (int i = xl; i <= xr; ++i)
				{
					scan[y-minY][i-minX] = '~';
					++cnt2;
					if (scan[y-1-minY][i-minX] == '|')
						x = i;
				}
				--y;

				continue;
			}

			if (scan[y-minY][xl-1-minX] == ' ')
			{
				scan[y-minY][xl-1-minX] = '|';
				++cnt;
				stack.push(new std::pair<int, int>(xl-1, y));
			}
			if (scan[y-minY][xr+1-minX] == ' ')
			{
				scan[y-minY][xr+1-minX] = '|';
				++cnt;
				stack.push(new std::pair<int, int>(xr+1, y));
			}

			break;
		}

		delete c;
	}

	/*
	// print map
	for (size_t i = 0; i < nRows; ++i)
		std::cout << scan[i] << std::endl;
	 */

	writeSolution(cnt, cnt2);
}


