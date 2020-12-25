/*
 * main.cpp
 *
 *  Created on: 2018-11-30
 *      Author: mbreit
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <iomanip>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <array>
#include <regex>
#include <bitset>


// function template for every day
// to be specialized by every day
template <int i>
void executeDay(const std::string& fn) {}

// forward declaration
template <typename A, typename B>
void writeSolution(A a, B b);


#include "day01.h"
#include "day02.h"
#include "day03.h"
#include "day04.h"
#include "day05.h"
#include "day06.h"
#include "day07.h"
#include "day08.h"
#include "day09.h"
#include "day10.h"
#include "day11.h"
#include "day12.h"
#include "day13.h"
#include "day14.h"
#include "day15.h"
#include "day16.h"
#include "day17.h"
#include "day18.h"
#include "day19.h"
#include "day20.h"
#include "day21.h"
#include "day22.h"
#include "day23.h"
#include "day24.h"
#include "day25.h"

template <typename A, typename B>
void writeSolution(A a, B b)
{
	// solution output
	std::cout << "a: " << a
		<< "      b: " << b << std::endl;
}


int main(int argc, char** argv)
{
	// which day
	int day = 1;
	if (argc >= 2)
		day = atoi(argv[1]);

	// non-standard input file postfix (useful for debugging)
	std::string fileNameAdd = "";
	if (argc >= 3)
		fileNameAdd = argv[2];

	// construct input file name
	std::ostringstream oss;
	oss << "input/input";
	if (day < 10)
		oss << "0";
	oss << day;
	oss << fileNameAdd;
	oss << ".dat";
	std::string inputFileName = oss.str();

	switch (day)
	{
		case 1:
			executeDay<1>(inputFileName);
			break;
		case 2:
			executeDay<2>(inputFileName);
			break;
		case 3:
			executeDay<3>(inputFileName);
			break;
		case 4:
			executeDay<4>(inputFileName);
			break;
		case 5:
			executeDay<5>(inputFileName);
			break;
		case 6:
			executeDay<6>(inputFileName);
			break;
		case 7:
			executeDay<7>(inputFileName);
			break;
		case 8:
			executeDay<8>(inputFileName);
			break;
		case 9:
			executeDay<9>(inputFileName);
			break;
		case 10:
			executeDay<10>(inputFileName);
			break;
		case 11:
			executeDay<11>(inputFileName);
			break;
		case 12:
			executeDay<12>(inputFileName);
			break;
		case 13:
			executeDay<13>(inputFileName);
			break;
		case 14:
			executeDay<14>(inputFileName);
			break;
		case 15:
			executeDay<15>(inputFileName);
			break;
		case 16:
			executeDay<16>(inputFileName);
			break;
		case 17:
			executeDay<17>(inputFileName);
			break;
		case 18:
			executeDay<18>(inputFileName);
			break;
		case 19:
			executeDay<19>(inputFileName);
			break;
		case 20:
			executeDay<20>(inputFileName);
			break;
		case 21:
			executeDay<21>(inputFileName);
			break;
		case 22:
			executeDay<22>(inputFileName);
			break;
		case 23:
			executeDay<23>(inputFileName);
			break;
		case 24:
			executeDay<24>(inputFileName);
			break;
		case 25:
			executeDay<25>(inputFileName);
			break;
		default:
			break;
	}

	return 0;
}













