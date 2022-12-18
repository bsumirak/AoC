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
	std::vector<unsigned> v(8000, 0);
	{
		std::ifstream infile(fn.c_str());
		unsigned x, y, z;
		while (infile >> x)
		{
			infile >> y;
			infile >> z;
			v[400*z + 20*y + x] = 1;
		}
		infile.close();
	}


	// part a
	unsigned resA = 0;
	for (size_t i = 0; i < 8000; ++i)
	{
		if (!v[i])
			continue;

		if (i % 20 == 0 || !v[i - 1])
			++resA;
		if (i % 20 == 19 || !v[i + 1])
			++resA;
		unsigned j = i / 20;
		if (j % 20 == 0 || !v[i - 20])
			++resA;
		if (j % 20 == 19 || !v[i + 20])
			++resA;
		j = j / 20;
		if (j % 20 == 0 || !v[i - 400])
			++resA;
		if (j % 20 == 19 || !v[i + 400])
			++resA;
	}

	// part b
	std::size_t resB = 0;

	std::queue<unsigned> q;
	v[0] = 2;
	q.push(0u);
	while (!q.empty())
	{
		unsigned p = q.front();
		q.pop();

		if (p % 20 != 0 && v[p - 1] == 0)
		{
			v[p - 1] = 2;
			q.push(p-1);
		}
		if (p % 20 != 19 && v[p + 1] == 0)
		{
			v[p + 1] = 2;
			q.push(p + 1);
		}
		unsigned p1 = p / 20u;
		if (p1 % 20 != 0 && v[p - 20] == 0)
		{
			v[p - 20] = 2;
			q.push(p - 20);
		}
		if (p1 % 20 != 19 && v[p + 20] == 0)
		{
			v[p + 20] = 2;
			q.push(p + 20);
		}
		p1 /= 20u;
		if (p1 % 20 != 0 && v[p - 400] == 0)
		{
			v[p - 400] = 2;
			q.push(p - 400);
		}
		if (p1 % 20 != 19 && v[p + 400] == 0)
		{
			v[p + 400] = 2;
			q.push(p + 400);
		}
	}

	for (size_t i = 0; i < 8000; ++i)
	{
		if (v[i] != 1)
			continue;

		if (i % 20 == 0 || v[i - 1] == 2)
			++resB;
		if (i % 20 == 19 || v[i + 1] == 2)
			++resB;
		unsigned j = i / 20;
		if (j % 20 == 0 || v[i - 20] == 2)
			++resB;
		if (j % 20 == 19 || v[i + 20] == 2)
			++resB;
		j = j / 20;
		if (j % 20 == 0 || v[i - 400] == 2)
			++resB;
		if (j % 20 == 19 || v[i + 400] == 2)
			++resB;
	}


	writeSolution(resA, resB);
}


