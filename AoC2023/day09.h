/*
 * day09.h
 *
 *  Created on: 2023-12-09
 *      Author: mbreit
 */

template <>
void executeDay<9>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	int64_t resA = 0;
	int64_t resB = 0;
	
	std::string line;
	std::vector<std::vector<int64_t>> suites;
	while (std::getline(infile, line))
	{
		suites.emplace_back();
		auto& suite = suites.back();
		std::istringstream iss(line);
		int64_t i;
		while (iss >> i)
			suite.push_back(i);
	}
	
	// part a
	for (auto suite : suites)
	{
		const size_t l = suite.size();
		bool allEqual = false;
		size_t k = 1;
		while (!allEqual)
		{
			allEqual = true;
			for (size_t j = 0; j < l - k; ++j)
			{
				suite[j] = suite[j+1] - suite[j];
				if (j > 0 && suite[j] != suite[j - 1])
					allEqual = false;
			}
			++k;
		}
		
		for (size_t j = l - k + 1; j < l; ++j)
			suite[j] += suite[j-1];
			
		resA += suite[l - 1];
	}
	
	
	// part b
	for (auto& suite : suites)
	{
		const size_t l = suite.size();
		bool allEqual = false;
		size_t k = 1;
		while (!allEqual)
		{
			allEqual = true;
			for (size_t j = l - 1; j >= k; --j)
			{
				suite[j] = suite[j] - suite[j - 1];
				if (j < l - 1 && suite[j] != suite[j + 1])
					allEqual = false;
			}
			++k;
		}
		
		for (size_t j = k - 1; j > 0; --j)
			suite[j - 1] -= suite[j];
			
		resB += suite[0];
	}
	
	writeSolution(resA, resB);
}


