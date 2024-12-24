/*
 * day24.h
 *
 *  Created on: 2024-12-24
 *      Author: mbreit
 */


template <>
void executeDay<24>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::map<std::string, bool> wire;
	std::map<std::array<std::string, 3>, char> gate;

	std::string line;
	while (std::getline(infile, line))
	{
		std::regex re("(...): (\\d)");
		std::smatch match;
		if (!std::regex_match(line, match, re))
			break;
		wire[match.str(1)] = match.str(2) == "1";
	}
	while (std::getline(infile, line))
	{
		std::regex re("(...) (.).{1,2} (...) -> (...)");
		std::smatch match;
		if (std::regex_match(line, match, re))
			gate[{match.str(4), match.str(1), match.str(3)}] = match.str(2)[0];
	}

	// part a
	uint64_t resA = 0u;
	bool cont = true;
	while (cont)
	{
		cont = false;
		for (auto& g : gate)
		{
			if (wire.find(g.first[2]) == wire.end()
				|| wire.find(g.first[1]) == wire.end())
			{
				cont = true;
				continue;
			}

			switch (g.second)
			{
				case 'A':
					wire[g.first[0]] = wire[g.first[2]] && wire[g.first[1]]; break;
				case 'O':
					wire[g.first[0]] = wire[g.first[2]] || wire[g.first[1]]; break;
				case 'X':
					wire[g.first[0]] = wire[g.first[2]] != wire[g.first[1]]; break;
				default:
					std::cout << "whut" << std::endl;
			}
		}
	}

	for (auto& g : gate)
	{
		if (g.first[0][0] == 'z')
			resA += (uint64_t)(wire[g.first[0]]) << std::stoull(g.first[0].substr(1));
	}

	// part b (solved by hand)
	std::string resB = "gwh,jct,rcb,wbw,wgb,z09,z21,z39";


	writeSolution(resA, resB);
}

