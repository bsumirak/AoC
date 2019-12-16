/*
 * day16.h
 *
 *  Created on: 2019-12-16
 *      Author: mbreit
 */

#include <cstring>

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
	std::vector<int> code;
	char sign;
	while (infile >> sign)
		code.push_back(sign - '0');

	std::size_t sz = code.size();
	std::vector<int> codeCp = code;;
	std::vector<int> next = code;


	// part a
	for (std::size_t i = 0; i < 100; ++i)
	{
		for (std::size_t j = 0; j < sz; ++j)
		{
			int sum = 0;

			// +1
			std::size_t cnt = 0;
			std::size_t offset = 0;
			while ((4*cnt+1)*(j+1) + offset - 1 < sz)
			{
				while (offset < j+1 && (4*cnt+1)*(j+1) + offset - 1 < sz)
				{
					sum += code[(4*cnt+1)*(j+1) + offset - 1];
					++offset;
				}
				offset = 0;
				++cnt;
			}

			// -1
			cnt = 0;
			offset = 0;
			while ((4*cnt + 3)*(j+1) + offset - 1 < sz)
			{
				while (offset < j+1 && (4*cnt + 3)*(j+1) + offset - 1 < sz)
				{
					sum -= code[(4*cnt+3)*(j+1) + offset - 1];
					++offset;
				}
				offset = 0;
				++cnt;
			}

			next[j] = sum >= 0 ?  sum % 10 : (-sum) % 10;
		}

		code.swap(next);
	}

	int fac = 1;
	int sola = 0;
	for (std::size_t i = 0; i < 8; ++i)
	{
		sola += fac * code[7-i];
		fac *= 10;
	}


	// part b
	int f = 1;
	std::size_t offset = 0;
	for (std::size_t i = 0; i < 7; ++i)
	{
		offset += f * codeCp[6-i];
		f *= 10;
	}

	code.resize(10000 * sz - offset);
	next.resize(10000 * sz - offset);

	std::size_t pos = 10000 * sz - offset;
	std::size_t cnt = 0;
	while (pos > 0)
		code[--pos] = codeCp[sz-1 - (cnt++) % sz];
	sz = 10000 * sz - offset;


	for (std::size_t i = 0; i < 100; ++i)
	{
		next[sz-1] = code[sz-1];
		for (std::size_t j = sz-1; j > 0; --j)
			next[j-1] = (next[j] + code[j-1]) % 10;

		code.swap(next);
	}

	fac = 1;
	int solb = 0;
	for (std::size_t i = 0; i < 8; ++i)
	{
		solb += fac * code[7-i];
		fac *= 10;
	}


	writeSolution(sola, solb);
}


