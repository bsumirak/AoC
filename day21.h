/*
 * day21.h
 *
 *  Created on: 21.12.2017
 *      Author: mbreit
 */

#include <algorithm>


template <>
void executeDay<21>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::map<std::string, std::string> convRules;

	std::string line;
	while (std::getline(infile, line))
	{
		line.erase(std::remove(line.begin(), line.end(), '/'), line.end());

		std::istringstream iss(line);

		std::string in, dummy, out;
		iss >> in;
		iss >> dummy;
		iss >> out;

		size_t l = in.size() == 4 ? 2 : 3;

		// turn around
		std::string turnedIn = in;
		std::string flippedIn = in;
		for (size_t i = 0; i < 4; ++i)
		{
			if (l == 2)
			{
				turnedIn[0] = in[2];
				turnedIn[1] = in[0];
				turnedIn[2] = in[3];
				turnedIn[3] = in[1];

				flippedIn[0] = in[1];
				flippedIn[0] = in[1];
				flippedIn[2] = in[3];
				flippedIn[3] = in[2];

				convRules[turnedIn] = out;
				convRules[flippedIn] = out;
				in = turnedIn;
			}
			else
			{
				turnedIn[0] = in[6];
				turnedIn[1] = in[3];
				turnedIn[2] = in[0];
				turnedIn[3] = in[7];
				turnedIn[5] = in[1];
				turnedIn[6] = in[8];
				turnedIn[7] = in[5];
				turnedIn[8] = in[2];

				flippedIn[0] = in[2];
				flippedIn[1] = in[1];
				flippedIn[2] = in[0];
				flippedIn[3] = in[5];
				flippedIn[5] = in[3];
				flippedIn[6] = in[8];
				flippedIn[7] = in[7];
				flippedIn[8] = in[6];

				convRules[turnedIn] = out;
				convRules[flippedIn] = out;
				in = turnedIn;
			}
		}
	}

	std::string pic = ".#...####";
	for (size_t i = 0; i < 5; ++i)
	{
		std::string newPic;
		size_t blockSz = pic.size() % 4 == 0 ? 2 : 3;
		size_t sideL = (size_t) sqrt(pic.size());
		size_t newSideL = sideL / blockSz * (blockSz+1);
		newPic.resize(pic.size() / (blockSz*blockSz) * (blockSz+1)*(blockSz+1));
		std::string block;
		block.resize(blockSz*blockSz);
		for (size_t i = 0; i < sideL / blockSz; ++i)
		{
			for (size_t j = 0; j < sideL / blockSz; ++j)
			{
				// get block
				for (size_t k = 0; k < blockSz; ++k)
					for (size_t l = 0; l < blockSz; ++l)
						block[k*blockSz+l] = pic[(blockSz*i+k)*sideL + (blockSz*j+l)];

				// transform
				//std::cout << block << std::endl;
				std::map<std::string, std::string>::const_iterator it = convRules.find(block);
				if (it == convRules.end())
					std::cout << block << "  " << block.size() << "  " << blockSz << std::endl;

				std::string convBlock = it->second;

				// insert into new pic
				for (size_t k = 0; k < blockSz+1; ++k)
					for (size_t l = 0; l < blockSz+1; ++l)
						newPic[((blockSz+1)*i+k)*newSideL + ((blockSz+1)*j+l)] = convBlock[k*(blockSz+1)+l];
			}
		}

		pic = newPic;
std::cout << pic << std::endl;
	}
/*
	std::map<std::string, std::string>::const_iterator it = convRules.begin();
	std::map<std::string, std::string>::const_iterator itEnd = convRules.end();
	for (; it != itEnd; ++it)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}
*/
	// count #
	size_t cnt = 0;
	size_t sz = pic.size();
	for (size_t i = 0; i < sz; ++i)
	{
		if (pic[i] == '#')
			++cnt;
	}

	writeSolution(cnt, (int) 0);
}

