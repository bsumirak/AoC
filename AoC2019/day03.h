/*
 * day03.h
 *
 *  Created on: 2019-12-03
 *      Author: mbreit
 */


template <>
void executeDay<3>(const std::string& fn)
{
	// read input
	std::array<std::vector<std::pair<int, int> >, 2> coords;
	std::array<std::vector<int>, 2> cumSteps;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		char dir;
		int dist;
		for (size_t i = 0; i < 2; ++i)
		{
			coords[i].push_back(std::make_pair(0,0));
			cumSteps[i].push_back(0);
			std::getline(infile, line);
			std::istringstream iss(line);
			while (iss >> dir)
			{
				iss >> dist;
				coords[i].push_back(coords[i].back());
				cumSteps[i].push_back(cumSteps[i].back() + dist);

				switch (dir)
				{
					case 'R':
						coords[i].back().first += dist;
						break;
					case 'L':
						coords[i].back().first -= dist;
						break;
					case 'U':
						coords[i].back().second += dist;
						break;
					case 'D':
						coords[i].back().second -= dist;
						break;
				}
			}
		}
	}


	// part a / b combined
	int minDist = std::numeric_limits<int>::max();
	int minSteps = std::numeric_limits<int>::max();

	const std::size_t sz0 = coords[0].size();
	const std::size_t sz1 = coords[1].size();
	for (std::size_t i = 1; i < sz0; ++i)
	{
		const std::pair<int, int>& pt00 = coords[0][i-1];
		const std::pair<int, int>& pt01 = coords[0][i];
		const bool seg0Horz = pt00.second == pt01.second;

		for (std::size_t j = 1; j < sz1; ++j)
		{
			const std::pair<int, int>& pt10 = coords[1][j-1];
			const std::pair<int, int>& pt11 = coords[1][j];

			const bool seg1Horz = pt10.second == pt11.second;
			if (seg0Horz && !seg1Horz)
			{
				int x = pt10.first;
				int y = pt00.second;
				if (((pt00.first <= x && x <= pt01.first) || (pt00.first >= x && x >= pt01.first))
					&& ((pt10.second <= y && y <= pt11.second) || (pt10.second >= y && y >= pt11.second)))
				{
					minDist = std::min(minDist, abs(x) + abs(y));
					const int steps0 = cumSteps[0][i-1] + abs(pt00.first - x);
					const int steps1 = cumSteps[1][j-1] + abs(pt10.second - y);
					minSteps = std::min(minSteps, steps0 + steps1);
				}
			}
			if (!seg0Horz && seg1Horz)
			{
				int x = pt00.first;
				int y = pt10.second;
				if (((pt10.first <= x && x <= pt11.first) || (pt10.first >= x && x >= pt11.first))
					&& ((pt00.second <= y && y <= pt01.second) || (pt00.second >= y && y >= pt01.second)))
				{
					minDist = std::min(minDist, abs(x) + abs(y));
					const int steps0 = cumSteps[0][i-1] + abs(pt00.second - y);
					const int steps1 = cumSteps[1][j-1] + abs(pt10.first - x);
					minSteps = std::min(minSteps, steps0 + steps1);
				}
			}
		}
	}

	writeSolution(minDist, minSteps);
}


