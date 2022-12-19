/*
 * day19.h
 *
 *  Created on: 2022-12-19
 *      Author: mbreit
 */


struct Reservoir19
{
	std::array<unsigned, 4> rob{1, 0, 0, 0};
	std::array<unsigned, 4> mat{0, 0, 0, 0};
};


void findBestPlan19(const std::array<std::array<unsigned, 4>, 4>& bp, Reservoir19& res, unsigned& maxGeod, unsigned it = 24)
{
	unsigned maxReqOre = std::max(std::max(bp[1][0], bp[2][0]), bp[3][0]);

	// early exit?
	std::array<unsigned, 2> max = {res.mat[2], res.mat[3]};
	std::array<unsigned, 2> nr = {res.rob[2], res.rob[3]};
	for (unsigned i = it; i > 0; --i)
	{
		max[0] += nr[0];
		max[1] += nr[1];
		if (max[0] >= bp[3][2])
		{
			max[0] -= bp[3][2];
			++nr[1];
		}
		++nr[0];
	}
	if (max[1] <= maxGeod)
		return;

	while (it > 0)
	{
		std::array<bool, 4> canBuild;
		canBuild[3] = res.mat[0] >= bp[3][0] && res.mat[2] >= bp[3][2];
		canBuild[2] = res.mat[0] >= bp[2][0] && res.mat[1] >= bp[2][1] && res.rob[2] < bp[3][2];
		canBuild[1] = res.mat[0] >= bp[1][0] && res.rob[1] < bp[2][1];
		canBuild[0] = res.mat[0] >= bp[0][0] && res.rob[0] < maxReqOre;

		Reservoir19 resCp = res;
		for (unsigned k = 3; k < 4; --k)
		{
			if (!canBuild[k])
				continue;

			for (size_t l = 0; l < 4; ++l)
				res.mat[l] += res.rob[l] - bp[k][l];
			++res.rob[k];

			findBestPlan19(bp, res, maxGeod, it - 1);

			res = resCp;
		}

		for (size_t l = 0; l < 4; ++l)
			res.mat[l] += res.rob[l];

		--it;
	}

	maxGeod = std::max(maxGeod, res.mat[3]);
}


template <>
void executeDay<19>(const std::string& fn)
{

	// read input
	std::ifstream infile(fn.c_str());

	unsigned resA = 0;
	unsigned resB = 1;

	std::array<std::array<unsigned, 4>, 4> bp
	{
		std::array<unsigned, 4>{0,0,0,0},
		std::array<unsigned, 4>{0,0,0,0},
		std::array<unsigned, 4>{0,0,0,0},
		std::array<unsigned, 4>{0,0,0,0}
	};

	unsigned id;
	while (infile >> id)
	{
		infile >> bp[0][0];
		infile >> bp[1][0];
		infile >> bp[2][0];
		infile >> bp[2][1];
		infile >> bp[3][0];
		infile >> bp[3][2];

		Reservoir19 res;
		unsigned numProducibleGeodes = 0;
		findBestPlan19(bp, res, numProducibleGeodes, 24);
		resA += numProducibleGeodes * id;

		if (id <= 3)
		{
			Reservoir19 res2;
			findBestPlan19(bp, res2, numProducibleGeodes, 32);
			resB *= numProducibleGeodes;
		}
	}
	infile.close();


	writeSolution(resA, resB);
}


