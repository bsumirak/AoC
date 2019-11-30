/*
 * day15.h
 *
 *  Created on: 15.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<15>(const std::string& fn)
{
	int64_t genA = 512;
	int64_t genB = 191;

	// part a
	size_t judgeCntA = 0;
	for (size_t i = 0; i < 40000000; ++i)
	{
		genA *= 16807;
		genA = genA % (int64_t) 2147483647;

		genB *= 48271;
		genB = genB % (int64_t) 2147483647;

		int16_t a = genA;
		int16_t b = genB;

		if (a == b) ++judgeCntA;
	}

	// reset generators for part b
	genA = 512;
	genB = 191;
	size_t judgeCntB = 0;
	for (size_t i = 0; i < 5000000; ++i)
	{
		do
		{
			genA *= 16807;
			genA = genA % (int64_t) 2147483647;
		}
		while (genA % 4 != 0);

		do
		{
			genB *= 48271;
			genB = genB % (int64_t) 2147483647;
		}
		while (genB % 8 != 0);

		int16_t a = genA;
		int16_t b = genB;

		if (a == b) ++judgeCntB;
	}

	writeSolution(judgeCntA, judgeCntB);
}


