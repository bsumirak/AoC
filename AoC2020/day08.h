/*
 * day08.h
 *
 *  Created on: 2020-12-08
 *      Author: mbreit
 */


template <>
void executeDay<8>(const std::string& fn)
{
	// read input
	struct OpCode
	{
		std::string op;
		int arg;
	};

	std::vector<OpCode> code;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		while (std::getline(infile, line))
		{
			std::istringstream iss(line);
			code.resize(code.size() + 1);
			OpCode& instr = code.back();
			iss >> instr.op;
			iss >> instr.arg;
		}
		infile.close();
	}
	const std::size_t numLines = code.size();



	// part a
	std::size_t ip = 0;
	int resA = 0;
	std::vector<bool> wasHere(numLines, false);
	while (ip < numLines)
	{
		if (wasHere[ip])
			break;
		wasHere[ip] = true;
		const OpCode& instr = code[ip];
		if (instr.op == "jmp")
			ip += instr.arg - 1;
		else if (instr.op == "acc")
			resA += instr.arg;
		++ip;
	}


	// part b
	int resB = 0;
	for (std::size_t i = 0; i < numLines; ++i)
	{
		if (code[i].op == "jmp")
			code[i].op = "nop";
		else if (code[i].op == "nop")
			code[i].op = "jmp";
		else
			continue;


		std::size_t ip = 0;
		std::vector<bool> wasHere(numLines, false);
		resB = 0;
		while (ip < numLines)
		{
			if (wasHere[ip])
				break;
			wasHere[ip] = true;
			const OpCode& instr = code[ip];
			if (instr.op == "jmp")
				ip += instr.arg - 1;
			else if (instr.op == "acc")
				resB += instr.arg;
			++ip;
		}

		if (ip == numLines)
			break;
		else
		{
			if (code[i].op == "jmp")
				code[i].op = "nop";
			else if (code[i].op == "nop")
				code[i].op = "jmp";
		}
	}


	writeSolution(resA, resB);
}


