/*
 * day03.h
 *
 *  Created on: 2024-12-03
 *      Author: mbreit
 */

template <>
void executeDay<3>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	unsigned resA = 0;
	unsigned resB = 0;

	bool enable = true;

	std::string line;
	while (std::getline(infile, line))
	{
		// part a
		{
			std::regex re("mul\\((\\d{1,3}),(\\d{1,3})\\)");
			auto matchBegin = std::sregex_iterator(line.begin(), line.end(), re);
			auto matchEnd = std::sregex_iterator();
			for (auto it = matchBegin; it != matchEnd; ++it)
			{
				std::smatch match = *it;
				resA += std::stoul(match.str(1)) * std::stoul(match.str(2));
			}
		}

		// part b
		{
			std::regex re("(mul)\\((\\d{1,3}),(\\d{1,3})\\)|(do)\\(\\)|(don)\'t\\(\\)");
			auto matchBegin = std::sregex_iterator(line.begin(), line.end(), re);
			auto matchEnd = std::sregex_iterator();
			for (auto it = matchBegin; it != matchEnd; ++it)
			{
				std::smatch match = *it;
				if (match.str(1) == "mul" && enable)
					resB += std::stoul(match.str(2)) * std::stoul(match.str(3));
				else if (match.str(4) == "do")
					enable = true;
				else if (match.str(5) == "don")
					enable = false;
			}
		}
	}

	writeSolution(resA, resB);
}


