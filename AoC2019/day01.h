/*
 * day01.h
 *
 *  Created on: 2019-12-01
 *      Author: mbreit
 */


template <>
void executeDay<1>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	int i;

	// part a
	int suma = 0;
	int sumb = 0;
	while (infile >> i)
	{
		i = i/3 - 2;
		suma += i;
		while (i > 8)
		{
			i /= 3;
			i -= 2;
			sumb += i;
		}
	}

	writeSolution(suma, suma + sumb);
}


