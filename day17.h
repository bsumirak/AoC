/*
 * day17.h
 *
 *  Created on: 17.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<17>(const std::string& fn)
{
	int step = 354;

	int pos = 0;
	std::list<int> buf;
	buf.insert(buf.begin(), 0);

	std::list<int>::iterator it;
	for (size_t i = 1; i < 2018; ++i)
	{
		// step
		pos = (pos + step) % i + 1;

		it = buf.begin();
		for (size_t j = 0; j < pos; ++j)
			++it;

		buf.insert(it, i);
	}

	int sola;
	if (it == buf.end())
		sola = *buf.begin();
	else
		sola = *it;

	pos = 0;
	int curAt1 = 0;
	for (size_t i = 1; i < 50000001; ++i)
	{
		if ((pos = (pos + step) % i) == 0)
			curAt1 = i;
		++pos;
	}
	writeSolution(sola, curAt1);
}


