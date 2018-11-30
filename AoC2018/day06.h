/*
 * day06.h
 *
 *  Created on: 06.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<6>(const std::string& fn)
{
	// part a and b together (and really brute force)
	int tmp[] = {14, 0, 15, 12, 11, 11, 3, 5, 1, 6, 8, 4, 9, 1, 8, 4};
	std::vector<int> mem(tmp, tmp+16);
	std::vector<std::vector<int> > allStates;
	allStates.reserve(1000);
	allStates.push_back(mem);

	int na = 1;
	int nb;
	while (true)
	{
		// find slot with max.
		int max = mem[0];
		size_t maxInd = 0;
		for (size_t i = 1; i < 16; ++i)
		{
			if (mem[i] > max)
			{
				max = mem[i];
				maxInd = i;
			}
		}

		// distribute
		int forAll = max / 16;
		int rest = max % 16;

		for (size_t i = 0; i < 16; ++i)
			mem[i] += forAll;

		for (size_t i = maxInd+1; i < maxInd+1+rest; ++i)
			++mem[i%16];

		mem[maxInd] = forAll;

		// check reoccurrence
		bool reocc = false;
		for (size_t i = 0; i < allStates.size(); ++i)
		{
			bool same = true;
			for (size_t j = 0; j < 16; ++j)
			{
				if (allStates[i][j] != mem[j])
				{
					same = false;
					break;
				}
			}

			if (same)
			{
				reocc = true;
				nb = na - i;
				break;
			}
		}

		if (reocc) break;

		// save and inc
		allStates.push_back(mem);
		++na;
	}

	writeSolution(na, nb);
}


