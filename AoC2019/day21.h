/*
 * day21.h
 *
 *  Created on: 21.12.2017
 *      Author: mbreit
 */

#include <algorithm>


template <>
void executeDay<21>(const std::string& fn)
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
	int64_t sola = -1;
	{
		IntCodeMachine<int64_t> robot(opCode);
		robot.setMemorySize(10000);
		std::vector<int64_t> input;
		std::vector<int64_t> output;

		input.push_back('N');
		input.push_back('O');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('A');
		input.push_back(' ');
		input.push_back('J');
		input.push_back(10);

		input.push_back('N');
		input.push_back('O');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('B');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(10);

		input.push_back('O');
		input.push_back('R');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('J');
		input.push_back(10);

		input.push_back('N');
		input.push_back('O');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('C');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(10);

		input.push_back('O');
		input.push_back('R');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('J');
		input.push_back(10);

		input.push_back('N');
		input.push_back('O');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('D');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(10);

		input.push_back('N');
		input.push_back('O');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(10);

		input.push_back('A');
		input.push_back('N');
		input.push_back('D');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('J');
		input.push_back(10);

		input.push_back('W');
		input.push_back('A');
		input.push_back('L');
		input.push_back('K');
		input.push_back(10);

		for (auto i : input)
			std::cout << char(i);

		robot.execute(input, output);

		if (output.size() == 34)
			sola = output[33];
		else
		{
			for (auto i : output)
				std::cout << char(i);
		}
	}

	// part b
	int64_t solb = -1;
	{
		IntCodeMachine<int64_t> robot(opCode);
		robot.setMemorySize(10000);
		std::vector<int64_t> input;
		std::vector<int64_t> output;

		input.push_back('N');
		input.push_back('O');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('A');
		input.push_back(' ');
		input.push_back('J');
		input.push_back(10);

		input.push_back('N');
		input.push_back('O');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('B');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(10);

		input.push_back('O');
		input.push_back('R');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('J');
		input.push_back(10);

		input.push_back('N');
		input.push_back('O');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('C');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(10);

		input.push_back('O');
		input.push_back('R');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('J');
		input.push_back(10);

		input.push_back('N');
		input.push_back('O');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('D');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(10);

		input.push_back('N');
		input.push_back('O');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(10);

		input.push_back('A');
		input.push_back('N');
		input.push_back('D');
		input.push_back(' ');
		input.push_back('T');
		input.push_back(' ');
		input.push_back('J');
		input.push_back(10);

		input.push_back('R');
		input.push_back('U');
		input.push_back('N');
		input.push_back(10);

		for (auto i : input)
			std::cout << char(i);

		robot.execute(input, output);

		if (output.size() == 34)
			sola = output[33];
		else
		{
			for (auto i : output)
				std::cout << char(i);
		}
	}


	writeSolution(sola, solb);
}

