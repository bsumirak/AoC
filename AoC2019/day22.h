/*
 * day22.h
 *
 *  Created on: 22.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<22>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	const std::size_t sz = 10007;
	std::vector<int> deck(sz);
	for (std::size_t i = 0; i < sz; ++i)
		deck[i] = i;

	bool order = true;
	std::size_t startPos = 0;
	int tmp;
	std::vector<int> help(sz);
	while (infile >> tmp)
	{
		switch (tmp)
		{
			case 0: // stack
				order = !order;
				break;
			case 1:
				infile >> tmp;
				startPos = (startPos + (order ? tmp : -tmp) + sz) % sz;
				break;
			case 2:
				infile >> tmp;
				for (std::size_t i = 0; i < sz; ++i)
					help[(i*tmp)%sz] = deck[(startPos + (order ? i : -(i+1)) + sz) % sz];
				deck.swap(help);
				order = true;
				startPos = 0;
				break;
		}
	}

	std::size_t i = 0;
	for (; i < sz; ++i)
		if (deck[(startPos + (order ? i : -(i+1)) + sz) % sz] == 2019)
			break;

	writeSolution(i, 0);
}


