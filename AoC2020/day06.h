/*
 * day01.h
 *
 *  Created on: 2020-12-06
 *      Author: mbreit
 */


template <>
void executeDay<6>(const std::string& fn)
{
	// read input
	std::vector<std::vector<std::string>> groups(1);
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		while (std::getline(infile, line))
		{
			if (!line.size())
				groups.resize(groups.size() + 1);
			else
				groups.back().push_back(line);
		}
		infile.close();
	}
	const std::size_t sz = groups.size();


	// part a
	std::size_t resA = 0;
	std::array<bool, 26> q;
	for (std::size_t i = 0; i < sz; ++i)
	{
		memset(q.data(), 0, 26 * sizeof(bool));
		for (std::size_t p = 0; p < groups[i].size(); ++p)
		{
			for (std::size_t c = 0; c < groups[i][p].size(); ++c)
				q[groups[i][p][c] - 'a'] = true;
		}
		int a = 0;
		for (std::size_t j = 0; j < 26; ++j)
			if (q[j])
				++a;
		resA += a;
	}


	// part b
	std::size_t resB = 0;
	std::array<bool, 26> qAll;
	for (std::size_t i = 0; i < sz; ++i)
	{
		memset(qAll.data(), 1, 26 * sizeof(bool));
		for (std::size_t p = 0; p < groups[i].size(); ++p)
		{
			memset(q.data(), 0, 26 * sizeof(bool));
			for (std::size_t c = 0; c < groups[i][p].size(); ++c)
				q[groups[i][p][c] - 'a'] = true;

			for (std::size_t j = 0; j < 26; ++j)
				qAll[j] = q[j] && qAll[j];
		}
		int a = 0;
		for (std::size_t j = 0; j < 26; ++j)
		{
			if (qAll[j])
				++a;
		}
		resB += a;
	}


	writeSolution(resA, resB);
}


