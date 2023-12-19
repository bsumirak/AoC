/*
 * day18.h
 *
 *  Created on: 2023-12-18
 *      Author: mbreit
 */

template <>
void executeDay<18>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	
	std::vector<std::array<unsigned, 2>> diggingPlanA;
	std::vector<std::array<unsigned, 2>> diggingPlanB;
	char dir;
	while (infile >> dir)
	{
		unsigned uDir = dir == 'R' ? 0u : dir == 'U' ? 1u : dir == 'L' ? 2u : 3u;
		unsigned cnt;
		infile >> cnt;
		diggingPlanA.emplace_back(std::array<unsigned, 2>{uDir, cnt});

		std::string s;
		infile >> s;
		diggingPlanB.emplace_back();
		diggingPlanB.back()[0] = s[7] - '0';
		std::istringstream iss(s.substr(2, 5));
		iss >> std::hex >> diggingPlanB.back()[1];
	}


	const auto computeLagoonVolume = [](const std::vector<std::array<unsigned, 2>>& diggingPlan)
	{
		std::set<std::array<int, 3>> horizTrenches;
		std::set<std::array<int, 3>> vertTrenches;
	
		int minX = std::numeric_limits<int>::max();
		int maxX = -std::numeric_limits<int>::max();
		int minY = std::numeric_limits<int>::max();
		int maxY = -std::numeric_limits<int>::max();
	
		std::array<int, 2> pos{0, 0};
		for (const auto& dig : diggingPlan)
		{
			switch (dig[0])
			{
				case 0:
				{
					horizTrenches.insert({pos[1], pos[0], pos[0] + (int)dig[1]});
					pos[0] += dig[1];
					maxX = std::max(maxX, pos[0]);
					break;
				}
				case 3:
					vertTrenches.insert({pos[1] - (int)dig[1], pos[1], pos[0]});
					pos[1] -= dig[1];
					minY = std::min(minY, pos[1]);
					break;
				case 2:
				{
					horizTrenches.insert({pos[1], pos[0] - (int)dig[1], pos[0]});
					pos[0] -= dig[1];
					minX = std::min(minX, pos[0]);
					break;
				}
				case 1:
					vertTrenches.insert({pos[1], pos[1] + (int)dig[1], pos[0]});
					pos[1] += dig[1];
					maxY = std::max(maxY, pos[1]);
					break;
			}
		}

		uint64_t ret = 0;

		std::vector<std::array<int, 3>> actVertTrenches;
		std::vector<std::array<int, 3>> actHorizTrenches;
		auto vertTrenchesIt = vertTrenches.begin();
		auto horizTrenchesIt = horizTrenches.begin();
		
		bool prevLineHadHorizTrench = false;
		unsigned prevVal = 0;
		for (int y = minY; y <= maxY; ++y)
		{
			// remove ended vertical trenches
			const auto eraseIt = std::stable_partition(actVertTrenches.begin(), actVertTrenches.end(),
				[y](const std::array<int, 3>& trench) {return trench[1] >= y;});
			actVertTrenches.erase(eraseIt, actVertTrenches.end());
		
			// insert possible new vertical trenches
			while (vertTrenchesIt != vertTrenches.end() && (*vertTrenchesIt)[0] == y)
			{
				const auto insIt = std::upper_bound(actVertTrenches.begin(), actVertTrenches.end(), (*vertTrenchesIt)[2],
					[](int val, const std::array<int, 3>& array){return val < array[2];});
				actVertTrenches.insert(insIt, *vertTrenchesIt);
				++vertTrenchesIt;
			}
			
			// get current horizontal trenches		
			actHorizTrenches.clear();
			while (horizTrenchesIt != horizTrenches.end() && (*horizTrenchesIt)[0] == y)
			{
				actHorizTrenches.push_back(*horizTrenchesIt);
				++horizTrenchesIt;
			}
			
			auto horizTrenchIt = actHorizTrenches.begin();
			auto vertTrenchIt = actVertTrenches.begin();

			if (actHorizTrenches.empty() && !prevLineHadHorizTrench)
			{
				ret += prevVal;
				continue;
			}
			
			unsigned curVal = 0;
			
			enum State{OUT = 0, IN};
			State state = OUT;
			int prevEntry = 0;
			
			while (horizTrenchIt != actHorizTrenches.end() || vertTrenchIt != actVertTrenches.end())
			{
				// next trench is pure vertical
				if (vertTrenchIt != actVertTrenches.end()
					&& (horizTrenchIt == actHorizTrenches.end() || (*horizTrenchIt)[1] > (*vertTrenchIt)[2]))
				{
					if (state == OUT)
					{
						prevEntry = (*vertTrenchIt)[2];
						state = IN;
					}
					else if (state == IN)
					{
						curVal += (*vertTrenchIt)[2] - prevEntry + 1;
						state = OUT;
					}
				
					++vertTrenchIt;
				}
			
				// next trench is horizontal
				else
				{
					prevLineHadHorizTrench = true;
					
					// it must be a corner
					bool isLowerBorder = (state == OUT) == ((*vertTrenchIt)[0] == y);
					if (state == OUT)
					{
						prevEntry = (*vertTrenchIt)[2];
						state = IN;
					}
				
					++vertTrenchIt;
								
					while (true)
					{
						if ((*vertTrenchIt)[2] != (*horizTrenchIt)[2])
							++horizTrenchIt;
						else
							break;
					}
								
					bool nextStateIsOut = isLowerBorder == ((*vertTrenchIt)[0] == y);
					if (nextStateIsOut)
					{
						if (state == IN)
							curVal += (*vertTrenchIt)[2] - prevEntry + 1;
						state = OUT;
					}
					else
					{
						if (state == OUT)
							prevEntry = (*vertTrenchIt)[2];
						state = IN;
					}
				
					++horizTrenchIt;
					++vertTrenchIt;
				}
			}
			
			ret += curVal;
			prevVal = curVal;
		}
	
		return ret;
	};
	
	
	// part a
	uint64_t resA = computeLagoonVolume(diggingPlanA);

	// part b
	uint64_t resB = computeLagoonVolume(diggingPlanB);
	
	writeSolution(resA, resB);
}


