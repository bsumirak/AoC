/*
 * day05.h
 *
 *  Created on: 2019-12-05
 *      Author: mbreit
 */

#include "classes/intCodeMachine.h"


template <>
void executeDay<5>(const std::string& fn)
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
	int sola = 0;
	IntCodeMachine<int> icm(opCode);
	std::vector<int> inputs(1, 1);
	std::vector<int> outputs;
	icm.execute(inputs, outputs);
	if (!outputs.size())
		std::cout << "Program did not return output in part a." << std::endl;
	else
		sola = outputs.back();


	// part b
	int solb = 0;
	inputs[0] = 5;
	outputs.clear();
	icm.reset(opCode);
	icm.execute(inputs, outputs);
	if (!outputs.size())
		std::cout << "Program did not return output in part b." << std::endl;
	else
		solb = outputs.back();

	writeSolution(sola, solb);
}


