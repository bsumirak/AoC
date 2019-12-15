/*
 * day12.h
 *
 *  Created on: 2019-12-12
 *      Author: mbreit
 */

template <typename T>
T ggt(T a, T b)
{
	if (b > a)
		std::swap(a, b);
	T tmp;
	while (b)
	{
		tmp = b;
		b = a % b;
		a = tmp;
	}
	return a;
}

template <typename T>
T kgv(T a, T b)
{
	T g = ggt(a, b);
	return a*b/g;
}


template <>
void executeDay<12>(const std::string& fn)
{
	// read data
	std::array<std::array<int, 3>, 4> pos =
	{{ {{-5, 6, -11}}, {{-8, -4, -2}}, {{1, 16, 4}}, {{11, 11, -4}} }};
	std::array<std::array<int, 3>, 4> posCp = pos;

	std::array<std::array<int, 3>, 4> vel =
	{{ {{0, 0, 0,}}, {{0, 0, 0,}}, {{0, 0, 0,}}, {{0, 0, 0}} }};
	std::array<std::array<int, 3>, 4> velCp = vel;

	for (std::size_t i = 0; i < 1000; ++i)
	{
		for (std::size_t j = 0; j < 4; ++j)
		{
			for (std::size_t k = j+1; k < 4; ++k)
			{
				for (std::size_t l = 0; l < 3; ++l)
				{
					if (pos[j][l] > pos[k][l])
					{
						--vel[j][l];
						++vel[k][l];
					}
					else if (pos[j][l] < pos[k][l])
					{
						++vel[j][l];
						--vel[k][l];
					}
				}
			}
		}

		for (std::size_t j = 0; j < 4; ++j)
		{
			for (std::size_t l = 0; l < 3; ++l)
			{
				pos[j][l] += vel[j][l];
			}
		}
	}

	int sola = 0;
	for (std::size_t j = 0; j < 4; ++j)
	{
		int potE = 0;
		int kinE = 0;
		for (std::size_t l = 0; l < 3; ++l)
		{
			potE += abs(pos[j][l]);
			kinE +=  + abs(vel[j][l]);
		}
		sola += potE * kinE;
	}


	// part b
	pos = posCp;
	vel = velCp;

	int period[3] = {0, 0, 0};
	for (std::size_t l = 0; l < 3; ++l)
	{
		do
		{
			++period[l];
			for (std::size_t j = 0; j < 4; ++j)
			{
				for (std::size_t k = j+1; k < 4; ++k)
				{
					if (pos[j][l] > pos[k][l])
					{
						--vel[j][l];
						++vel[k][l];
					}
					else if (pos[j][l] < pos[k][l])
					{
						++vel[j][l];
						--vel[k][l];
					}
				}
			}
			for (std::size_t j = 0; j < 4; ++j)
				pos[j][l] += vel[j][l];
		}
		while (pos[0][l] != posCp[0][l] || pos[1][l] != posCp[1][l]
			|| pos[2][l] != posCp[2][l] || pos[3][l] != posCp[3][l]
			|| vel[0][l] != velCp[0][l] || vel[1][l] != velCp[1][l]
			|| vel[2][l] != velCp[2][l] || vel[3][l] != velCp[3][l]);
	}

	int64_t solb = kgv(int64_t(period[0]),
		kgv(int64_t(period[1]), int64_t(period[2])));


	writeSolution(sola, solb);
}


