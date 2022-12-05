/*
 * day05.h
 *
 *  Created on: 2022-12-05
 *      Author: mbreit
 */


template <>
void executeDay<5>(const std::string& fn)
{
	std::array<std::stack<char>, 9> stacks;
	stacks[0].push('G');
	stacks[0].push('F');
	stacks[0].push('V');
	stacks[0].push('H');
	stacks[0].push('P');
	stacks[0].push('S');

	stacks[1].push('G');
	stacks[1].push('J');
	stacks[1].push('F');
	stacks[1].push('B');
	stacks[1].push('V');
	stacks[1].push('D');
	stacks[1].push('Z');
	stacks[1].push('M');

	stacks[2].push('G');
	stacks[2].push('M');
	stacks[2].push('L');
	stacks[2].push('J');
	stacks[2].push('N');

	stacks[3].push('N');
	stacks[3].push('G');
	stacks[3].push('Z');
	stacks[3].push('V');
	stacks[3].push('D');
	stacks[3].push('W');
	stacks[3].push('P');

	stacks[4].push('V');
	stacks[4].push('R');
	stacks[4].push('C');
	stacks[4].push('B');

	stacks[5].push('V');
	stacks[5].push('R');
	stacks[5].push('S');
	stacks[5].push('M');
	stacks[5].push('P');
	stacks[5].push('W');
	stacks[5].push('L');
	stacks[5].push('Z');

	stacks[6].push('T');
	stacks[6].push('H');
	stacks[6].push('P');

	stacks[7].push('Q');
	stacks[7].push('R');
	stacks[7].push('S');
	stacks[7].push('N');
	stacks[7].push('C');
	stacks[7].push('H');
	stacks[7].push('Z');
	stacks[7].push('V');

	stacks[8].push('F');
	stacks[8].push('L');
	stacks[8].push('G');
	stacks[8].push('P');
	stacks[8].push('V');
	stacks[8].push('Q');
	stacks[8].push('J');

	std::array<std::stack<char>, 9> stacksCpy = stacks;

	// read input
	unsigned n, f, t;
	std::vector<char> tmp;
	std::ifstream infile(fn.c_str());
	while (infile >> n)
	{
		infile >> f;
		infile >> t;

		// part a
		for (unsigned i = 0; i < n; ++i)
		{
			stacks[t - 1].push(stacks[f - 1].top());
			stacks[f - 1].pop();
		}

		// part b
		tmp.resize(n);
		for (unsigned i = 0; i < n; ++i)
		{
			tmp[n - i - 1] = stacksCpy[f - 1].top();
			stacksCpy[f - 1].pop();
		}
		for (unsigned i = 0; i < n; ++i)
			stacksCpy[t - 1].push(tmp[i]);
	}
	std::string resA;
	std::string resB;
	for (size_t i = 0; i < 9; ++i)
	{
		resA += stacks[i].top();
		resB += stacksCpy[i].top();
	}

	writeSolution(resA, resB);
}


