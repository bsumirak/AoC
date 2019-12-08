/*
 * day08.h
 *
 *  Created on: 08.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<8>(const std::string& fn)
{
	// read data
	std::ifstream infile(fn.c_str());
	std::string pic;
	infile >> pic;
	std::size_t nLayers = pic.size() / std::size_t(150);


	// part a
	std::size_t nMinZero = 150;
	std::size_t nMin1 = 0;
	std::size_t nMin2 = 0;
	for (std::size_t l = 0; l < nLayers; ++l)
	{
		std::size_t n0 = 0;
		std::size_t n1 = 0;
		std::size_t n2 = 0;
		for (std::size_t r = 0; r < std::size_t(6); ++r)
		{
			for (std::size_t c = 0; c < std::size_t(25); ++c)
			{
				switch (pic[150*l + 25*r + c])
				{
					case '0':
						++n0; break;
					case '1':
						++n1; break;
					case '2':
						++n2; break;
					default:
						break;
				}
			}
		}

		if (n0 < nMinZero)
		{
			nMinZero = n0;
			nMin1 = n1;
			nMin2 = n2;
		}
	}
	std::size_t sola = nMin1 * nMin2;
	std::cout << "part 1: " << sola << std::endl;


	// part b
	std::cout << "part 2: " << std::endl;
	for (std::size_t r = 0; r < std::size_t(6); ++r)
	{
		for (std::size_t c = 0; c < std::size_t(25); ++c)
		{
			std::size_t l = 0;
			while (pic[150*l + 25*r + c] == '2')
				++l;

			switch (pic[150*l + 25*r + c])
			{
				case '0':
					std::cout << " "; break;
				case '1':
					std::cout << "*"; break;
				default:
					break;
			}
		}
		std::cout << std::endl;
	}
}


