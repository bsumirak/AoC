/*
 * day04.h
 *
 *  Created on: 2022-12-04
 *      Author: mbreit
 */


template <>
void executeDay<4>(const std::string& fn)
{
	// read input
	unsigned l1, l2, r1, r2;
	std::ifstream infile(fn.c_str());
	unsigned resA = 0;
	unsigned resB = 0;
	while (infile >> l1)
	{
		infile >> r1;
		infile >> l2;
		infile >> r2;

		if ((l1 <= l2 && r1 >= r2) || (l1 >= l2 && r1 <= r2))
			++resA;
		if (l1 <= r2 && r1 >= l2)
			++resB;
	}

	writeSolution(resA, resB);
}


