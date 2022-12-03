/*
 * day03.h
 *
 *  Created on: 2022-12-03
 *      Author: mbreit
 */


template <>
void executeDay<3>(const std::string& fn)
{
	// read input
	std::vector<std::string> rucksacks;
	{
		std::ifstream infile(fn.c_str());
		std::string s;
		while (infile >> s)
			rucksacks.push_back(s);
		infile.close();
	}

	// part a
	unsigned resA = 0;
	for (const auto& r : rucksacks)
	{
		std::array<bool, 52> inventory;
		std::fill(inventory.begin(), inventory.end(), false);
		const size_t rsz = r.size();
		const size_t compSz = rsz / 2;
		for (size_t i = 0; i < compSz; ++i)
		{
			if (r[i] < 'a')
				inventory[(r[i] - 'A') + 26] = true;
			else
				inventory[r[i] - 'a'] = true;
		}
		size_t i = compSz;
		for (; i < rsz; ++i)
		{
			if (r[i] < 'a')
			{
				if (inventory[(r[i] - 'A') + 26])
				{
					resA += (r[i] - 'A') + 27;
					break;
				}
			}
			else if (inventory[r[i] - 'a'])
			{
				resA += (r[i] - 'a') + 1;
				break;
			}
		}
	}

	// part b
	const size_t numR = rucksacks.size();
	std::size_t resB = 0;
	for (size_t k = 0; k < numR; k += 3)
	{
		std::array<bool, 52> inventory;
		std::array<bool, 52> sharedInv;
		std::fill(sharedInv.begin(), sharedInv.end(), true);

		for (size_t g = 0; g < 3; ++g)
		{
			const std::string& r = rucksacks[k+g];

			std::fill(inventory.begin(), inventory.end(), false);
			const size_t rsz = r.size();
			for (size_t i = 0; i < rsz; ++i)
			{
				if (r[i] < 'a')
					inventory[(r[i] - 'A') + 26] = true;
				else
					inventory[r[i] - 'a'] = true;
			}
			for (size_t i = 0; i < 52; ++i)
				sharedInv[i] &= inventory[i];
		}

		for (size_t i = 0; i < 52; ++i)
		{
			if (sharedInv[i])
			{
				std::cout << i+1 << std::endl;
				resB += i + 1;
				break;
			}
		}
	}


	writeSolution(resA, resB);
}


