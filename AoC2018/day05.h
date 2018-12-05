/*
 * day05.h
 *
 *  Created on: 2018-12-05
 *      Author: mbreit
 */



void collapsePolymer(std::string& poly)
{
	std::size_t i = 0;
	while (i < poly.size() - 1)
	{
		if (poly[i] == poly[i+1] + 32 || poly[i] == poly[i+1] - 32 )
		{
			poly.erase(i, 2);
			if (i>0)
				--i;
		}
		else
			++i;
	}
}


template <>
void executeDay<5>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	// read input
	std::string poly;
	infile >> poly;
	std::string copy = poly;

	// part a
	collapsePolymer(poly);
	std::size_t sola = poly.size();


	// part b
	std::size_t solb = copy.size();
	for (char c = 65; c < 91; ++c)
	{
		// remove all instances of c
		poly = copy;

		std::size_t i = 0;
		while (i < poly.size() - 1)
		{
			if (poly[i] == c + 32 || poly[i] == c )
				poly.erase(i, 1);
			else
				++i;
		}

		// remaining collapsed poly
		collapsePolymer(poly);
		if (poly.size() < solb)
			solb = poly.size();
	}

	writeSolution(sola, solb);
}


