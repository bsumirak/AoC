/*
 * day17.h
 *
 *  Created on: 2019-12-17
 *      Author: mbreit
 */


template <>
void executeDay<17>(const std::string& fn)
{
	std::vector<int64_t> opCode;

	// read program
	{
		std::ifstream infile(fn.c_str());
		int64_t id;
		while (infile >> id)
			opCode.push_back(id);
	}
	std::vector<int64_t> codeCp = opCode;

	// prepare and run robot
	IntCodeMachine<int64_t> robot(opCode);
	robot.setMemorySize(100000);
	std::vector<int64_t> input(0);
	std::vector<int64_t> output;
	robot.execute(input, output);

	// save the map
	const std::size_t sz = output.size();
	std::string printMap;
	std::vector<std::vector<int> > map(1);
	for (std::size_t o = 0; o < sz-1; ++o)
	{
		printMap += (char) output[o];

		if (output[o] == 10)
		{
			if (o != sz-2)
				map.resize(map.size()+1);
		}

		else if (output[o] == 46)
			map.back().push_back(0);

		else
			map.back().push_back(1);
	}

	// find junctions on map
	int sola = 0;
	const std::size_t nRows = map.size();
	const std::size_t nCols = map[0].size();
	for (std::size_t r = 1; r < nRows-1; ++r)
	{
		for (std::size_t c = 1; c < nCols-1; ++c)
		{
			if (map[r][c] && map[r+1][c] && map[r-1][c]
				&& map[r][c+1] && map[r][c-1])
				sola += r*c;
		}
	}


	// part b
	opCode = codeCp;
	opCode[0] = 2;

	// print the map
	std::cout << printMap << std::endl;

	// give move instructions
	input.push_back('A');
	input.push_back(',');
	input.push_back('A');
	input.push_back(',');
	input.push_back('B');
	input.push_back(',');
	input.push_back('C');
	input.push_back(',');
	input.push_back('B');
	input.push_back(',');
	input.push_back('C');
	input.push_back(',');
	input.push_back('B');
	input.push_back(',');
	input.push_back('C');
	input.push_back(',');
	input.push_back('C');
	input.push_back(',');
	input.push_back('A');
	input.push_back(10);

	input.push_back('L');
	input.push_back(',');
	input.push_back('1');
	input.push_back('0');
	input.push_back(',');
	input.push_back('R');
	input.push_back(',');
	input.push_back('8');
	input.push_back(',');
	input.push_back('R');
	input.push_back(',');
	input.push_back('8');
	input.push_back(10);

	input.push_back('L');
	input.push_back(',');
	input.push_back('1');
	input.push_back('0');
	input.push_back(',');
	input.push_back('L');
	input.push_back(',');
	input.push_back('1');
	input.push_back('2');
	input.push_back(',');
	input.push_back('R');
	input.push_back(',');
	input.push_back('8');
	input.push_back(',');
	input.push_back('R');
	input.push_back(',');
	input.push_back('1');
	input.push_back('0');
	input.push_back(10);

	input.push_back('R');
	input.push_back(',');
	input.push_back('1');
	input.push_back('0');
	input.push_back(',');
	input.push_back('L');
	input.push_back(',');
	input.push_back('1');
	input.push_back('2');
	input.push_back(',');
	input.push_back('R');
	input.push_back(',');
	input.push_back('1');
	input.push_back('0');
	input.push_back(10);

	// whether to give continuous visual output
	input.push_back('n');
	input.push_back(10);

	// run robot
	robot.reset(opCode);
	output.clear();
	robot.execute(input, output);

	// give continuous output if opted for
	if (input[input.size()-2] == 'y')
	{
		const std::size_t oSz = output.size();
		std::size_t cnt = std::size_t(-1);
		while (++cnt < oSz-1)
			std::cout << (char) output[cnt];
	}

	int solb = output.back();

	writeSolution(sola, solb);
}


