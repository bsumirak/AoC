/*
 * day21.h
 *
 *  Created on: 2018-01-05
 *      Author: mbreit
 */


template <>
void executeDay<21>(const std::string& fn)
{
	// part a (solved on paper)
	int sola = 2792537;


	// part b
	const uint32_t sz = (1 << 24);

	const uint64_t p1 = 65899;
	const uint64_t p2 = (p1*p1) & ((1<<24)-1);
	const uint64_t p3 = (p1*p2) & ((1<<24)-1);
	const uint64_t r3 = 7637914;
	const uint64_t r3p3 = (r3*p3) & ((1<<24)-1);

	std::vector<uint32_t> memo(sz,0);

	uint32_t solb = 0;
	uint64_t r2 = 0;
	uint32_t i = 0;
	while (++i)
	{
		solb = r2;

		r2 = r2 | (1 << 16);
	 	r2 = r3p3 + (r2 & 255)*p3 + ((r2 >> 8) & 255)*p2 + ((r2 >> 16) & 255)*p1;
		r2 = r2 & ((1<<24)-1);

		if (memo[(uint32_t) r2])
			break;
		memo[(uint32_t) r2] = i;
	}

	writeSolution(sola, solb);
}

