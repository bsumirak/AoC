/*
 * day10.h
 *
 *  Created on: 2022-12-10
 *      Author: mbreit
 */


template <>
void executeDay<10>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());
	unsigned cycle = 0;
	int x = 1;
	int resA = 0;
	std::string screen(240, ' ');

	auto incCycleAndEval = [&]()
	{
		++cycle;

		// part a
		if ((cycle + 20u) % 40u == 0u)
			resA += x * cycle;
		// part b
		if (abs((int)(cycle % 40u) -1 - x) <= 1)
			screen[cycle-1] = '#';
	};

	std::string s;
	while (infile >> s)
	{
		incCycleAndEval();

		if (s == "addx")
		{
			incCycleAndEval();

			int i;
			infile >> i;
			x += i;
		}
		if (cycle > 240)
			break;
	}
	infile.close();

	std::string resB(246, ' ');
	for (size_t i = 0; i < 246; ++i)
	{
		if (i%41 == 0)
			resB[i] = '\n';
		else
			resB[i] = screen[i - i/41 - 1];
	}

	writeSolution(resA, resB);
}


