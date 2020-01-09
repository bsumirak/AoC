/*
 * day25.h
 *
 *  Created on: 2019-12-25
 *      Author: mbreit
 */

#include "classes/intCodeMachine.h"


void commandToDroid(const std::string& cmd, std::vector<int64_t>& input)
{
	const std::size_t sz = input.size();
	input.resize(sz + cmd.size() + 1);
	for (std::size_t i = 0; i < cmd.size(); ++i)
		input[sz+i] = (int64_t) cmd[i];
	input.back() = int64_t(10);
}


template <>
void executeDay<25>(const std::string& fn)
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
	IntCodeMachine<int64_t> robot(opCode);
	robot.setMemorySize(10000);
	std::vector<int64_t> input;
	std::vector<int64_t> output;

	std::string cmd = "east";
	commandToDroid(cmd, input);

	cmd = "take antenna";
	commandToDroid(cmd, input);

	cmd = "west";
	commandToDroid(cmd, input);

	cmd = "north";
	commandToDroid(cmd, input);

	cmd = "take weather machine";
	commandToDroid(cmd, input);

	cmd = "north";
	commandToDroid(cmd, input);

	cmd = "take klein bottle";
	commandToDroid(cmd, input);

	cmd = "east";
	commandToDroid(cmd, input);

	cmd = "take spool of cat6";
	commandToDroid(cmd, input);

	cmd = "east";
	commandToDroid(cmd, input);

	cmd = "south";
	commandToDroid(cmd, input);

	cmd = "take mug";
	commandToDroid(cmd, input);

	cmd = "north";
	commandToDroid(cmd, input);

	cmd = "north";
	commandToDroid(cmd, input);

	cmd = "west";
	commandToDroid(cmd, input);

	cmd = "north";
	commandToDroid(cmd, input);

	cmd = "take cake";
	commandToDroid(cmd, input);

	cmd = "south";
	commandToDroid(cmd, input);

	cmd = "east";
	commandToDroid(cmd, input);

	cmd = "east";
	commandToDroid(cmd, input);

	cmd = "north";
	commandToDroid(cmd, input);

	cmd = "north";
	commandToDroid(cmd, input);

	cmd = "take tambourine";
	commandToDroid(cmd, input);

	cmd = "south";
	commandToDroid(cmd, input);

	cmd = "south";
	commandToDroid(cmd, input);

	cmd = "south";
	commandToDroid(cmd, input);

	cmd = "take shell";
	commandToDroid(cmd, input);

	cmd = "north";
	commandToDroid(cmd, input);

	cmd = "west";
	commandToDroid(cmd, input);

	cmd = "south";
	commandToDroid(cmd, input);

	cmd = "west";
	commandToDroid(cmd, input);

	cmd = "south";
	commandToDroid(cmd, input);

	cmd = "south";
	commandToDroid(cmd, input);


	std::vector<std::string> inv(8);
	cmd = "drop shell";
	commandToDroid(cmd, input);
	inv[0] = "shell";

	cmd = "drop klein bottle";
	commandToDroid(cmd, input);
	inv[1] = "klein bottle";

	cmd = "drop tambourine";
	commandToDroid(cmd, input);
	inv[2] = "tambourine";

	cmd = "drop spool of cat6";
	commandToDroid(cmd, input);
	inv[3] = "spool of cat6";

	cmd = "drop mug";
	commandToDroid(cmd, input);
	inv[4] = "mug";

	cmd = "drop cake";
	commandToDroid(cmd, input);
	inv[5] = "cake";

	cmd = "drop antenna";
	commandToDroid(cmd, input);
	inv[6] = "antenna";

	cmd = "drop weather machine";
	commandToDroid(cmd, input);
	inv[7] = "weather machine";

	robot.execute(input, output);

	uint perm = 0;

	while (robot.state() == IntCodeMachine<int64_t>::ICMS_WAITING_FOR_INPUT)
	{
		/*
		const std::size_t sz = output.size();
		for (std::size_t i = 0; i < sz; ++i)
			std::cout << (char)(output[i]);
		*/
		output.clear();

		/*
		std::string userInput;
		std::getline(std::cin, userInput);
		input.clear();
		commandToDroid(userInput, input);
		 */

		++perm;
		if (perm == 256)
			break;

		input.clear();
		std::string cmd;
		for (std::size_t i = 0; i < 8; ++i)
		{
			if (!(perm & (uint) 1 << i) && (perm-1 & (uint) 1 << i))
			{
				cmd = "drop " + inv[i];
				commandToDroid(cmd, input);
			}
			else if ((perm & (uint) 1 << i) && !(perm-1 & (uint) 1 << i))
			{
				cmd = "take " + inv[i];
				commandToDroid(cmd, input);
			}

		}
		cmd = "east";
		commandToDroid(cmd, input);

		robot.execute(input, output);
	}

	const std::size_t sz = output.size();
	for (std::size_t i = 217; i < sz; ++i)
		std::cout << (char)(output[i]);

}


