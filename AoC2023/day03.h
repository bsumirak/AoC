/*
 * day03.h
 *
 *  Created on: 2023-12-03
 *      Author: mbreit
 */

template <>
void executeDay<3>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	unsigned resA = 0;
	unsigned resB = 0;
	
	std::vector<std::string> plan(1);
	while (infile >> plan.back())
		plan.emplace_back();
	const size_t numLines = plan.size() - 1;
	plan.resize(numLines);
	
	const auto isSymbol = [](char c) {return c != '.' && (c < '0' || c > '9');};
	
	std::map<size_t, std::vector<unsigned>> starMap;
	
	for (size_t r = 0; r < numLines; ++r)
	{
		const std::string& line = plan[r];
		const size_t numCol = line.size();
		
		unsigned len = 0;
		unsigned num = 0;
		for (size_t c = 0; c < numCol; ++c)
		{
			const char ch = line[c];
			if (ch >= '0' && ch <= '9')
			{
				num *= 10u;
				num += ch - '0';
				++len;
			}
			else
			{
				if (num != 0)
				{
					bool connectsToSymbol = false;
						
					for (size_t k = 0; k <= len + 1; ++k)
					{
						if (k > c)
							break;
						size_t p = c - k;
						if (r > 0 && isSymbol(plan[r-1][p]))
						{
							connectsToSymbol = true;
							if (plan[r-1][p] == '*')
								starMap[(r-1) * numCol + p].push_back(num);
						}
						if (isSymbol(plan[r][p]))
						{
							connectsToSymbol = true;
							if (plan[r][p] == '*')
								starMap[r * numCol + p].push_back(num);
						}
						if (r + 1 < numLines && isSymbol(plan[r+1][p]))
						{
							connectsToSymbol = true;
							if (plan[r+1][p] == '*')
								starMap[(r+1) * numCol + p].push_back(num);
						}
					}

					if (connectsToSymbol)
						resA += num;
			
					num = 0;
					len = 0;
				}
			}
		}	
	}
	
	for (const auto& entry: starMap)
	{
		if (entry.second.size() == 2)
			resB += entry.second[0] * entry.second[1]; 
	}
	
	writeSolution(resA, resB);
}


