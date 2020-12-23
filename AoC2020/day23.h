/*
 * day23.h
 *
 *  Created on: 2020-12-23
 *      Author: mbreit
 */




template <>
void executeDay<23>(const std::string& fn)
{
	std::list<unsigned> input = {1, 5, 8, 9, 3, 7, 4, 6, 2};

	const auto crabGame = [] (std::list<unsigned>& l, unsigned numIt)
	{
		// init iterator lookup table
		const unsigned sz = l.size();
		std::vector<std::list<unsigned>::iterator> its(sz);
		auto it = l.begin();
		while (it != l.end())
		{
			its[*it-1u] = it;
			++it;
		}

		auto cur = l.begin();
		std::array<unsigned, 3> tmp;
		for (size_t i = 0; i < numIt; ++i)
		{
			// find destination
			unsigned dest = *cur == 1u ? sz : *cur - 1u;

			// pick out three following elements
			++cur;
			for (size_t j = 0; j < 3; ++j)
			{
				if (cur == l.end())
					cur = l.begin();
				tmp[j] = *cur;
				cur = l.erase(cur);
			}

			while (dest == tmp[0] || dest == tmp[1] || dest == tmp[2])
				dest = dest == 1u ? sz : dest - 1u;

			// insert after dest and update lookup table
			auto destIt = its[dest-1u];
			++destIt;
			auto newIt = l.insert(destIt, tmp.begin(), tmp.end());
			its[tmp[0]-1u] = newIt;
			its[tmp[1]-1u] = ++newIt;
			its[tmp[2]-1u] = ++newIt;

			if (cur == l.end())
				cur = l.begin();
		}

		return its[0];
	};


	// part a
	std::string resA;
	{
		std::list<unsigned> l = input;
		auto it1 = crabGame(l, 100);

		std::ostringstream oss;
		auto it = it1;
		for (++it; it != l.end(); ++it)
			oss << *it;
		for (it = l.begin(); it != it1; ++it)
			oss << *it;
		resA = oss.str();
	}


	// part b
	std::size_t resB = 0;
	{
		std::list<unsigned> l = input;
		for (size_t k = 10; k <= 1000000; ++k)
			l.push_back(k);

		auto it1 = crabGame(l, 10000000);
		resB = *++it1;
		resB *= *++it1;
	}


	writeSolution(resA, resB);
}


