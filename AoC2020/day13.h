/*
 * day013.h
 *
 *  Created on: 2020-12-13
 *      Author: mbreit
 */


template <>
void executeDay<13>(const std::string& fn)
{
	// part a
	std::size_t resA = 0;
	std::vector<int64_t> busIDs = {13, 41, 467, 19, 17, 29, 353, 37, 23};
	int start = 1008713;

	for (int i = start; i < start+467; ++i)
	{
		for (int j = 0; j < 9; ++j)
			if (i % busIDs[j] == 0)
			{
				resA = (i-start) * busIDs[j];
				goto haveResA;
			}
	}

haveResA:


	// part b
	std::vector<int64_t> offsets = {0, 3, 13, 25, 30, 42, 44, 50, 67};

	int64_t resB = busIDs[0];
	int64_t fac = resB;
	for (int j = 1; j < 9; ++j)
	{
		offsets[j] = busIDs[j] - offsets[j] % busIDs[j];

		int64_t nextFac = fac * busIDs[j];
		for (int64_t k = resB; k <= nextFac; k += fac)
		{
			if (k % busIDs[j] == offsets[j])
			{
				resB = k;
				break;
			}
		}
		fac = nextFac;
	}


	writeSolution(resA, resB);
}


