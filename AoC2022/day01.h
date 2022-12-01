/*
 * day01.h
 *
 *  Created on: 2022-12-01
 *      Author: mbreit
 */


template <>
void executeDay<1>(const std::string& fn)
{
	// read input
	int resA = 0;
	int resB = 0;

	unsigned cal;
	unsigned calTot = 0;
	std::array<unsigned,3> maxCalTot{0, 0, 0};

	const auto checkForPodium = [&](){
		if (calTot > maxCalTot[0])
		{
			maxCalTot[2] = maxCalTot[1];
			maxCalTot[1] = maxCalTot[0];
			maxCalTot[0] = calTot;
		}
		else if (calTot > maxCalTot[1])
		{
			maxCalTot[2] = maxCalTot[1];
			maxCalTot[1] = calTot;
		}
		else if (calTot > maxCalTot[2])
		{
			maxCalTot[2] = calTot;
		}
	};

	std::ifstream infile(fn.c_str());
	std::string line;
	while (std::getline(infile, line))
	{
		// parse input line
		std::istringstream iss(line);
		if (line.empty())
		{
			checkForPodium();
			calTot = 0;
			continue;
		}

		iss >> cal;
		calTot += cal;
	}
	checkForPodium();

	resA = maxCalTot[0];
	resB = maxCalTot[0] + maxCalTot[1] + maxCalTot[2];

	writeSolution(resA, resB);
}


