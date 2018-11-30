/*
 * day16.h
 *
 *  Created on: 16.12.2017
 *      Author: mbreit
 */


struct move
{
	char type;
	char x1;
	char x2;
};

template <>
void executeDay<16>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::vector<char> order(17);
	for (int i = 0; i < 16; ++i)
		order[i] = 'a' + (char) i;

	std::vector<move> vMoves;

	char c;
	while (infile.get(c))
	{
		switch (c)
		{
			case 's':
			{
				int cnt = -1;
				size_t nS = 0;
				while (infile.get(c) && c != ',')
					nS += (c-'0') * std::pow(10, 1 - ++cnt);
				if (cnt == 0)
					nS /= 10;

				vMoves.resize(vMoves.size()+1);
				vMoves.back().type = 's';
				vMoves.back().x1 = (char) nS;

				break;
			}
			case 'x':
			{
				int cnt = -1;
				size_t xa = 0;
				while (infile.get(c) && c != '/')
					xa += (c-'0') * std::pow(10, 1 - ++cnt);
				if (cnt == 0)
					xa /= 10;

				cnt = -1;
				size_t xb = 0;
				while (infile.get(c) && c != ',')
					xb += (c-'0') * std::pow(10, 1 - ++cnt);
				if (cnt == 0)
					xb /= 10;

				vMoves.resize(vMoves.size()+1);
				vMoves.back().type = 'x';
				vMoves.back().x1 = (char) xa;
				vMoves.back().x2 = (char) xb;

				break;
			}
			case 'p':
			{
				int cnt = 0;
				char pa, pb;
				infile.get(pa);
				infile.get(pb); // slash
				infile.get(pb);

				vMoves.resize(vMoves.size()+1);
				vMoves.back().type = 'p';
				vMoves.back().x1 = (char) pa;
				vMoves.back().x2 = (char) pb;

				infile.get(pb); // comma
				break;
			}
			default: throw;
		}
	}

	std::vector<char> tmp(16);
	std::vector<char> order1(16);

	std::vector<std::vector<char> > mem;
	mem.push_back(order);
	size_t cycleLength = 0;
	size_t cycleOffset;

	for (size_t k = 0; k < (size_t) 1000000000; ++k)
	{
		for (size_t i = 0; i < vMoves.size(); ++i)
		{
			switch (vMoves[i].type)
			{
				case 's':
				{
					const int nS = vMoves[i].x1;
					for (int i = 0; i < nS; ++i)
						tmp[i] = order[16-nS+i];
					for (int i = 0; i < 16-nS; ++i)
						tmp[nS+i] = order[i];

					tmp.swap(order);

					break;
				}

				case 'x':
				{
					std::swap(order[vMoves[i].x1], order[vMoves[i].x2]);
					break;
				}
				case 'p':
				{
					const char& pa = vMoves[i].x1;
					const char& pb = vMoves[i].x2;

					size_t posa = 0;
					while (order[posa] != pa)
						++posa;
					size_t posb = 0;
					while (order[posb] != pb)
						++posb;

					std::swap(order[posa], order[posb]);

					break;
				}
				default: throw;
			}
		}

		if (k == 0)
			order1 = order;

		// check for cycles
		++cycleLength;
		bool foundCycle = false;
		for (size_t i = 0; i < cycleLength; ++i)
		{
			bool same = true;
			for (size_t j = 0; j < 16; ++j)
			{
				if (mem[i][j] != order[j])
				{
					same = false;
					break;
				}
			}
			if (same)
			{
				foundCycle = true;
				cycleOffset = i;
				cycleLength -= i;
			}
		}

		if (foundCycle)
			break;

		mem.push_back(order);
	}

	// post-process for part a
	order1.resize(17);
	order1[16] = '\0';

	// post-process for part b
	size_t pos = cycleOffset + ((size_t) 1000000000 - cycleOffset) % cycleLength;
	mem[pos].resize(17);
	mem[pos][16] = '\0';

	writeSolution(&order1[0], &mem[pos][0]);
}


