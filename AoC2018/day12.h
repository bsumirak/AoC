/*
 * day12.h
 *
 *  Created on: 2018-12-12
 *      Author: mbreit
 */


void printPots(const std::vector<bool>& config, int spaces)
{
	const size_t sz = config.size();
	std::cout << std::string(spaces, ' ');
	for (int k = 0; k < sz; ++k)
	{
		if (config[k])
			std::cout << '#';
		else
			std::cout << '.';
	}
	std::cout << std::endl;
}


template <>
void executeDay<12>(const std::string& fn)
{
	// convert start config
	std::string start = "##..#..##.#....##.#..#.#.##.#.#.######..##.#.#.####.#..#...##...#....#....#.##.###..#..###...#...#..";
	const int initSz = start.size();
	std::vector<bool> config(initSz);
	for (int i = 0; i < initSz; ++i)
		config[i] = start[i] == '#';

	// read rules
	std::vector<bool> rules(32);
	std::ifstream infile(fn.c_str());
	std::string line;
	int i = -1;
	while (++i, std::getline(infile, line))
	{
		int rule = 0;
		if (line[0] == '#')
			rule += 16;
		if (line[1] == '#')
			rule += 8;
		if (line[2] == '#')
			rule += 4;
		if (line[3] == '#')
			rule += 2;
		if (line[4] == '#')
			rule += 1;

		rules[rule] = line[9] == '#';
	}

	// part a
	const size_t nGen = 20;
	for (size_t j = 0; j < nGen; ++j)
	{
		std::vector<bool> newConfig(config.size() + 4);
		const int sz = initSz + 4*(j+1);

		for (int k = 0; k < sz; ++k)
		{
			// which rule to use
			size_t r = 0;
			for (int l = -2; l <= 2; ++l)
				if (k+l-2 >= 0 && k+l-2 < sz-4 && config[k+l-2])
					r += std::pow(2,2-l);

			// apply rule
			newConfig[k] = rules[r];
		}
		config.swap(newConfig);
	}

	int sola = 0;
	const int sz = initSz + 4*nGen;
	for (size_t j = 0; j < sz; ++j)
		if (config[j])
			sola += j - 2*nGen;


	// part b
	size_t solb = 0;

	// reset
	config.resize(initSz);
	for (int i = 0; i < initSz; ++i)
		config[i] = start[i] == '#';

	std::vector<std::pair<std::vector<bool>, int> > list;
	for (size_t j = 1; j < 8000; ++j)
	{
		std::vector<bool> newConfig(config.size() + 4);
		const int sz = initSz + 4*j;

		for (int k = 0; k < sz; ++k)
		{
			// which rule to use
			size_t r = 0;
			for (int l = -2; l <= 2; ++l)
				if (k+l-2 >= 0 && k+l-2 < sz-4 && config[k+l-2])
					r += std::pow(2,2-l);

			// apply rule
			newConfig[k] = rules[r];
		}
		config.swap(newConfig);

		// check whether identical to another config (modulo offset)
		size_t first = sz;
		size_t last = -1;
		for (size_t k = 0; k < sz; ++k)
		{
			if (config[k])
			{
				first = std::min(first, k);
				last = k;
			}
		}
		std::vector<bool> configRed(last-first+1);
		for (size_t k = 0; k < last-first+1; ++k)
			configRed[k] = config[first+k];

		for (size_t k = 0; k < j-1; ++k)
		{
			const std::vector<bool>& cmp = list[k].first;
			if (last-first+1 == cmp.size())
			{
				bool same = true;
				for (size_t l = 0; l < last-first+1; ++l)
				{
					if (cmp[l] != configRed[l])
					{
						same = false;
						break;
					}
				}
				if (same)
				{
					size_t period = j - (k+1);
					size_t iter = size_t(50000000000 - (k+1)) / period;
					size_t rest = size_t(50000000000 - (k+1)) % period;

					size_t finalOffset = list[k + rest].second
						+ iter * ((first - 2*j) - list[k].second);

					const size_t finalSz = list[k+rest].first.size();
					for (size_t l = 0; l < finalSz; ++l)
						if (list[k+rest].first[l])
							solb += l + finalOffset;

					goto solution;
				}
			}
		}

		list.push_back(make_pair(configRed, first - 2*j));
	}

solution:


	writeSolution(sola, solb);
}


