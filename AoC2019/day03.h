/*
 * day03.h
 *
 *  Created on: 03.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<3>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());
	std::size_t claims[4*1373];
	std::size_t i = 0;
	while (infile >> claims[i])
		++i;

	// part a, b
	std::vector<std::size_t> inchClaims(1000000,0);
	for (std::size_t i = 0; i < 1373; ++i)
		for (std::size_t j = 0; j < claims[4*i+2]; ++j)
			for (std::size_t k = 0; k < claims[4*i+3]; ++k)
				++inchClaims[(claims[4*i+1]+k)*1000 + claims[4*i]+j];


	std::size_t suma = 0;
	for (std::size_t i = 0; i < 1000000; ++i)
		if (inchClaims[i] >= 2)
			++suma;


	// part b
	std::size_t nonOverlappingClaim = (std::size_t)-1;
	for (std::size_t i = 0; i < 1373; ++i)
	{
		bool nonOverlapping = true;
		for (std::size_t j = 0; j < claims[4*i+2]; ++j)
		{
			for (std::size_t k = 0; k < claims[4*i+3]; ++k)
			{
				if (inchClaims[(claims[4*i+1]+k)*1000 + claims[4*i]+j] > 1)
				{
					nonOverlapping = false;
					j = claims[4*i+2];
					break;
				}
			}
		}
		if (nonOverlapping)
		{
			nonOverlappingClaim = i;
			std::cout << i << std::endl;
		}
	}


	writeSolution(suma, nonOverlappingClaim+1);
}


