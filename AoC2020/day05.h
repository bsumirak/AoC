/*
 * day01.h
 *
 *  Created on: 2020-12-05
 *      Author: mbreit
 */


template <>
void executeDay<5>(const std::string& fn)
{
	// read input
	std::array<bool, 1024> seatTaken;
	memset(seatTaken.data(), 0, 1024*sizeof(bool));
	{
		std::ifstream infile(fn.c_str());
		std::string s;
		while (infile >> s)
		{
			int i = stoi(s, 0, 2);
			seatTaken[i] = true;
		}
		infile.close();
	}


	// part a
	std::size_t resA = 1024;
	while (!seatTaken[--resA])
		;

	// part b
	std::size_t resB = -1;
	while (!seatTaken[++resB])
		;
	while (seatTaken[++resB])
		;


	writeSolution(resA, resB);
}


