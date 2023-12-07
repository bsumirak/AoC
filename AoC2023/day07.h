/*
 * day07.h
 *
 *  Created on: 2023-12-07
 *      Author: mbreit
 */

template <>
void executeDay<7>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::vector<std::pair<std::string, unsigned>> game;
	std::pair<std::string, unsigned> handBid;	
	while (infile >> handBid.first)
	{
		infile >> handBid.second;
		game.push_back(handBid);
	}
	
	enum HandType{HIGH = 0, ONE, TWO, THREE, FULL, FOUR, FIVE};
		
	const auto getOrder = [&](unsigned part) -> std::vector<size_t>
	{
		std::vector<HandType> types;
		types.reserve(game.size());
		for (const auto& player : game)
		{
			auto hand = player.first;
			std::sort(hand.begin(), hand.end());
		
			unsigned jCnt = 0;
			unsigned maxCnt = 0;
			unsigned secCnt = 0;
			char curChar = hand[0];
			unsigned curCnt = 1;
			for (size_t k = 1; k < 6; ++k)
			{
				const char c = k < 5 ? hand[k] : '0';
				if (c == curChar)
					++curCnt;
				else
				{
					if (part == 2 && curChar == 'J')
						jCnt = curCnt;
					else if (curCnt > maxCnt)
					{
						secCnt = maxCnt;
						maxCnt = curCnt;
					}
					else if (curCnt > secCnt)
						secCnt = curCnt;
					curCnt = 1;
					curChar = c;
				}
			}
		
			if (part == 2)
				maxCnt += jCnt;

			if (maxCnt == 5)
				types.push_back(FIVE);
			else if (maxCnt == 4)
				types.push_back(FOUR);
			else if (maxCnt == 3 && secCnt == 2)
				types.push_back(FULL);
			else if (maxCnt == 3)
				types.push_back(THREE);
			else if (maxCnt == 2 && secCnt == 2)
				types.push_back(TWO);
			else if (maxCnt == 2)
				types.push_back(ONE);
			else
				types.push_back(HIGH);
		}
	
		std::vector<size_t> inds(game.size());
		for (size_t k = 0; k < inds.size(); ++k)
			inds[k] = k;
	
		const auto cardValue = [&](char c)
		{
			if (c == 'A')
				return 14;
			if (c == 'K')
				return 13;
			if (c == 'Q')
				return 12;
			if (c == 'J')
				return part == 2 ? 1 : 11;
			if (c == 'T')
				return 10;
			else return c - '0';
		};
	
		const auto cardCompare = [&](char c1, char c2)
		{
			auto val1 = cardValue(c1);
			auto val2 = cardValue(c2);
			return val1 < val2;
		};
	
		const auto secondaryCompare = [&](const std::string& s1, const std::string& s2)
		{
			for (size_t k = 0; k < 5; ++k)
			{
				if (cardCompare(s1[k], s2[k]))
					return true;
				if (cardCompare(s2[k], s1[k]))
					return false;
			}
			return false;
		};
	
		const auto sorting = [&](size_t k, size_t l)
		{
			if (types[k] < types[l])
				return true;
			if (types[k] > types[l])
				return false;
			return secondaryCompare(game[k].first, game[l].first); 
		};
		std::sort(inds.begin(), inds.end(), sorting);
		
		return inds;
	};
	
	
	// part a
	auto indsA = getOrder(1);
	uint64_t resA = 0;
	for (size_t k = 0; k < indsA.size(); ++k)
		resA += (k+1) * game[indsA[k]].second;

	// part b
	auto indsB = getOrder(2);	
	uint64_t resB = 0;
	for (size_t k = 0; k < indsB.size(); ++k)
		resB += (k+1) * game[indsB[k]].second;
	
	
	writeSolution(resA, resB);
}


