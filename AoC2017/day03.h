/*
 * day03.h
 *
 *  Created on: 03.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<3>(const std::string& fn)
{
	// part a - solved using only calculator
	int sola = 326;

	// part b
	int x = 0;
	int y = 0;
	int n = 1;
	int resolution = 11; // looking at the solution, 11 would suffice
	int hr = (resolution-1)/2;
	std::vector<std::vector<int> > mem(resolution);
	for (size_t i = 0; i < resolution; ++i)
		mem[i].resize(resolution,0);
	mem[hr][hr] = 1;
	int solb = -1;

	while (true)
	{
		if (y <= x && y <= -x) // new ring and lower side
			x += 1;
		else if (y < x && y >= -x) // right side
			y += 1;
		else if (y >= x && y > -x) // upper side
			x -= 1;
		else
			y -= 1;

		mem[x+hr][y+hr] += mem[x+hr-1][y+hr+1] + mem[x+hr][y+hr+1] + mem[x+hr+1][y+hr+1]
						 + mem[x+hr-1][y+hr] + mem[x+hr][y+hr] + mem[x+hr+1][y+hr]
						 + mem[x+hr-1][y+hr-1] + mem[x+hr][y+hr-1] + mem[x+hr+1][y+hr-1];

		if (mem[x+hr][y+hr] > 361527)
		{
			solb = mem[x+hr][y+hr];
			break;
		}
		if (x == hr-1 && y == -(hr-1))
			break; // for mem safety;
	}

	writeSolution(sola, solb);
}


