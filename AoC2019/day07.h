/*
 * day07.h
 *
 *  Created on: 2019-12-07
 *      Author: mbreit
 */

#include "classes/intCodeMachine.h"
#include <array>


template <>
void executeDay<7>(const std::string& fn)
{
	std::vector<int> opCode;

	// read program
	{
		std::ifstream infile(fn.c_str());
		int id;
		while (infile >> id)
			opCode.push_back(id);
	}


	// part a
	std::vector<int> phaseInput(5);
	for (std::size_t i = 0; i < 5; ++i)
		phaseInput[i] = i;

	std::array<IntCodeMachine<int>, 5> icm;
	int sola = -std::numeric_limits<int>::max();
	std::vector<int> output(1, 0);
	std::vector<int> input(2, 0);
	do
	{
		for (std::size_t b = 0; b < 5; ++b)
		{
			icm[b].setOpCode(opCode);
			input[0] = phaseInput[b];
			input[1] = output[0];
			output.clear();
			icm[b].execute(input, output);
		}
		sola = std::max(sola, output[0]);
	}
	while (std::next_permutation(phaseInput.begin(), phaseInput.end()));


/*
	std::vector<int> phaseInput(5);
	for (std::size_t i = 0; i < 5; ++i)
		phaseInput[i] = i+5;

	int maxOutput = -std::numeric_limits<int>::max();
	std::vector<int> output(1, 0);
	std::vector<int> input(2, 0);
	do
	{
		std::vector<std::vector<int> > vCopy(5, opCode);
		int loopCnt = 0;
		int lastOutput = 0;
		std::vector<std::size_t> retVal(5, 0);
		output[0] = 0;
		while (retVal[4] != std::size_t(-1))
		{
			for (std::size_t b = 0; b < 5; ++b)
			{
				if (!loopCnt)
				{
					input[0] = phaseInput[b];
					input[1] = output[0];
				}
				else
				{
					input[0] = output[0];
				}
				output.clear();
				retVal[b] = runProgram7(vCopy[b], output, &input, retVal[b]);
			}
			if (retVal[4] != std::size_t(-1))
				lastOutput = output[0];
			++loopCnt;
		}
		maxOutput = std::max(maxOutput, lastOutput);
	}
	while (std::next_permutation(phaseInput.begin(), phaseInput.end()));
*/

	writeSolution(sola, 0);
}

