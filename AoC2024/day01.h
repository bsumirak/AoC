/*
 * day01.h
 *
 *  Created on: 2024-12-01
 *      Author: mbreit
 */


template <>
void executeDay<1>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::array<std::vector<unsigned>, 2> values;

	unsigned v = 0u;
	while (infile >> v)
	{
		values[0].push_back(v);
		infile >> v;
		values[1].push_back(v);
	}

	std::sort(values[0].begin(), values[0].end());
	std::sort(values[1].begin(), values[1].end());

	// part a
	unsigned resA = 0;
	const auto num = values[0].size();
	for (size_t k = 0; k < num; ++k)
		resA += (unsigned)std::abs((int)values[0][k] - (int)values[1][k]);

	// part b
	unsigned resB = 0;

	auto it1 = values[0].begin();
	auto it2 = values[1].begin();
	while (it1 != values[0].end())
	{
		const auto v = *it1;
		unsigned cnt1 = 1u;
		while (++it1 != values[0].end() && *it1 == v)
			++cnt1;

		unsigned cnt2 = 0u;
		while (it2 != values[1].end() && *it2 <= v)
		{
			if (*it2 == v)
				++cnt2;
			++it2;
		}

		resB += v * cnt1 * cnt2;
	}


	writeSolution(resA, resB);
}


