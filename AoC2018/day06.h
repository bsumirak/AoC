/*
 * day06.h
 *
 *  Created on: 2017-12-06
 *      Author: mbreit
 */


template <>
void executeDay<6>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());
	std::string line;
	std::vector<std::pair<int, int> > coords(50);
	std::size_t i = 0;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		iss >> coords[i].first;
		iss >> coords[i].second;
		++i;
	}

	// part a and b together
	std::vector<bool> invalid(50, false);
	std::vector<int> cnt(50,0);
	size_t numTotalDistLessThan10000 = 0;
	for (int i = 0; i < 800; ++i)
	{
		for (int j = 0; j < 800; ++j)
		{
			bool tied = false;
			int minDist = 20000;
			size_t minK = 0;
			size_t totalDist = 0;
			for (size_t k = 0; k < 50; ++k)
			{
				int dist = abs(coords[k].first - (i-200)) + abs(coords[k].second - (j-200));
				if (dist == minDist)
					tied = true;
				if (dist < minDist)
				{
					tied = false;
					minDist = dist;
					minK = k;
				}
				totalDist += dist;
			}

			if (!tied)
				++cnt[minK];

			// invalidate border owners (for they have infinite size)
			if (i == 0 || i == 799 || j == 0 || j == 799)
				invalid[minK] = true;

			if (totalDist < 10000)
				++numTotalDistLessThan10000;
		}
	}

	size_t maxSize = 0;
	for (size_t k = 0; k < 50; ++k)
	{
		if (cnt[k] > maxSize && !invalid[k])
			maxSize = cnt[k];
	}

	writeSolution(maxSize, numTotalDistLessThan10000);
}


