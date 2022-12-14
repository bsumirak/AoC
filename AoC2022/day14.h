/*
 * day14.h
 *
 *  Created on: 2022-12-14
 *      Author: mbreit
 */


template <>
void executeDay<14>(const std::string& fn)
{
	// read input
	const unsigned width = 700;
	const unsigned height = 500;
	std::vector<bool> cave(width*height, false);
	std::ifstream infile(fn.c_str());
	std::string line;
	unsigned maxY = 0;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		unsigned x, y;
		unsigned prevX;
		unsigned prevY;
		iss >> prevX;
		iss >> prevY;
		maxY = std::max(maxY, prevY);
		while (iss >> x)
		{
			iss >> y;
			maxY = std::max(maxY, y);

			if (x == prevX)
				for (unsigned j = std::min(y, prevY); j <= std::max(y, prevY); ++j)
					cave[width*j + x] = true;
			else if (y == prevY)
				for (unsigned j = std::min(x, prevX); j <= std::max(x, prevX); ++j)
					cave[width*y + j] = true;
			else
				std::cout << "blub" << std::endl;

			prevX = x;
			prevY = y;
		}
	}
	infile.close();

	assert(maxY < 500);
	assert(width > 500 + maxY + 2);

	/*
	std::cout << std::string(20, ' ') << '*' << std::string(20, ' ') << std::endl;
	for (unsigned y = 1; y < 40; ++y)
	{
		for (unsigned x = 480; x < width; ++x)
			std::cout << (cave[width*y + x] ? '#' : ' ');
		std::cout << std::endl;
	}
	*/

	// part a
	unsigned resA = 0;
	unsigned cnt = 0;
	while (true)
	{
		if (cave[height])
			break;

		unsigned x = height;
		unsigned y = 0;
		while (true)
		{
			if (y == maxY + 1)
			{
				if (resA == 0)
					resA = cnt;
				break;
			}

			unsigned test = width * (y + 1) + x;
			if (!cave[test])
			{
				++y;
				continue;
			}

			if (!cave[test - 1])
			{
				++y;
				--x;
				continue;
			}

			if (!cave[test + 1])
			{
				++y;
				++x;
				continue;
			}

			break;
		}

		cave[width*y + x] = true;
		++cnt;
	}

	// part b
	unsigned resB = cnt;

	writeSolution(resA, resB);
}


