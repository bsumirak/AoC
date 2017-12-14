/*
 * day10.h
 *
 *  Created on: 10.12.2017
 *      Author: mbreit
 */


std::string calculate_knot_hash(const std::string& line)
{
	size_t sz = line.size();

	// convert to integer lengths
	std::vector<int> vLength(sz);
	for (size_t i = 0; i < sz; ++i)
		vLength[i] = line[i];

	vLength.reserve(sz+5);
	vLength.push_back(17);
	vLength.push_back(31);
	vLength.push_back(73);
	vLength.push_back(47);
	vLength.push_back(23);
	sz += 5;

	// initiate list
	int list[256];
	for (size_t i = 0; i < 256; ++i)
		list[i] = i;

	// apply 64 iterations of knotting
	int curPos = 0;
	int skip = 0;
	for (int k = 0; k < 64; ++k)
	{
		for (size_t i = 0; i < sz; ++i)
		{
			// reverse order
			int n = vLength[i];
			for (size_t j = 0; j < n/2; ++j)
				std::swap(list[(curPos+j)%256], list[(curPos+n-1-j)%256]);

			// move forward
			curPos += (n + skip) % 256;
			++skip;
		}
	}

	// calculate dense hash
	int denseHash[16];
	for (size_t i = 0; i < 16; ++i)
	{
		int xorRes = 0;
		for (int j = 0; j < 16; ++j)
			xorRes ^= list[16*i + j];
		denseHash[i] = xorRes;
	}

	// reformat dense hash to hexadecimal representation
	std::ostringstream oss;
	for (size_t i = 0; i < 16; ++i)
		oss << std::setfill('0') << std::setw(2) << std::hex << denseHash[i];

	return oss.str();
}



template <>
void executeDay<10>(const std::string& fn)
{
	// part a
	int sola;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		std::getline(infile, line);
		std::istringstream iss(line);

		// read file
		std::vector<int> vLength;
		std::string token;
		while (std::getline(iss, token, ','))
		{
			std::istringstream tokenStream(token);
			int i;
			tokenStream >> i;
			vLength.push_back(i);
		}

		int list[256];
		for (size_t i = 0; i < 256; ++i)
			list[i] = i;

		int curPos = 0;
		int skip = 0;
		size_t sz = vLength.size();
		for (size_t i = 0; i < sz; ++i)
		{
			// reverse order
			int n = vLength[i];
			for (size_t j = 0; j < n/2; ++j)
				std::swap(list[(curPos+j)%256], list[(curPos+n-1-j)%256]);

			// move forward
			curPos += (n + skip) % 256;
			++skip;
		}

		sola = list[0] * list[1];
	}

	// part b
	std::string solb;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		std::getline(infile, line);

		solb = calculate_knot_hash(line);
	}

	writeSolution(sola, solb);
}


