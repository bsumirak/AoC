/*
 * day14.h
 *
 *  Created on: 2020-12-14
 *      Author: mbreit
 */


template <>
void executeDay<14>(const std::string& fn)
{
	// read input
	std::map<uint64_t, uint64_t> mem;
	std::map<uint64_t, uint64_t> mem2;
	uint64_t ones = 0;
	uint64_t zeros = 0;
	std::vector<unsigned> floatingPos;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		std::string target;
		while (std::getline(infile, line))
		{
			std::istringstream iss(line);
			iss >> target;

			if (target == "mask")
			{
				// part a
				iss >> target;
				std::string mask0 =	target;
				std::replace(mask0.begin(), mask0.end(), 'X', '1');
				zeros = stoull(mask0, 0, 2);
				std::string mask1 =	target;
				std::replace(mask1.begin(), mask1.end(), 'X', '0');
				ones = stoull(mask1, 0, 2);


				// part b
				floatingPos.clear();
				std::size_t pos = 0;
				while ((pos = target.find_first_of('X', pos)) != std::string::npos)
				{
					floatingPos.push_back(35 - pos);
					++pos;
				}
			}

			else if (target == "mem")
			{
				// part a
				uint64_t a;
				iss >> a;
				uint64_t v;
				iss >> v;
				uint64_t v2 = v;
				v &= zeros;
				v |= ones;
				mem[a] = v;

				// part b
				a |= ones;
				std::bitset<36> bsA(a);
				const size_t num = 1 << floatingPos.size();
				for (size_t i = 0; i < num; ++i)
				{
					std::bitset<36> bsI(i);
					for (size_t j = 0; j < floatingPos.size(); ++j)
						bsA[floatingPos[j]] = bsI[j];
					mem2[bsA.to_ulong()] = v2;
				}
			}
		}
		infile.close();
	}


	// part a
	std::size_t resA = 0;
	for (auto& pair : mem)
		resA += pair.second;


	// part b
	std::size_t resB = 0;
	for (auto& pair : mem2)
		resB += pair.second;


	writeSolution(resA, resB);
}


