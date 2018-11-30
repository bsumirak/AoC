/*
 * day08.h
 *
 *  Created on: 08.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<8>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::string line;

	// part a
	std::map<std::string, int> reg;
	int maxb = std::numeric_limits<int>::min();
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		std::string affReg;
		iss >> affReg;

		// create reg if not present already
		if (reg.find(affReg) == reg.end())
			reg[affReg] = 0;

		std::string op;
		iss >> op;

		std::string tmp;
		iss >> tmp;
		int opVal = atoi(tmp.c_str());
		if (op == "dec")
			opVal *= -1;

		iss >> tmp; // ignore "if"

		std::string condReg;
		iss >> condReg;

		if (reg.find(condReg) == reg.end())
			reg[condReg] = 0;

		std::string comp;
		iss >> comp;

		iss >> tmp;
		int compVal = atoi(tmp.c_str());

		// perform action
		bool doAdd = false;
		if ((comp == "<" && reg[condReg] < compVal)
			|| (comp == ">" && reg[condReg] > compVal)
			|| (comp == "<=" && reg[condReg] <= compVal)
			|| (comp == ">=" && reg[condReg] >= compVal)
			|| (comp == "==" && reg[condReg] == compVal)
			|| (comp == "!=" && reg[condReg] != compVal)
		)
		{
			reg[affReg] += opVal;
			if (reg[affReg] > maxb)
				maxb = reg[affReg];
		}
	}

	// search max after all instructions
	std::map<std::string, int>::iterator it = reg.begin();
	std::map<std::string, int>::iterator itEnd = reg.end();
	int maxa = std::numeric_limits<int>::min();
	for (; it != itEnd; ++it)
	{
		if (it->second > maxa)
			maxa = it->second;
	}

	// solution output
	writeSolution(maxa, maxb);
}


