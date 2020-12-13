/*
 * day02.h
 *
 *  Created on: 2020-12-02
 *      Author: mbreit
 */


template <>
void executeDay<2>(const std::string& fn)
{
	// read input
	int resA = 0;
	int resB = 0;

	std::ifstream infile(fn.c_str());
	std::string line;
	char c, bla;
	std::string pw, blub;
	int min, max;
	while (std::getline(infile, line))
	{
		// parse input line
		std::istringstream iss(line);
		iss >> min;
		iss >> blub;
		iss >> max;
		iss >> c;
		iss >> bla;
		iss >> pw;


		// part a
		int cnt = 0;
		const std::size_t sz = pw.size();
		for (size_t i = 0; i < sz; ++i)
			if (pw[i] == c)
				++cnt;
		if (cnt >= min && cnt <= max)
			++resA;

		// part b
		if ((pw[min-1] == c) ^ (pw[max-1] == c))
			++resB;
	}

	writeSolution(resA, resB);
}


