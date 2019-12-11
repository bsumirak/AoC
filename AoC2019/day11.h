/*
 * day11.h
 *
 *  Created on: 2019-12-11
 *      Author: mbreit
 */

#include "classes/intCodeMachine.h"


template <>
void executeDay<11>(const std::string& fn)
{
	std::vector<int64_t> opCode;

	// read program
	{
		std::ifstream infile(fn.c_str());
		int64_t id;
		while (infile >> id)
			opCode.push_back(id);
	}

	int sola = 1;
	std::pair<int, int> curPos = {0, 0};
	int curDir = 1;
	std::map<std::pair<int, int>, int> hull;
	auto hullIt = hull.begin();
	hullIt = hull.insert(hullIt, std::make_pair(curPos, 0));
	IntCodeMachine<int64_t> robot(opCode);
	std::vector<int64_t> input(1, 0);
	std::vector<int64_t> output;
	robot.execute(input, output);
	while (robot.state() == IntCodeMachine<int64_t>::ICMS_WAITING_FOR_INPUT)
	{
		if (output.size() != 2)
		{
			std::cout << "output size is " << output.size() << " instead of 2." << std::endl;
			throw std::runtime_error("");
		}

		// paint the hull
		hullIt->second = output[0];


		// move
		if (output[1] == 0)
		{
			// turn left
			curDir = (curDir + 1) % 4;
		}
		else if (output[1] == 1)
		{
			// turn right
			if (!curDir)
				curDir = 3;
			else
				--curDir;
		}
		switch (curDir)
		{
			case 0:
				++curPos.first; break;
			case 1:
				++curPos.second; break;
			case 2:
				--curPos.first; break;
			case 3:
				--curPos.second; break;
			default: break;
		}

		// update hull iterator
		hullIt = hull.lower_bound(curPos);
		if (hullIt == hull.end() || hullIt->first != curPos)
		{
			++sola;
			hullIt = hull.insert(hullIt, std::make_pair(curPos, 0));
		}

		// prepare next robot instruction
		input[0] = hullIt->second;
		output.clear();
		robot.execute(input, output);
	}
	std::cout << "a: " << sola << std::endl;

	// part b
	curPos = {0, 0};
	curDir = 1;
	hull.clear();
	hullIt = hull.begin();
	hullIt = hull.insert(hullIt, std::make_pair(curPos, 1));
	robot.reset(opCode);
	robot.setMemorySize(10000);
	do
	{
		// execute robot
		input[0] = hullIt->second;
		output.clear();
		robot.execute(input, output);
		if (output.size() != 2)
		{
			std::cout << "output size is " << output.size() << " instead of 2." << std::endl;
			throw std::runtime_error("");
		}

		// update the hull
		hullIt->second = output[0];

		// move
		if (output[1] == 0)
		{
			// turn left
			curDir = (curDir + 1) % 4;
		}
		else if (output[1] == 1)
		{
			// turn right
			if (!curDir)
				curDir = 3;
			else
				--curDir;
		}
		switch (curDir)
		{
			case 0:
				++curPos.first; break;
			case 1:
				++curPos.second; break;
			case 2:
				--curPos.first; break;
			case 3:
				--curPos.second; break;
			default: break;
		}

		// update hull iterator
		hullIt = hull.lower_bound(curPos);
		if (hullIt == hull.end() || hullIt->first != curPos)
			hullIt = hull.insert(hullIt, std::make_pair(curPos, 0));
	}
	while (robot.state() == IntCodeMachine<int64_t>::ICMS_WAITING_FOR_INPUT);

	// now find max extensions and copy to arrays
	int minX = std::numeric_limits<int>::max();
	int maxX = std::numeric_limits<int>::min();
	int minY = std::numeric_limits<int>::max();
	int maxY = std::numeric_limits<int>::min();
	auto hullItEnd = hull.end();
	for (hullIt = hull.begin(); hullIt != hullItEnd; ++hullIt)
	{
		minX = std::min(minX, hullIt->first.first);
		minY = std::min(minY, hullIt->first.second);
		maxX = std::max(maxX, hullIt->first.first);
		maxY = std::max(maxY, hullIt->first.second);
	}
	const std::size_t nRows = maxY - minY + 1;
	const std::size_t nCols = maxX - minX + 1;

	std::vector<std::vector<char> > paintedHull(nRows, std::vector<char>(nCols, ' '));
	for (hullIt = hull.begin(); hullIt != hullItEnd; ++hullIt)
		if (hullIt->second)
			paintedHull[maxY - hullIt->first.second][hullIt->first.first - minX] = '#';

	std::cout << "b:" << std::endl;
	for (std::size_t r = 0; r < nRows; ++r)
	{
		for (std::size_t c = 0; c < nCols; ++c)
			std::cout << paintedHull[r][c];
		std::cout << std::endl;
	}
}


