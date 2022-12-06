/*
 * day06.h
 *
 *  Created on: 2022-12-06
 *      Author: mbreit
 */


template <>
void executeDay<6>(const std::string& fn)
{
	// read input
	std::string input;
	{
		std::ifstream infile(fn.c_str());
		infile >> input;
		infile.close();
	}
	const std::size_t sz = input.size();

	// part a
	size_t resA = 0;
	for (size_t i = 3; i < sz; ++i)
	{
		if (input[i] != input[i-1] && input[i] != input[i-2] && input[i] != input[i-3]
			&& input[i-1] != input[i-2] && input[i-1] != input[i-3] && input[i-2] != input[i-3])
		{
			resA = i+1;
			break;
		}
	}

	// part b
	size_t resB = 0;
	for (size_t i = 13; i < sz; ++i)
	{
		for (size_t j = 0; j < 13; ++j)
		{
			for (size_t k = 1; k < 14 - j; ++k)
			{
				if (input[i - j] == input[i - j - k])
				{
					goto hasDouble;
				}
			}
		}
		resB = i + 1;
		break;

hasDouble:
		continue;
	}

	writeSolution(resA, resB);
}


