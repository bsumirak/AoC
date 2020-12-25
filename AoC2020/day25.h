/*
 * day25.h
 *
 *  Created on: 2020-12-25
 *      Author: mbreit
 */


template <>
void executeDay<25>(const std::string& fn)
{
	// read input
	uint64_t cardKey = 16616892;
	uint64_t doorKey = 14505727;

	// part a
	unsigned cnt = 0;
	uint64_t k = 1;
	while (k != cardKey)
	{
		k = (k * 7) % 20201227;
		++cnt;
	}

	uint64_t resA = 1;
	for (unsigned i = 0; i < cnt; ++i)
		resA = (resA * doorKey) % 20201227;


	writeSolution(resA, 0);
}


