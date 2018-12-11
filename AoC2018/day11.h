/*
 * day11.h
 *
 *  Created on: 2018-12-11
 *      Author: mbreit
 */


template <>
void executeDay<11>(const std::string& fn)
{
	// input
	int serial = 1133;

	// write grid
	int grid[90000];
	for (int i = 0; i < 300; ++i)
	{
		for (int j = 0; j < 300; ++j)
		{
			int x = i + 10;
			int level = x*j;
			level += serial;
			level *= x;
			level /= 100;
			level = level % 10;
			level -= 5;
			grid[300*i+j] = level;
		}
	}


	// part a
	int maxSum = 0;
	int maxIDx = 0;
	int maxIDy = 0;
	for (int i = 0; i < 298; ++i)
	{
		for (int j = 0; j < 298; ++j)
		{
			int sum = 0;
			for (int k = 0; k < 3; ++k)
				for (int l = 0; l < 3; ++l)
					sum += grid[300*(i+k)+j+l];

			if (sum > maxSum)
			{
				maxSum = sum;
				maxIDx = i;
				maxIDy = j;
			}
		}
	}

	std::ostringstream ossa;
	ossa << maxIDx << "," << maxIDy;


	// part b
	maxSum = 0;
	maxIDx = 0;
	maxIDy = 0;
	int maxS = 0;
	for (int s = 1; s <= 300; ++s)
	{
		for (int i = 0; i < 301-s; ++i)
		{
			for (int j = 0; j < 301-s; ++j)
			{
				int sum = 0;
				for (int k = 0; k < s; ++k)
					for (int l = 0; l < s; ++l)
						sum += grid[300*(i+k)+(j+l)];

				if (sum > maxSum)
				{
					maxSum = sum;
					maxIDx = i;
					maxIDy = j;
					maxS = s;
				}
			}
		}
	}

	std::ostringstream ossb;
	ossb << maxIDx << "," << maxIDy << "," << maxS;


	writeSolution(ossa.str(), ossb.str());
}


