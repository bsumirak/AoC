/*
 * day02.h
 *
 *  Created on: 2022-12-02
 *      Author: mbreit
 */


template <>
void executeDay<2>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());
	char c;
	unsigned resA = 0;
	unsigned resB = 0;
	for (unsigned i = 0; i < 2500; ++i)
	{
		infile >> c;
		unsigned opp = c - 'A';
		infile >> c;
		unsigned my = c - 'X';

		// part a
		resA += my + 1u;
		resA += 3u * ((4u + my - opp) % 3u);

		// part b
		resB += 3u * my;
		resB += (opp + (my + 2u) % 3u) % 3u + 1u;
	}
	infile.close();

	writeSolution(resA, resB);
}


