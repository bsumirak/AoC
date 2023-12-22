/*
 * day22.h
 *
 *  Created on: 2023-12-22
 *      Author: mbreit
 */

template <>
void executeDay<22>(const std::string& fn)
{
	// parse input
	std::ifstream infile(fn.c_str());
	
	std::vector<std::array<unsigned, 6>> bricks;
	unsigned u;
	while (infile >> u)
	{
		bricks.emplace_back();
		bricks.back()[0] = u;
		for (size_t k = 1; k < 6; ++k)
			infile >> bricks.back()[k];
	}
	const size_t sz = bricks.size();	

	std::sort(bricks.begin(), bricks.end(),
		[](const std::array<unsigned, 6>& b1, const std::array<unsigned, 6>& b2)
		{
			if (std::min(b1[2], b1[5]) < std::min(b2[2], b2[5]))
				return true;
			return false;
		});


	// part a
	std::vector<bool> safeToCrush(sz, true);
	std::vector<std::pair<unsigned, size_t>> lvl(1000000, {0, sz});
	std::vector<std::vector<size_t>> suppBy(sz);
	for (size_t k = 0; k < sz; ++k)
	{
		auto& brick = bricks[k];
		auto minX = std::min(brick[0], brick[3]);
		auto maxX = std::max(brick[0], brick[3]);
		auto minY = std::min(brick[1], brick[4]);
		auto maxY = std::max(brick[1], brick[4]);
		auto minZ = std::min(brick[2], brick[5]);
		auto maxZ = std::max(brick[2], brick[5]);
		auto zLen = maxZ - minZ;
		unsigned maxLvl{0};
		std::vector<size_t>& supp = suppBy[k];
		for (size_t x = minX; x <= maxX; ++x)
		{
			for (size_t y = minY; y <= maxY; ++y)
			{
				auto& lp = lvl[1000*x + y];
				if (lp.first > maxLvl)
				{
					maxLvl = lp.first;
					supp = {lp.second};
				}
				else if (lp.first == maxLvl)
				{
					auto it = std::find(supp.begin(), supp.end(), lp.second);
					if (it == supp.end())
						supp.push_back(lp.second);
				}
			}
		}
		for (size_t x = minX; x <= maxX; ++x)
			for (size_t y = minY; y <= maxY; ++y)
				lvl[1000*x+y] = {maxLvl + 1 + zLen, k};
		
		if (supp.size() == 1)
			safeToCrush[supp[0]] = false;
	}

	size_t resA = 0;
	for (size_t k = 0; k < sz; ++k)
		if (safeToCrush[k])
			++resA;


	// part b
	uint64_t resB = 0;
	for (size_t k= 0; k < sz; ++k)
	{
		std::vector<bool> hasFallen(sz, false);
		hasFallen[k] = true;
		
		size_t nFalls = 0;
		bool moreFalls = true;
		do
		{
			moreFalls = false;
			for (size_t l = 0; l < sz; ++l)
			{
				if (hasFallen[l])
					continue;
					
				bool falls = true;
				for (size_t s : suppBy[l])
					if (!hasFallen[s])
					{
						falls = false;
						break;
					}
				if (falls)
				{
					++nFalls;
					moreFalls = true;
					hasFallen[l] = true;
				}
			}
		}
		while (moreFalls);
		
		resB += nFalls;
	}	
	
	
	writeSolution(resA, resB);
}


