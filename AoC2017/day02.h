/*
 * day02.h
 *
 *  Created on: 02.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<2>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::string line;
	int suma = 0;
	int sumb = 0;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int n = 0;
		int tmp;
		int min = std::numeric_limits<int>::max();
		int max = std::numeric_limits<int>::min();
		while (iss >> tmp)
		{
			++n;

			// part a
			if (tmp > max)
				max = tmp;
			if (tmp < min)
				min = tmp;

			// part b
			std::istringstream iss2(line);
			int m = 0;
			int tmp2;
			while (iss2 >> tmp2)
			{
				++m;
				if (m == n) continue;

				if (tmp%tmp2 == 0)
				{
					sumb += tmp / tmp2;
					//std::cout << "adding " << tmp << " / " << tmp2 << std::endl;
				}
			}
		}
		suma += max - min;
	}

	writeSolution(suma, sumb);
}


