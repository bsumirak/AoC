/*
 * day16.h
 *
 *  Created on: 2018-12-25
 *      Author: mbreit
 */


enum InstructionType
{
	IT_ADDR = 0,
	IT_ADDI,
	IT_MULR,
	IT_MULI,
	IT_BANR,
	IT_BANI,
	IT_BORR,
	IT_BORI,
	IT_SETR,
	IT_SETI,
	IT_GTIR,
	IT_GTRI,
	IT_GTRR,
	IT_EQIR,
	IT_EQRI,
	IT_EQRR,
	IT_INVL
};


std::vector<uint>& instructionResult
(
	const std::vector<uint>& instr,
	const std::vector<uint>& regBefore,
	std::vector<uint>& regAfter
)
{
	regAfter = regBefore;

	InstructionType it = (InstructionType) instr[0];
	switch (it)
	{
		case IT_ADDR:
			regAfter[instr[3]] = regAfter[instr[1]] + regAfter[instr[2]];
			return regAfter;
		case IT_ADDI:
			regAfter[instr[3]] = regAfter[instr[1]] + instr[2];
			return regAfter;
		case IT_MULR:
			regAfter[instr[3]] = regAfter[instr[1]] * regAfter[instr[2]];
			return regAfter;
		case IT_MULI:
			regAfter[instr[3]] = regAfter[instr[1]] * instr[2];
			return regAfter;
		case IT_BANR:
			regAfter[instr[3]] = regAfter[instr[1]] & regAfter[instr[2]];
			return regAfter;
		case IT_BANI:
			regAfter[instr[3]] = regAfter[instr[1]] & instr[2];
			return regAfter;
		case IT_BORR:
			regAfter[instr[3]] = regAfter[instr[1]] | regAfter[instr[2]];
			return regAfter;
		case IT_BORI:
			regAfter[instr[3]] = regAfter[instr[1]] | instr[2];
			return regAfter;
		case IT_SETR:
			regAfter[instr[3]] = regAfter[instr[1]];
			return regAfter;
		case IT_SETI:
			regAfter[instr[3]] = instr[1];
			return regAfter;
		case IT_GTIR:
			regAfter[instr[3]] = instr[1] > regAfter[instr[2]] ? 1 : 0;
			return regAfter;
		case IT_GTRI:
			regAfter[instr[3]] = regAfter[instr[1]] > instr[2] ? 1 : 0;
			return regAfter;
		case IT_GTRR:
			regAfter[instr[3]] = regAfter[instr[1]] > regAfter[instr[2]] ? 1 : 0;
			return regAfter;
		case IT_EQIR:
			regAfter[instr[3]] = instr[1] == regAfter[instr[2]] ? 1 : 0;
			return regAfter;
		case IT_EQRI:
			regAfter[instr[3]] = regAfter[instr[1]] == instr[2] ? 1 : 0;
			return regAfter;
		case IT_EQRR:
			regAfter[instr[3]] = regAfter[instr[1]] == regAfter[instr[2]] ? 1 : 0;
			return regAfter;
		default:
			std::cout << "Invalid opcode!" << std::endl;
			exit(1);
	}

	return regAfter;
}


template <>
void executeDay<16>(const std::string& fn)
{
	// read input (part 1)
	std::ifstream infile1((fn+'1').c_str());

	std::vector<uint> tmp(4);
	std::vector<std::vector<uint> > vBefore;
	std::vector<std::vector<uint> > vAfter;
	std::vector<std::vector<uint> > vInstr;

	while (infile1 >> tmp[0])
	{
		infile1 >> tmp[1];
		infile1 >> tmp[2];
		infile1 >> tmp[3];
		vBefore.push_back(tmp);

		infile1 >> tmp[0];
		infile1 >> tmp[1];
		infile1 >> tmp[2];
		infile1 >> tmp[3];
		vInstr.push_back(tmp);

		infile1 >> tmp[0];
		infile1 >> tmp[1];
		infile1 >> tmp[2];
		infile1 >> tmp[3];
		vAfter.push_back(tmp);
	}

	const size_t nInstr = vInstr.size();

	size_t cnt = 0;
	std::vector<std::vector<InstructionType> > decrypt(16);
	for (size_t i = 0; i < nInstr; ++i)
	{
		const std::vector<uint>& before = vBefore[i];
		const std::vector<uint>& after = vAfter[i];
		std::vector<uint>& instr = vInstr[i];

		std::vector<uint> tmp(4,0);
		std::vector<InstructionType> vCand;
		const uint origInstr = instr[0];
		instr[0] = IT_ADDR;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_ADDR);
		instr[0] = IT_ADDI;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_ADDI);
		instr[0] = IT_MULR;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_MULR);
		instr[0] = IT_MULI;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_MULI);
		instr[0] = IT_BANR;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_BANR);
		instr[0] = IT_BANI;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_BANI);
		instr[0] = IT_BORR;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_BORR);
		instr[0] = IT_BORI;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_BORI);
		instr[0] = IT_SETR;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_SETR);
		instr[0] = IT_SETI;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_SETI);
		instr[0] = IT_GTIR;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_GTIR);
		instr[0] = IT_GTRI;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_GTRI);
		instr[0] = IT_GTRR;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_GTRR);
		instr[0] = IT_EQIR;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_EQIR);
		instr[0] = IT_EQRI;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_EQRI);
		instr[0] = IT_EQRR;
		if (instructionResult(instr, before, tmp) == after)
			vCand.push_back(IT_EQRR);

		const size_t vcSz = vCand.size();
		if (decrypt[origInstr].size())
		{
			std::vector<InstructionType>& decryptCands = decrypt[origInstr];
			for (size_t i = 0; i < decryptCands.size();)
			{
				InstructionType it = decryptCands[i];
				size_t j = 0;
				for (; j < vcSz; ++j)
					if (vCand[j] == it)
						break;
				if (j == vcSz)
					decryptCands.erase(decryptCands.begin() + i);
				else
					++i;
			}
		}
		else
		{
			for (size_t i = 0; i < vcSz; ++i)
				decrypt[origInstr].push_back(vCand[i]);
		}

		if (vcSz >= 3)
			++cnt;
	}

	// postprocess decrypt data
	std::vector<InstructionType> opCode2Instr(16, IT_INVL);
	bool foundOne = true;
	while (foundOne)
	{
		foundOne = false;
		for (size_t i = 0; i < 16; ++i)
		{
			if (decrypt[i].size() == 1)
			{
				foundOne = true;
				opCode2Instr[i] = decrypt[i][0];
			}

			for (size_t j = 0; j < 16; ++j)
			{
				for (size_t k = 0; k < decrypt[j].size();)
				{
					if (decrypt[j][k] == opCode2Instr[i])
						decrypt[j].erase(decrypt[j].begin() + k);
					else
						++k;
				}
			}
		}
	}

/*
	for (size_t i = 0; i < 16; ++i)
	{
		std::cout << i << ":";
		for (size_t j = 0; j < decrypt[i].size(); ++j)
			std::cout << " " << decrypt[i][j];
		std::cout << std::endl;
	}
*/

	// read input (part 2)
	std::ifstream infile2((fn+'2').c_str());
	std::vector<std::vector<uint> > program;
	while (infile2 >> tmp[0])
	{
		infile2 >> tmp[1];
		infile2 >> tmp[2];
		infile2 >> tmp[3];
		program.push_back(tmp);
	}

	// execute program
	std::vector<uint> reg(4, 0);
	const size_t nProgInstr = program.size();
	for (size_t i = 0; i < nProgInstr; ++i)
	{
		program[i][0] = opCode2Instr[program[i][0]];
		instructionResult(program[i], reg, reg);
	}

	writeSolution(cnt, reg[0]);
}


