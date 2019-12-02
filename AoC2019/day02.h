/*
 * day02.h
 *
 *  Created on: 2018-12-02
 *      Author: mbreit
 */

#include <algorithm>


void runProgram(std::vector<int>& opCode)
{
	int* instr = &opCode[0];

	bool doBreak = false;
	while (!doBreak)
	{
		switch (*instr)
		{
			case 1:
			{
				int sum = opCode[*++instr];
				sum += opCode[*++instr];
				opCode[*++instr] = sum;
				break;
			}
			case 2:
			{
				int prod = opCode[*++instr];
				prod *= opCode[*++instr];
				opCode[*++instr] = prod;
				break;
			}
			case 99:
				doBreak = true;
				break;
			default:
				throw new std::runtime_error("Wrong op.");
		}
		++instr;
	}
}


template <>
void executeDay<2>(const std::string& fn)
{
	std::vector<int> opCode;

	{
		std::ifstream infile(fn.c_str());
		int id;
		while (infile >> id)
			opCode.push_back(id);
	}
	std::vector<int> vCopy = opCode;


	// part a
	opCode[1] = 12;
	opCode[2] = 2;
	runProgram(opCode);
	int sola = opCode[0];

	// part b
	int noun = 0;
	int verb = 0;
	bool doBreak = false;
	for (; noun < 100; ++noun)
	{
		for (verb = 0; verb < 100; ++verb)
		{
			opCode = vCopy;
			opCode[1] = noun;
			opCode[2] = verb;
			runProgram(opCode);
			if (opCode[0] == 19690720)
			{
				doBreak = true;
				break;
			}
		}
		if (doBreak)
			break;
	}

	if (!doBreak)
		throw new std::runtime_error("Desired end state not reached.");

	int solb = 100*noun + verb;

	writeSolution(sola, solb);
}


