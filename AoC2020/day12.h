/*
 * day12.h
 *
 *  Created on: 2020-12-12
 *      Author: mbreit
 */


template <>
void executeDay<12>(const std::string& fn)
{
	int x = 0;
	int y = 0;
	int x1 = 0;
	int y1 = 0;
	int v = 10;
	int w = 1;

	std::ifstream infile(fn.c_str());
	char c;
	int d;
	std::string line;
	int o = 0;
	while (std::getline(infile, line))
	{
		// read input
		std::istringstream iss(line);
		iss >> c;
		iss >> d;

		// part a
		switch (c)
		{
			case 'E': x += d; break;
			case 'W': x -= d; break;
			case 'N': y += d; break;
			case 'S': y -= d; break;
			case 'L': o = (o + d/90) % 4; break;
			case 'R': o = (o + 4 - d/90) % 4; break;
			case 'F':
				x -= d * ((o-1) % 2);
				y -= d * ((o-2) % 2);
		}


		// part b
		switch (c)
		{
			case 'E': v += d; break;
			case 'W': v -= d; break;
			case 'N': w += d; break;
			case 'S': w -= d; break;
			case 'L':
				for (int i = 0; i < d/90; ++i)
				{
					int z = w;
					w = v;
					v = -z;
				}
				break;
			case 'R':
				for (int i = 0; i < d/90; ++i)
				{
					int z = w;
					w = -v;
					v = z;
				}
				break;
			case 'F':
				x1 += d * v;
				y1 += d * w;
		}
	}
	infile.close();


	int resA = abs(x) + abs(y);
	int resB = abs(x1) + abs(y1);


	writeSolution(resA, resB);
}


