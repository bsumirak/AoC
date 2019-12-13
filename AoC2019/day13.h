/*
 * day13.h
 *
 *  Created on: 2019-12-13
 *      Author: mbreit
 */

#include "classes/intCodeMachine.h"


char code2Tile(int64_t code)
{
	switch (code)
	{
		case 0:
			return ' ';
		case 1:
			return 'w';
		case 2:
			return '#';
		case 3:
			return '_';
		case 4:
			return 'o';
		default:
			std::cout << "wrong: " << code << std::endl;
			return ' ';
	}
}


void printScreen(const std::vector<std::vector<int64_t> >& screen)
{
	const std::size_t nRows = screen.size();
	const std::size_t nCols = screen[0].size();
	for (std::size_t r = 0; r < nRows; ++r)
	{
		for (std::size_t c = 0; c < nCols; ++c)
			std::cout << code2Tile(screen[r][c]);
		std::cout << std::endl;
	}
}



template <>
void executeDay<13>(const std::string& fn)
{
	std::vector<int64_t> opCode;

	// read program
	{
		std::ifstream infile(fn.c_str());
		int64_t id;
		while (infile >> id)
			opCode.push_back(id);
	}


	// part a
	IntCodeMachine<int64_t> game(opCode);
	game.setMemorySize(100000);
	std::vector<int64_t> input;
	std::vector<int64_t> output;
	game.execute(input, output);
	const std::size_t sz = output.size();

	int sola = 0;
	std::vector<std::vector<int64_t> > screen(100, std::vector<int64_t>(100, 0));
	std::size_t nCols = std::numeric_limits<std::size_t>::min();
	std::size_t nRows = std::numeric_limits<std::size_t>::min();
	for (std::size_t i = 0; i < sz; i += 3)
	{
		std::size_t x = output[i];
		std::size_t y = output[i+1];
		nCols = std::max(nCols, x+1);
		nRows = std::max(nRows, y+1);
		screen[y][x] = output[i+2];

		if (screen[y][x] == 2)
			++sola;
	}


	// part b
	screen.resize(nRows);
	int64_t paddleX = 0;
	for (std::size_t r = 0; r < nRows; ++r)
	{
		screen[r].resize(nCols);
		for (std::size_t c = 0; c < nCols; ++c)
		{
			if (screen[r][c] == 3)
				paddleX = c;

		}
	}

	int64_t score = 0;
	int64_t solb = 0;
	opCode[0] = 2;
	game.reset(opCode);
	output.clear();
	input.resize(1, 0);
	int cnt = 0;
	do
	{
		++cnt;
		game.execute(input, output);

		input[0] = 0;

		// process output / set next input
		const std::size_t oSz = output.size();
		for (std::size_t o = 0; o < oSz; o += 3)
		{
			if (output[o] == -1 && output[o+1] == 0)
				score = output[o+2];
			else
			{
				screen[output[o+1]][output[o]] = output[o+2];

				if (output[o+2] == 4)
				{
					if (output[o] < paddleX)
					{
						--paddleX;
						input[0] = -1;
					}
					else if (output[o] > paddleX)
					{
						++paddleX;
						input[0] = 1;
					}
				}
			}
		}

		output.clear();
	}
	while (game.state() == IntCodeMachine<int64_t>::ICMS_WAITING_FOR_INPUT);
	solb = score;

	writeSolution(sola, solb);
}


