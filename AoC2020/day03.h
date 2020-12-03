/*
 * day01.h
 *
 *  Created on: 2020-12-03
 *      Author: mbreit
 */


template <>
void executeDay<3>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(infile, line))
		lines.push_back(line);
	std::size_t sz = lines.size();
	std::size_t nCols = lines[0].size();


	// part a
	std::size_t resA = 0;
	std::size_t currPos = 0;
	for (std::size_t i = 0; i < sz; ++i, currPos+=3)
	{
		if (lines[i][currPos % nCols] == '#')
			++resA;
	}

	// part b
	std::size_t resB = resA;

	std::vector<std::pair<std::size_t, std::size_t> > slopes;
	slopes.push_back(std::make_pair(1, 1));
	slopes.push_back(std::make_pair(1, 5));
	slopes.push_back(std::make_pair(1, 7));
	slopes.push_back(std::make_pair(2, 1));

	for (std::size_t n = 0; n < 4; ++n)
	{
		std::size_t tmp = 0;
		currPos = 0;
		for (std::size_t i = 0; i < sz; i += slopes[n].first, currPos += slopes[n].second)
		{
			if (lines[i][currPos % nCols] == '#')
				++tmp;
		}
		resB *= tmp;
	}

	writeSolution(resA, resB);
}


