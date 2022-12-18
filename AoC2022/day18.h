/*
 * day18.h
 *
 *  Created on: 2022-12-18
 *      Author: mbreit
 */


template <>
void executeDay<18>(const std::string& fn)
{
	// read input
	std::vector<unsigned> scan(8000, 0);
	{
		std::ifstream infile(fn.c_str());
		unsigned x, y, z;
		while (infile >> x)
		{
			infile >> y;
			infile >> z;
			scan[400*z + 20*y + x] = 1;
		}
		infile.close();
	}

	const auto determineBorderSize = [](const std::vector<unsigned>& scan, unsigned b)
	{
		unsigned ret = 0;
		for (size_t i = 0; i < 8000; ++i)
		{
			if (scan[i] != 1)
				continue;

			if (i % 20 == 0 || scan[i - 1] == b)
				++ret;
			if (i % 20 == 19 || scan[i + 1] == b)
				++ret;
			unsigned j = i / 20;
			if (j % 20 == 0 || scan[i - 20] == b)
				++ret;
			if (j % 20 == 19 || scan[i + 20] == b)
				++ret;
			j = j / 20;
			if (j % 20 == 0 || scan[i - 400] == b)
				++ret;
			if (j % 20 == 19 || scan[i + 400] == b)
				++ret;
		}
		return ret;
	};


	// part a
	unsigned resA = determineBorderSize(scan, 0u);


	// part b
	std::queue<unsigned> q;
	scan[0] = 2;
	q.push(0u);
	while (!q.empty())
	{
		unsigned p = q.front();
		q.pop();

		if (p % 20 != 0 && scan[p - 1] == 0)
		{
			scan[p - 1] = 2;
			q.push(p-1);
		}
		if (p % 20 != 19 && scan[p + 1] == 0)
		{
			scan[p + 1] = 2;
			q.push(p + 1);
		}
		unsigned p1 = p / 20u;
		if (p1 % 20 != 0 && scan[p - 20] == 0)
		{
			scan[p - 20] = 2;
			q.push(p - 20);
		}
		if (p1 % 20 != 19 && scan[p + 20] == 0)
		{
			scan[p + 20] = 2;
			q.push(p + 20);
		}
		p1 /= 20u;
		if (p1 % 20 != 0 && scan[p - 400] == 0)
		{
			scan[p - 400] = 2;
			q.push(p - 400);
		}
		if (p1 % 20 != 19 && scan[p + 400] == 0)
		{
			scan[p + 400] = 2;
			q.push(p + 400);
		}
	}

	unsigned resB = determineBorderSize(scan, 2u);


	writeSolution(resA, resB);
}


