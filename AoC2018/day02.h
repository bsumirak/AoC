/*
 * day02.h
 *
 *  Created on: 2018-12-02
 *      Author: mbreit
 */


template <>
void executeDay<2>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::vector<std::string> vID;
	int n2 = 0;
	int n3 = 0;
	int suma = 0;
	std::string solb;
	std::string id;

	// part a
	while (infile >> id)
	{
		vID.push_back(id);
		const size_t len = id.size();
		std::map<char, int> counter;
		for (size_t i = 0; i < len; ++i)
		{
			++counter[id[i]];
		}

		std::map<char, int>::const_iterator it = counter.begin();
		std::map<char, int>::const_iterator itEnd = counter.end();
		bool hasDouble = false;
		bool hasTriple = false;
		for (; it != itEnd; ++it)
		{
			if (it->second == 2)
				hasDouble = true;
			else if (it->second== 3)
				hasTriple = true;
		}
		if (hasDouble)
			++n2;
		if (hasTriple)
			++n3;

	}
	suma = n2*n3;


	// part b
	std::sort(vID.begin(), vID.end());
	const size_t sz = vID.size() - 1;
	for (size_t i = 0; i < sz; ++i)
	{
		// compare with next
		std::string& s1 = vID[i];
		std::string& s2 = vID[i+1];

		const size_t len = s1.size();
		int differIn = -1;
		for (size_t j = 0; j < len; ++j)
		{
			if (s1[j] != s2[j])
			{
				if (differIn == -1)
					differIn = j;
				else
				{
					differIn = -1;
					break;
				}
			}
		}
		if (differIn != -1)
		{
			solb = s1.erase(differIn, 1);
			break;
		}
	}


	writeSolution(suma, solb);
}


