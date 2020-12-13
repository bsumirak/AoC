/*
 * day09.h
 *
 *  Created on: 2020-12-09
 *      Author: mbreit
 */


template <>
void executeDay<9>(const std::string& fn)
{
	// read input
	std::vector<int64_t> v;
	{
		std::ifstream infile(fn.c_str());
		int64_t i;
		while (infile >> i)
			v.push_back(i);
		infile.close();
	}
	const std::size_t sz = v.size();
	std::cout << sz<< std::endl;

	// part a
	int64_t resA = 0;
	for (std::size_t i = 25; i < sz; ++i)
	{
		bool found = false;
		for (std::size_t j = i - 25; j < i; ++j)
		{
			for (std::size_t k = j + 1; k < i; ++k)
			{
				if (v[i] == v[j] + v[k] && v[j] != v[k])
				{
					found = true;
					break;
				}
			}
			if (found)
				break;
		}
		if (!found)
		{
			resA = v[i];
			break;
		}
	}


	// part b
	std::size_t resB = 0;
	std::size_t first = 0;
	std::size_t last = 0;
	int64_t sum = v[0];
	while (last < sz)
	{
		while (sum < resA && ++last < sz)
			sum += v[last];
		while (sum > resA)
			sum -= v[first++];
		if (sum == resA)
			break;
	}
	int64_t min = v[first];
	int64_t max = v[first];
	for (std::size_t i = first + 1; i <= last; ++i)
	{
		min = std::min(min, v[i]);
		max = std::max(max, v[i]);
	}
	resB = min + max;


	writeSolution(resA, resB);
}


