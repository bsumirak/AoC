/*
 * day10.h
 *
 *  Created on: 2018-12-10
 *      Author: mbreit
 */


template <>
void executeDay<10>(const std::string& fn)
{
	// part a
	int solb;

	// read input
	std::ifstream infile(fn.c_str());

	std::vector<std::pair<int, int> > vPos;
	std::vector<std::pair<int, int> > vVel;
	int x1, x2;
	while (infile >> x1)
	{
		infile >> x2;
		vPos.push_back(std::make_pair(x2, x1));

		infile >> x1;
		infile >> x2;
		vVel.push_back(std::make_pair(x2, x1));
	}
	const int sz = vPos.size();


	// part a and b together
	for (int i = 0; i < 11000; ++i)
	{
		int minX = 100000;
		int maxX = -100000;
		int minY = 100000;
		int maxY = -100000;

		for (int k = 0; k < sz; ++k)
		{
			vPos[k].first += vVel[k].first;
			vPos[k].second += vVel[k].second;

			if (vPos[k].first < minY)
				minY = vPos[k].first;
			if (vPos[k].first > maxY)
				maxY = vPos[k].first;
			if (vPos[k].second < minX)
				minX = vPos[k].second;
			if (vPos[k].second > maxX)
				maxX = vPos[k].second;
		}

		if (maxY - minY < 15)
		{
			std::sort(vPos.begin(), vPos.end());

			int cur = 0;
			for (int y = minY; y <= maxY; ++y)
			{
				for (int x = minX; x <= maxX; ++x)
				{
					if (vPos[cur].first == y && vPos[cur].second == x)
					{
						std::cout << "#";
						while (cur < sz && vPos[cur].first == y && vPos[cur].second == x)
							++cur;
					}
					else
					{
						std::cout << " ";
					}
				}
				std::cout << std::endl;
			}

			solb = i + 1;
			break;
		}
	}


	writeSolution("", solb);
}


