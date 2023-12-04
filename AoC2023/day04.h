/*
 * day04.h
 *
 *  Created on: 2023-12-04
 *      Author: mbreit
 */

template <>
void executeDay<4>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	unsigned resA = 0;
	unsigned resB = 0;
	
	std::list<unsigned> l;
	
	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		std::string s;
		iss >> s;
		iss >> s;
		
		std::vector<unsigned> winNumbers(10, 0);
		for (size_t k = 0; k < 10; ++k)
			iss >> winNumbers[k];

		iss >> s;

		unsigned u;
		unsigned cnt = 0;
		for (size_t k = 0; k < 25; ++k)
		{
			iss >> u;
			if (std::find(winNumbers.begin(), winNumbers.end(), u) != winNumbers.end())
				++cnt;
		}
		
		// part a
		if (cnt > 0)
			resA += std::pow(2, cnt - 1);
			
		// part b
		unsigned fct = 1;
		if (!l.empty())
		{
			fct += l.front();
			l.pop_front();
		}
		if (cnt > 0)
		{
			for (auto it = l.begin(); it != l.end() && cnt > 0; ++it, --cnt)
				*it += fct;
			for (; cnt > 0; --cnt)
				l.push_back(fct);
		}
		
		resB += fct;
	}
	
	
	writeSolution(resA, resB);
}


