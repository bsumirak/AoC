/*
 * day15.h
 *
 *  Created on: 2020-12-15
 *      Author: mbreit
 */


template <>
void executeDay<15>(const std::string& fn)
{
	// input
	std::map<unsigned, unsigned> v;
	v[0] = 0;
	v[20] = 1;
	v[7] = 2;
	v[16] = 3;
	v[1] = 4;
	v[18] = 5;
	v[15] = 6;

	// part a
	unsigned resA = 0;
	unsigned resB = 0;
	for (size_t round = 7; round < 30000000-1; ++round)
	{
		auto it = v.find(resB);
		if (it == v.end())
		{
			v[resB] = round;
			resB = 0;
		}
		else
		{
			resB = round - it->second;
			it->second = round;
		}
		if (round == 2018)
			resA = resB;
	}


	writeSolution(resA, resB);
}


