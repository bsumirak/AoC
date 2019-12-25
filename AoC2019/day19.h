/*
 * day19.h
 *
 *  Created on: 2019-12-19
 *      Author: mbreit
 */

#include "classes/intCodeMachine.h"


bool testPos(const std::vector<int64_t>& opCode, std::size_t x, std::size_t y)
{
	IntCodeMachine<int64_t> robot(opCode);
	robot.setMemorySize(1000);
	std::vector<int64_t> input = {int64_t (x), int64_t(y)};
	std::vector<int64_t> output;
	robot.execute(input, output);

	return output[0] == 1;
}


bool fits(const std::vector<int64_t>& opCode, std::size_t x, std::size_t y)
{
	if (!testPos(opCode, x, y))
		return false;
	if (!testPos(opCode, x+99, y))
		return false;
	if (!testPos(opCode, x, y+99))
		return false;
	return true;
}


template <>
void executeDay<19>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	// read program
	std::vector<int64_t> opCode;
	{
		std::ifstream infile(fn.c_str());
		int64_t id;
		while (infile >> id)
			opCode.push_back(id);
	}


	// part a
	int sola = 0;
	for (std::size_t y = 0; y < 50; ++y)
		for (std::size_t x = 0; x < 50; ++x)
			if (testPos(opCode, x, y))
				++sola;


	// part b
	std::size_t y = 100;
	std::size_t x = 0;
	while (!testPos(opCode, x, y))
		++x;
	std::size_t x1 = x+1;  // safety

	while (testPos(opCode, x, y))
		++x;
	std::size_t x2 = x-1;  // safety

	y = (100 * (100 + x1)) / (x2 - x1);
	x = (x2*y) / 100 - 100;

	bool goOn = true;
	while (goOn)
	{
		goOn = false;

		if (fits(opCode, x, y-1))
		{
			goOn = true;
			--y;
		}

		if (fits(opCode, x-1, y))
		{
			goOn = true;
			--x;
		}


		if (fits(opCode, x-1, y-1))
		{
			goOn = true;
			--x;
			--y;
		}

		if (!goOn)
			break;
	}

	std::size_t solb = 10000*x + y;

	writeSolution(sola, solb);
}


