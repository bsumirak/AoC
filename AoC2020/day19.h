/*
 * day19.h
 *
 *  Created on: 2020-12-19
 *      Author: mbreit
 */


template <>
void executeDay<19>(const std::string& fn)
{
	// read input
	struct Data
	{
		Data() {}
		std::vector<unsigned> choice1;
		std::vector<unsigned> choice2;
		std::set<std::string> matches;
	};
	std::vector<Data> data(134);
	std::vector<std::string> lines;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		for (size_t i = 0; i < 134; ++i)
		{
			std::getline(infile, line);
			std::istringstream iss(line);

			int a;
			iss >> a;
			Data& d = data[a];

			char c;
			iss >> c;

			std::string s;
			iss >> s;
			if (s[0] == '"')
			{
				d.matches.insert(std::string(1, s[1]));
				continue;
			}

			d.choice1.push_back(stoul(s));

			while (iss >> s)
			{
				if (s[0] == '|')
					break;

				d.choice1.push_back(stoul(s));
			}

			while (iss >> a)
				d.choice2.push_back(a);

		}

		std::getline(infile, line);
		while (std::getline(infile, line))
			lines.push_back(line);

		infile.close();
	}


	// part a
	bool unfinished = true;
	while (unfinished)
	{
		unfinished = false;
		for (size_t i = 0; i < 134; ++i)
		{
			Data& d = data[i];
			if (d.matches.empty())
			{
				bool canBeProcessed = true;
				for (size_t j = 0; j < d.choice1.size(); ++j)
				{
					if (data[d.choice1[j]].matches.empty())
					{
						canBeProcessed = false;
						break;
					}
				}
				for (size_t j = 0; j < d.choice2.size(); ++j)
				{
					if (data[d.choice2[j]].matches.empty())
					{
						canBeProcessed = false;
						break;
					}
				}
				if (!canBeProcessed)
				{
					unfinished = true;
					continue;
				}

				if (d.choice1.size() == 1)
					d.matches = data[d.choice1[0]].matches;
				else if (d.choice1.size() == 2)
				{
					for (const auto& s1 : data[d.choice1[0]].matches)
						for (const auto& s2 : data[d.choice1[1]].matches)
							d.matches.insert(s1+s2);
				}

				if (d.choice2.size() == 1)
					for (const auto& s : data[d.choice2[0]].matches)
						d.matches.insert(s);
				else if (d.choice2.size() == 2)
				{
					for (const auto& s1 : data[d.choice2[0]].matches)
						for (const auto& s2 : data[d.choice2[1]].matches)
							d.matches.insert(s1+s2);
				}
			}
		}
	}

	std::size_t resA = 0;
	for (const std::string& line : lines)
		if (data[0].matches.find(line) != data[0].matches.end())
			++resA;


	// part b
	std::size_t resB = 0;
	for (const std::string& line : lines)
	{
		if (line.size() % 8u != 0)
			continue;

		size_t num = line.size() / 8u;

		size_t m = 0;
		for (; m < num; ++m)
		{
			std::string s = line.substr(8*m, 8);
			if (data[42].matches.find(s) == data[42].matches.end())
				break;
		}
		if (m == num || m < num/2+1)
			continue;

		bool yes = true;
		for (size_t n = m; n < num; ++n)
		{
			std::string s = line.substr(8*n, 8);
			if (data[31].matches.find(s) == data[31].matches.end())
			{
				yes = false;
				break;
			}
		}
		if (yes)
			++resB;
	}

	writeSolution(resA, resB);
}


