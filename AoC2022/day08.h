/*
 * day08.h
 *
 *  Created on: 2022-12-08
 *      Author: mbreit
 */


template <>
void executeDay<8>(const std::string& fn)
{
	// read input
	std::vector<char> v;
	{
		std::ifstream infile(fn.c_str());
		char c;
		while (infile >> c)
			v.push_back(c);
		infile.close();
	}
	const std::size_t sz = v.size();


	unsigned resA = 0;
	unsigned resB = 0;
	for (size_t t = 0; t < sz; ++t)
	{
		bool vis = false;
		unsigned score = 1;
		unsigned dist = 0;
		size_t s;

		// to top
		for (s = t; s >= 99; s -= 99)
		{
			++dist;
			if (v[s - 99] >= v[t])
				break;
		}
		vis |= s < 99;
		score *= dist;

		// to bottom
		for (s = t, dist = 0; s < 98*99; s += 99)
		{
			++dist;
			if (v[s + 99] >= v[t])
				break;
		}
		vis |= s >= 98*99;
		score *= dist;

		// to left
		for (s = t, dist = 0; s % 99 > 0; --s)
		{
			++dist;
			if (v[s-1] >= v[t])
				break;
		}
		vis |= s % 99 == 0;
		score *= dist;

		//to right
		for (s = t, dist = 0; s % 99 < 98; ++s)
		{
			++dist;
			if (v[s+1] >= v[t])
				break;
		}
		vis |= s % 99 == 98;
		score *= dist;

		// evaluate
		resA += vis;
		resB = std::max(resB, score);
	}


	writeSolution(resA, resB);
}


