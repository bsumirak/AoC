/*
 * day10.h
 *
 *  Created on: 2020-12-10
 *      Author: mbreit
 */


template <>
void executeDay<10>(const std::string& fn)
{
	// read input
	std::vector<int> v;
	{
		std::ifstream infile(fn.c_str());
		int i;
		while (infile >> i)
			v.push_back(i);
		infile.close();
	}
	v.push_back(0);
	const std::size_t sz = v.size();


	// part a
	std::size_t resA = 0;
	std::sort(v.begin(), v.end());
	int diff1 = 0;
	int diff3 = 0;

	for (size_t i = 0; i < sz-1; ++i)
	{
		if (v[i+1] - v[i] == 1)
			++diff1;
		else if (v[i+1] - v[i] == 3)
			++diff3;
	}
	resA = diff1 * (diff3+1);


	// part b
	int cnt3 = 0;
	int cnt4 = 0;
	int cnt5 = 0;
	for (size_t i = 0; i < sz; ++i)
	{
		int cnt = i;
		while (i + 1 < sz && v[i+1] == v[i] + 1)
			++i;

		if (i - cnt == 2)
			++cnt3;
		else if (i - cnt == 3)
			++cnt4;
		if (i - cnt == 4)
			++cnt5;
		else if (i - cnt > 4)
			std::cout << i - cnt << std::endl;
	}

	int64_t resB = int64_t(std::pow(2, cnt3 + 2*cnt4)) * int64_t(std::pow(7, cnt5));


	writeSolution(resA, resB);
}


