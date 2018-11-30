/*
 * day13.h
 *
 *  Created on: 13.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<13>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::string line;

	std::map<int, int> scanRange;

	int maxDepth = -1;

	// read data
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		std::string depth;
		iss >> depth;
		depth = depth.substr(0, depth.size()-1);
		int depthInt= atoi(depth.c_str());

		int range;
		iss >> range;


		scanRange[depthInt] = range;
		maxDepth = std::max(depthInt, maxDepth);
	}

	// part a
	int sola = 0;
	std::map<int, int>::const_iterator it = scanRange.begin();
	std::map<int, int>::const_iterator itEnd = scanRange.end();
	for (; it != itEnd; ++it)
	{
		int d = it->first;
		int r = it->second;
		if (d % (2*(r - 1)) == 0)
			sola += d * it->second;
	}

	// part b (brute force; one might be able to save quite some time
	//         using Chinese remainder thm. or something similar)
	int delay = 0;
	while (true)
	{
		bool caught = false;
		it = scanRange.begin();
		for (; it != itEnd; ++it)
		{
			int d = it->first;
			int r = it->second;
			if ((d+delay) % (2*(r - 1)) == 0)
			{
				caught = true;
				break;
			}
		}

		if (!caught)
			break;
		else
			++delay;
	}

	writeSolution(sola, delay);
}
