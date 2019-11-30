/*
 * day23.h
 *
 *  Created on: 23.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<23>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::string line;

	std::vector<std::string> vInstr;
	vInstr.reserve(1000);

	// read data
	while (std::getline(infile, line))
		vInstr.push_back(line);
	size_t sz = vInstr.size();

	// part a
	int sola = 0;
	{
		std::vector<int64_t> reg(8, 0);

		size_t sz = vInstr.size();
		int pos = 0;
		int lastFreq = 0;
		while (pos >= 0 && pos < (int) sz)
		{
			std::istringstream iss(vInstr[pos]);
			std::string instr;

	//std::cout << vInstr[pos] << std::endl;

			iss >> instr;




			std::string next;
			iss >> next;

			int arg1I;
			bool arg1IsReg = true;
			if (next[0] - 'a' < 8 && next[0] - 'a' >= 0)
			{
				arg1I = next[0] - 'a';
				arg1IsReg = true;
			}
			else
			{
				arg1I = std::stoi(next);
				arg1IsReg = false;
			}



			int arg2I;
			bool arg2IsReg = false;
			iss >> next;
			if (next[0] - 'a' < 8 && next[0] - 'a' >= 0)
			{
				arg2I = next[0] - 'a';
				arg2IsReg = true;
			}
			else
			{
				arg2I = std::stoi(next);
				arg2IsReg = false;
			}

//std::cout << instr << " " << (arg1IsReg ? "r" : "") << arg1I << " " << (arg2IsReg ? "r" : "") << arg2I << std::endl;




			if (instr == "set")
			{
				if (arg2IsReg)
					reg[arg1I] = reg[arg2I];
				else
					reg[arg1I] = arg2I;
			}
			else if (instr == "sub")
			{
				if (arg2IsReg)
					reg[arg1I] = reg[arg1I] - reg[arg2I];
				else
					reg[arg1I] = reg[arg1I] - arg2I;
			}
			else if (instr == "mul")
			{
				if (arg2IsReg)
					reg[arg1I] = reg[arg1I] * reg[arg2I];
				else
					reg[arg1I] = reg[arg1I] * arg2I;

				++sola;
			}
			else if (instr == "jnz")
			{
				if (arg1IsReg)
				{
					if (reg[arg1I] != 0)
					{
						if (arg2IsReg)
							pos = pos + reg[arg2I] - 1;
						else
							pos = pos + arg2I - 1;
					}
				}
				else
				{
					if (arg1I != 0)
					{
						if (arg2IsReg)
							pos = pos + reg[arg2I] - 1;
						else
							pos = pos + arg2I - 1;
					}
				}
			}
			else throw;

			++pos;
		}
	}

	// part b: find non-prime numbers in [108100, 125100]
	int last = 354;
	std::vector<bool> sieve(355, true);
	std::vector<bool> zone(17001, true);
	for (int i = 2; i <= last; ++i)
	{
		if (!sieve[i])
			continue;

		// shoot in sieve
		for (int j = 2*i; j <= last; j += i)
			sieve[j] = false;

		// shoot in zone
		int rest = 108100 % i;
		int start = (i - rest) % i;

		for (int j = start; j < 17001; j += i)
			zone[j] = false;
	}

	size_t cnt = 0;
	for (size_t i = 0; i < 17001; i += 17)
		if (!zone[i])
			++cnt;

	writeSolution(sola, cnt);
}


