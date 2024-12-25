/*
 * day25.h
 *
 *  Created on: 2024-12-25
 *      Author: mbreit
 */


template <>
void executeDay<25>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	uint64_t resA = 0u;
	uint64_t resB = 0u;

	std::vector<std::array<unsigned, 5>> keys;
	std::vector<std::array<unsigned, 5>> locks;


	std::string line;
	while (std::getline(infile, line))
	{
		bool isKey = line[0] == '.';
		std::array<unsigned, 5> size = {0, 0, 0, 0, 0};
		for (size_t k = 0; k < 5; ++k)
		{
			std::getline(infile, line);
			for (size_t l = 0; l < 5; ++l)
				if ((line[l] == '.' && !isKey) || (line[l] == '#' && isKey))
					++size[l];
		}
		std::getline(infile, line);
		std::getline(infile, line);

		if (isKey)
			keys.push_back(size);
		else
			locks.push_back(size);
	}

	for (auto& l : locks)
	{
		for (auto& k : keys)
		{
			bool overlap = false;
			for (size_t j = 0; j < 5; ++j)
			{
				if (k[j] > l[j])
				{
					overlap = true;
					break;
				}
			}
			if (!overlap)
				++resA;
		}
	}

	writeSolution(resA, resB);
}

