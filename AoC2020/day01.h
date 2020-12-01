/*
 * day01.h
 *
 *  Created on: 2019-12-01
 *      Author: mbreit
 */


template <>
void executeDay<1>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	int i;

	std::vector<int> v;
	while (infile >> i)
		v.push_back(i);
	infile.close();
	std::size_t sz = v.size();

	int resA = 0;
	for (std::size_t i = 0; i < sz; ++i)
	{
		for (std::size_t j = i; j < sz; ++j)
		{
			if (v[i] + v[j] != 2020)
				continue;
			resA = v[i] * v[j];
			break;
		}
		if (resA != 0)
			break;
	}


	int resB = 0;
	for (std::size_t i = 0; i < sz; ++i)
	{
		for (std::size_t j = i; j < sz; ++j)
		{
			for (std::size_t k = j; k < sz; ++k)
			{
				if (v[i] + v[j] + v[k] != 2020)
					continue;
				resB = v[i] * v[j] * v[k];
				break;
			}
			if (resB != 0)
				break;
		}
		if (resB != 0)
			break;
	}


	writeSolution(resA, resB);
}


