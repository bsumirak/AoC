/*
 * day11.h
 *
 *  Created on: 11.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<11>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::string line;
	std::getline(infile, line);
	std::istringstream iss(line);

	// read file
	std::vector<int> vLength(3,0);
	std::string token;

	int solb = 0;
	while (std::getline(iss, token, ','))
	{
		if (token == "n")
			++vLength[0];
		else if (token == "s")
			--vLength[0];
		else if (token == "ne")
			++vLength[1];
		else if (token == "sw")
			--vLength[1];
		else if (token == "se")
			++vLength[2];
		else if (token == "nw")
			--vLength[2];
		else
			std::cout << "Unknown direction." << std::endl;

		int x = vLength[1] + vLength[2];
		int y = 2*vLength[0] + vLength[1] - vLength[2];

		// x dir first
		int dist = abs(x);
		if (abs(y) > abs(x))
			dist += (abs(y) - abs(x)) / 2;

		solb = std::max(solb, dist);
	}

	// part a
	int x = vLength[1] + vLength[2];
	int y = 2*vLength[0] + vLength[1] - vLength[2];

	// x dir first
	int sola = abs(x);
	if (abs(y) > abs(x))
		sola += (abs(y) - abs(x)) / 2;

	writeSolution(sola, solb);
}


