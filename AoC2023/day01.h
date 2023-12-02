/*
 * day01.h
 *
 *  Created on: 2023-12-01
 *      Author: mbreit
 */


template <>
void executeDay<1>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::string s;
	unsigned resA = 0;
	unsigned resB = 0;
	while (infile >> s)
	{
		// part a
		const auto isDigit = [](char c){return c >= '0' && c <= '9';};
		const auto it1 = std::find_if(s.begin(), s.end(), isDigit);
		const auto it2 = std::find_if(s.rbegin(), s.rend(), isDigit);
		resA += 10u * (*it1 - '0') + (*it2 - '0');
		
		// part b
		size_t minPos = std::distance(s.begin(), it1);
		size_t maxPos = s.size() - 1 - std::distance(s.rbegin(), it2);
		unsigned minDigit = (*it1 - '0');
		unsigned maxDigit = (*it2 - '0');
		
		const auto checkDigit = [&](unsigned d, const std::string& ds)
		{
			size_t p = 0;
			if ((p = s.find(ds)) != std::string::npos && p < minPos)
			{
				minPos = std::min(minPos, p);
				minDigit = d;
			}
			if ((p = s.rfind(ds)) != std::string::npos && p > maxPos)
			{
				maxPos = std::max(maxPos, p);
				maxDigit = d;
			}
		};
		
		checkDigit(0, "zero");
		checkDigit(1, "one");
		checkDigit(2, "two");
		checkDigit(3, "three");
		checkDigit(4, "four");
		checkDigit(5, "five");
		checkDigit(6, "six");
		checkDigit(7, "seven");
		checkDigit(8, "eight");
		checkDigit(9, "nine");
		
		resB += 10u * minDigit + maxDigit;
	}
	
	writeSolution(resA, resB);
}


