/*
 * day09.h
 *
 *  Created on: 2019-12-09
 *      Author: mbreit
 */

#include "classes/intCodeMachine.h"


template <>
void executeDay<9>(const std::string& fn)
{
	std::vector<int64_t> opCode;

	// read program
	{
		std::ifstream infile(fn.c_str());
		int id;
		while (infile >> id)
			opCode.push_back(id);
	}

	// part a
	IntCodeMachine<int64_t> icm(opCode);
	icm.setMemorySize(10000);
	std::vector<int64_t> input(1, 1);
	std::vector<int64_t> output;
	icm.execute(input, output);
	int64_t sola = output[0];

	// part b
	icm.reset(opCode);
	icm.setMemorySize(10000);
	input[0] = 2;
	output.clear();
	icm.execute(input, output);
	int64_t solb = output[0];

	// solution output
	writeSolution(sola, solb);
}


