/*
 * day23.h
 *
 *  Created on: 2019-01-06
 *      Author: mbreit
 */


struct NanoBot
{
	NanoBot(int x, int y, int z, uint _r)
	: r(_r)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}

	int pos[3];
	uint r;
};


template <>
void executeDay<23>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());

	std::vector<NanoBot> vNB;

	int tmp;
	uint maxR = 0;
	size_t maxInd = 0;
	while (infile >> tmp)
	{
		int y, z;
		uint r;
		infile >> y;
		infile >> z;
		infile >> r;
		vNB.push_back(NanoBot(tmp, y, z, r));

		if (r > maxR)
		{
			maxR = r;
			maxInd = vNB.size() - 1;
		}
	}
	const size_t nNB = vNB.size();


	// part a
	size_t nInRange = 0;
	for (size_t i = 0; i < nNB; ++i)
	{
		uint dist = abs(vNB[i].pos[0] - vNB[maxInd].pos[0]);
		dist += abs(vNB[i].pos[1] - vNB[maxInd].pos[1]);
		dist += abs(vNB[i].pos[2] - vNB[maxInd].pos[2]);
		if (dist <= vNB[maxInd].r)
			++nInRange;
	}


	writeSolution(nInRange, 0);
}


