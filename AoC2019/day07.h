/*
 * day07.h
 *
 *  Created on: 2019-12-07
 *      Author: mbreit
 */

#include "classes/intCodeMachine.h"


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
		output[0] = 0;
		for (std::size_t b = 0; b < 5; ++b)
		{
			icm[b].reset(opCode);
			input[0] = phaseInput[b];
			input[1] = output[0];
			output.clear();
			icm[b].execute(input, output);
		}
		sola = std::max(sola, output[0]);
	}
	while (std::next_permutation(phaseInput.begin(), phaseInput.end()));


	// part b
	for (std::size_t i = 0; i < 5; ++i)
		phaseInput[i] = i+5;

	int solb = -std::numeric_limits<int>::max();
	do
	{
		int lastOutput = 0;
		int loopCnt = 0;
		output[0] = 0;
		for (std::size_t b = 0; b < 5; ++b)
		{
			icm[b].reset(opCode);
			icm[b].setHaltOnOutput(true);
		}
		while (icm[4].state() != IntCodeMachine<int>::ICMS_FINISHED)
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
				icm[b].execute(input, output);
			}
			if (icm[4].state() != IntCodeMachine<int>::ICMS_FINISHED)
				lastOutput = output[0];
			++loopCnt;
		}
		solb = std::max(solb, lastOutput);
	}
	while (std::next_permutation(phaseInput.begin(), phaseInput.end()));


	writeSolution(sola, solb);
}

