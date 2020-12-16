/*
 * day16.h
 *
 *  Created on: 2020-12-16
 *      Author: mbreit
 */


template <>
void executeDay<16>(const std::string& fn)
{
	// read input
	static const std::regex re0("^[a-z\\s]*:\\s([[:d:]]*)-([[:d:]]*)\\sor\\s([[:d:]]*)-([[:d:]]*)$");

	std::vector<std::array<unsigned, 4> > rules;
	std::array<unsigned, 20> myTicket;
	std::vector<std::array<unsigned, 20> > otherTickets;
	int state = 0;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		while (std::getline(infile, line))
		{

			if (line.empty())
			{
				++state;
				std::getline(infile, line);
				continue;
			}

			switch (state)
			{
				case 0:
				{
					rules.resize(rules.size() + 1);
					auto& r = rules.back();
					std::smatch match;
					if (!std::regex_match(line, match, re0))
					{
						std::cout << "error reading state 0" << std::endl;
						return;
					}
					r[0] = stoi(match[1]);
					r[1] = stoi(match[2]);
					r[2] = stoi(match[3]);
					r[3] = stoi(match[4]);
					break;
				}
				case 1:
				{
					std::istringstream iss(line);

					for (size_t j = 0; j < 20; ++j)
						iss >> myTicket[j];
					break;
				}
				case 2:
				{
					otherTickets.resize(otherTickets.size() + 1);
					std::array<unsigned, 20>& ot = otherTickets.back();
					std::istringstream iss(line);
					for (size_t j = 0; j < 20; ++j)
						iss >> ot[j];
					break;
				}

			}
		}
		infile.close();
	}


	// part a
	std::size_t resA = 0;
	const std::size_t nTickets = otherTickets.size();
	std::vector<bool> validTicket(nTickets, true);
	for (size_t t = 0; t < nTickets; ++t)
	{
		for (unsigned n : otherTickets[t])
		{
			bool isValid = false;
			for (size_t r = 0; r < 20; ++r)
			{
				if ((n >= rules[r][0] && n <= rules[r][1])
					|| (n >= rules[r][2] && n <= rules[r][3]))
				{
					isValid = true;
					break;
				}
			}
			if (!isValid)
			{
				validTicket[t] = false;
				resA += n;
			}
		}
	}


	// part b
	std::vector<std::set<unsigned> > fieldCands(20, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19});
	std::vector<std::set<unsigned> > ruleCands(20, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19});
	for (size_t t = 0; t < nTickets; ++t)
	{
		if (!validTicket[t])
			continue;

		for (size_t f = 0; f < 20; ++f)
		{
			unsigned n = otherTickets[t][f];
			for (unsigned r = 0; r < 20; ++r)
			{
				if (!((n >= rules[r][0] && n <= rules[r][1])
					|| (n >= rules[r][2] && n <= rules[r][3])))
				{
					fieldCands[f].erase(r);
					ruleCands[r].erase(f);
				}
			}
		}
	}

	std::array<unsigned, 20> sol;
	while (true)
	{
		size_t f = 0;
		size_t r = 0;
		for (; f < 20; ++f, ++r)
		{
			if (fieldCands[f].size() == 1)
			{
				r = 20;
				break;
			}
			if (ruleCands[r].size() == 1)
			{
				f = 20;
				break;
			}
		}
		if (f < 20)
		{
			r = *fieldCands[f].begin();
			sol[r] = f;

			for (auto& fieldCand : fieldCands)
				fieldCand.erase(r);
			for (auto& ruleCand : ruleCands)
				ruleCand.erase(f);
			ruleCands[r].clear();

			continue;
		}
		if (r < 20)
		{
			f = *ruleCands[r].begin();
			sol[r] = f;

			for (auto& fieldCand : fieldCands)
				fieldCand.erase(r);
			for (auto& ruleCand : ruleCands)
				ruleCand.erase(f);
			fieldCands[f].clear();
			continue;
		}

		break;
	}

	int64_t resB(1);
	for (size_t i = 0; i < 6; ++i)
	{
		resB *= (int64_t) myTicket[sol[i]];
		std::cout << sol[i] << " ";
	}
	std::cout << std::endl;


	writeSolution(resA, resB);
}


