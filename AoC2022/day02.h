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
	std::array<unsigned, 2500> opp;
	std::array<unsigned, 2500> my;

	std::ifstream infile(fn.c_str());
	char c;
	for (unsigned i = 0; i < 2500; ++i)
	{
		infile >> c;
		opp[i] = c - 'A';
		infile >> c;
		my[i] = c - 'X';
	}
	infile.close();

	// part a
	unsigned resA = 0;
	for (unsigned i = 0; i < 2500; ++i)
	{
		resA += my[i] + 1u;
		if (my[i] == opp[i])
			resA += 3;
		else if (my[i] == (opp[i] + 1u) % 3u)
			resA += 6;
	}

	// part b
	unsigned resB = 0;
	for (unsigned i = 0; i < 2500; ++i)
	{
		resB += 3u * my[i];
		resB += (opp[i] + (my[i] + 2u) % 3u) % 3u + 1u;
	}


	writeSolution(resA, resB);
}


