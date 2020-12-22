/*
 * day22.h
 *
 *  Created on: 2020-12-22
 *      Author: mbreit
 */


unsigned play(std::deque<unsigned>& d1, std::deque<unsigned>& d2)
{
	std::set<std::pair<std::deque<unsigned>, std::deque<unsigned> > > mem;
	while (!d1.empty() && !d2.empty())
	{
		if (mem.insert(std::make_pair(d1, d2)).second == false)
			return 1u;

		unsigned c1 = d1.front();
		unsigned c2 = d2.front();
		d1.pop_front();
		d2.pop_front();

		unsigned winner = 0;

		if (c1 <= d1.size() && c2 <= d2.size())
		{
			std::deque<unsigned> sd1(d1.begin(), d1.begin() + c1);
			std::deque<unsigned> sd2(d2.begin(), d2.begin() + c2);
			winner = play(sd1, sd2);
			if (winner == 0u)
				return 0u;
		}
		else
			winner = c1 > c2 ? 1u : 2u;

		if (winner == 1)
		{
			d1.push_back(c1);
			d1.push_back(c2);
		}
		else
		{
			d2.push_back(c2);
			d2.push_back(c1);
		}
	}

	if (d1.empty())
		return 2u;
	else
		return 1u;
}




template <>
void executeDay<22>(const std::string& fn)
{
	// read input
	std::deque<unsigned> p1 = {2, 31, 14, 45, 33, 18, 29, 36, 44, 47, 38, 6, 9, 5, 48, 17, 50, 41, 4, 21, 42, 23, 25, 28, 3};
	std::deque<unsigned> p2 = {26, 16, 27, 12, 49, 32, 19, 46, 37, 15, 10, 30, 11, 24, 1, 40, 7, 8, 43, 34, 20, 35, 22, 39, 13};
	auto d1 = p1;
	auto d2 = p2;

	// part a
	while (!p1.empty() && !p2.empty())
	{
		unsigned c1 = p1.front();
		unsigned c2 = p2.front();
		p1.pop_front();
		p2.pop_front();
		if (c1 > c2)
		{
			p1.push_back(c1);
			p1.push_back(c2);
		}
		else
		{
			p2.push_back(c2);
			p2.push_back(c1);
		}
	}

	std::size_t resA = 0;
	std::deque<unsigned>* l = p1.empty() ? &p2 : &p1;
	size_t i = 50;
	for (auto& k: *l)
	{
		resA += k*i;
		--i;
	}


	// part b
	unsigned winner = play(d1, d2);
	l = nullptr;
	if (winner == 0 || winner == 1)
		l = &d1;
	else
		l = &d2;

	std::size_t resB = 0;
	i = 50;
	for (auto& k: *l)
	{
		resB += k*i;
		--i;
	}

	writeSolution(resA, resB);
}


