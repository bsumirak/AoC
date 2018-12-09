/*
 * day09.h
 *
 *  Created on: 09.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<9>(const std::string& fn)
{
	// 468 players; last marble is worth 71010 points
	const int nPlayers = 468;
	const int nMarbles = 7101000;

	int maxa = 0;

	std::list<int> circle;

	std::list<int>::iterator curIt = circle.begin();
	curIt = circle.insert(curIt, 0);
	std::vector<int64_t> points(nPlayers, 0);
	std::vector<int64_t> overflowCounter(nPlayers, 0);
	for (int i = 1, p = 1; i <= nMarbles; ++i, p = (p+1)%nPlayers)
	{
		if (i%23 != 0)
		{
			for (int j = 0; j < 2; ++j)
			{
				++curIt;
				if (curIt == circle.end())
					curIt = circle.begin();
			}
			curIt = circle.insert(curIt, i);
		}
		else
		{
			for (int j = 0; j < 7; ++j)
			{
				if (curIt == circle.begin())
					curIt = circle.end();
				--curIt;
			}
			points[p] += i + *curIt;
			curIt = circle.erase(curIt);
			if (curIt == circle.end())
				curIt = circle.begin();
		}

		if (i == nMarbles / 100)
			for (int i = 0; i < nPlayers; ++i)
				if (maxa < points[i])
					maxa = points[i];
	}

	int64_t maxb = 0;
	for (int i = 0; i < nPlayers; ++i)
		if (maxb < points[i])
			maxb = points[i];

	// solution output
	writeSolution(maxa, maxb);
}


