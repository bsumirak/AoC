/*
 * day17.h
 *
 *  Created on: 2020-12-17
 *      Author: mbreit
 */


template <>
void executeDay<17>(const std::string& fn)
{
	// read input
	std::array<std::array<std::array<bool, 22>, 22>, 15> cubes;
	std::memset(cubes.data(), 0, 22*22*15*sizeof(bool));
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		size_t i = 7;
		while (std::getline(infile, line))
		{
			for (size_t j = 0; j < 8; ++j)
				cubes[7][i][j+7] = line[j] == '#';
			++i;
		}
		infile.close();
	}
	std::array<std::array<std::array<bool, 22>, 22>, 15> cubesCopy = cubes;


	// part a
	std::array<std::array<std::array<bool, 22>, 22>, 15> newCubes = cubes;
	for (size_t l = 0; l < 6; ++l)
	{
		for (size_t k = 6 - l; k < 9 + l; ++k)
		{
			for (size_t i = 6 - l; i < 16 + l; ++i)
			{
				for (size_t j = 6 - l; j < 16 + l; ++j)
				{
					size_t cnt = 0;
					for (size_t r = 0; r < 3; ++r)
						for (size_t s = 0; s < 3; ++s)
							for (size_t t = 0; t < 3; ++t)
								if (cubes[k+r-1][i+s-1][j+t-1])
									++cnt;
					if (!cubes[k][i][j] && cnt == 3)
						newCubes[k][i][j] = true;
					else if (cubes[k][i][j] && (cnt == 3 || cnt == 4))
						newCubes[k][i][j] = true;
					else
						newCubes[k][i][j] = false;
				}
			}
		}
		cubes.swap(newCubes);
	}

	size_t resA = 0;
	for (size_t k = 1; k < 14; ++k)
		for (size_t i = 1; i < 21; ++i)
			for (size_t j = 1; j < 21; ++j)
				if (cubes[k][i][j])
					++resA;


	// part b
	std::array<std::array<std::array<std::array<bool, 22>, 22>, 15>, 15> cubes2;
	std::memset(cubes2.data(), 0, 22*22*15*15*sizeof(bool));
	cubes2[7] = cubesCopy;

	std::array<std::array<std::array<std::array<bool, 22>, 22>, 15>, 15> newCubes2 = cubes2;
	for (size_t l = 0; l < 6; ++l)
	{
		for (size_t m = 6 - l; m < 9 + l; ++m)
		{
			for (size_t k = 6 - l; k < 9 + l; ++k)
			{
				for (size_t i = 6 - l; i < 16 + l; ++i)
				{
					for (size_t j = 6 - l; j < 16 + l; ++j)
					{
						size_t cnt = 0;
						for (size_t q = 0; q < 3; ++q)
							for (size_t r = 0; r < 3; ++r)
								for (size_t s = 0; s < 3; ++s)
									for (size_t t = 0; t < 3; ++t)
										if (cubes2[m+q-1][k+r-1][i+s-1][j+t-1])
											++cnt;
						if (!cubes2[m][k][i][j] && cnt == 3)
							newCubes2[m][k][i][j] = true;
						else if (cubes2[m][k][i][j] && (cnt == 3 || cnt == 4))
							newCubes2[m][k][i][j] = true;
						else
							newCubes2[m][k][i][j] = false;
					}
				}
			}
		}
		cubes2.swap(newCubes2);
	}


	size_t resB = 0;
	for (size_t m = 1; m < 14; ++m)
		for (size_t k = 1; k < 14; ++k)
			for (size_t i = 1; i < 21; ++i)
				for (size_t j = 1; j < 21; ++j)
					if (cubes2[m][k][i][j])
						++resB;


	writeSolution(resA, resB);
}


