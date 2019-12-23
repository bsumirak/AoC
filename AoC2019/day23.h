/*
 * day23.h
 *
 *  Created on: 2019-12-23
 *      Author: mbreit
 */


template <>
void executeDay<23>(const std::string& fn)
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

	std::vector<IntCodeMachine<int64_t> > icm(50, opCode);
	std::vector<std::vector<int64_t> > input(50);
	std::vector<std::vector<int64_t> > output(50);
	for (std::size_t i = 0; i < 50; ++i)
	{
		icm[i].setMemorySize(100000);
		input[i].push_back(i);
	}


	// part a
	int64_t sola = -1;
	while (true)
	{
		bool doBreak = false;
		for (std::size_t i = 0; i < 50; ++i)
		{
			if (!input[i].size())
				input[i].push_back(-1);
			output[i].clear();
			icm[i].execute(input[i], output[i]);
			input[i].clear();

			const std::size_t oSz = output[i].size();
			for (std::size_t j = 0; j < oSz; j += 3)
			{
				if (output[i][j] == int64_t(255))
				{
					sola = output[i][j+2];
					doBreak = true;
					break;
				}

				input[output[i][j]].push_back(output[i][j+1]);
				input[output[i][j]].push_back(output[i][j+2]);
			}
		}
		if (doBreak)
			break;
	}


	// part b
	for (std::size_t i = 0; i < 50; ++i)
	{
		icm[i].reset(opCode);
		input[i].clear();
		input[i].push_back(i);
	}

	int64_t solb = -1;
	std::pair<int64_t, int64_t> natData = {0, 0};
	while (true)
	{
		bool doBreak = false;
		for (std::size_t i = 0; i < 50; ++i)
		{
			if (!input[i].size())
				input[i].push_back(-1);
			output[i].clear();
			icm[i].execute(input[i], output[i]);
			input[i].clear();

			const std::size_t oSz = output[i].size();
			for (std::size_t j = 0; j < oSz; j += 3)
			{
				if (output[i][j] == int64_t(255))
				{
					natData.first = output[i][j+1];
					natData.second = output[i][j+2];
					doBreak = true;
				}
				else
				{
					input[output[i][j]].push_back(output[i][j+1]);
					input[output[i][j]].push_back(output[i][j+2]);
				}
			}
		}

		if (doBreak)
		{
			doBreak = false;
			bool doSend = true;
			for (std::size_t i = 0; i < 50; ++i)
			{
				if (input[i].size())
				{
					doSend = false;
					break;
				}
			}
			if (doSend)
			{
				if (solb == natData.second)
					doBreak = true;
				solb = natData.second;
				input[0].push_back(natData.first);
				input[0].push_back(natData.second);
			}
		}

		if (doBreak)
			break;
	}


	writeSolution(sola, solb);
}


