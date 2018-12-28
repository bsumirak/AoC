/*
 * day19.h
 *
 *  Created on: 2018-12-28
 *      Author: mbreit
 */


// needs inclusion of day 16!

template <>
void executeDay<19>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());

	std::vector<std::vector<uint> > vInstr;

	std::string line;
	infile >> line;
	size_t ip;
	infile >> ip;

	while (infile >> line)
	{
		vInstr.resize(vInstr.size() + 1);
		std::vector<uint>& instr = vInstr.back();
		instr.resize(4);
		if (line == "addr")
			instr[0] = IT_ADDR;
		else if (line == "addi")
			instr[0] = IT_ADDI;
		else if (line == "mulr")
			instr[0] = IT_MULR;
		else if (line == "muli")
			instr[0] = IT_MULI;
		else if (line == "banr")
			instr[0] = IT_BANR;
		else if (line == "bani")
			instr[0] = IT_BANI;
		else if (line == "borr")
			instr[0] = IT_BORR;
		else if (line == "bori")
			instr[0] = IT_BORI;
		else if (line == "setr")
			instr[0] = IT_SETR;
		else if (line == "seti")
			instr[0] = IT_SETI;
		else if (line == "gtir")
			instr[0] = IT_GTIR;
		else if (line == "gtri")
			instr[0] = IT_GTRI;
		else if (line == "gtrr")
			instr[0] = IT_GTRR;
		else if (line == "eqir")
			instr[0] = IT_EQIR;
		else if (line == "eqri")
			instr[0] = IT_EQRI;
		else if (line == "eqrr")
			instr[0] = IT_EQRR;
		else
			instr[0] = IT_INVL;

		infile >> instr[1];
		infile >> instr[2];
		infile >> instr[3];
	}

	// part a
	std::vector<uint> reg(6,0);
	uint& pc = reg[ip];
	while (pc < vInstr.size())
	{
		instructionResult(vInstr[pc], reg, reg);
		++pc;
	}
	uint sola = reg[0];


	// part b (algorithm calculates sum of all divisors)
	int solb = 0;
	int a = 10551432;
	int s = sqrt(a);
	for (int i = 1; i <= s; ++i)
		if (a % i == 0)
			solb += i + (a/i);


	writeSolution(sola, solb);
}


