/*
 * day24.h
 *
 *  Created on: 24.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<24>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::vector<std::pair<int, int> > modules;

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int in, out;

		iss >> in;
		iss >> out;

		modules.push_back(std::make_pair(in, out));
	}

	// build all possible bridges and find that with max strength
	int maxStrength = 0;
	int longestStrength;
	int maxLength = -1;
	std::vector<bool> used(modules.size(), false);
	std::vector<size_t> tried(modules.size(), 0);
	std::vector<int> conn(modules.size()+1, 0);
	size_t pos = 0;
	while (true)
	{
		size_t next = tried[pos];
		while ((used[next] || (modules[next].first != conn[pos] && modules[next].second != conn[pos]))
				&& next < modules.size())
			++next;

		// no more module fits
		if (next == modules.size())
		{
			// all bridges built
			if (pos == 0)
				break;

			// compute strength
			int strength = 0;
			for (size_t i = 0; i < pos; ++i)
				strength += modules[tried[i]].first + modules[tried[i]].second;

			if (strength > maxStrength)
				maxStrength = strength;

			if ((int) pos >= maxLength)
			{
				if ((pos == maxLength && strength > longestStrength) || pos > maxLength)
					longestStrength = strength;
				maxLength = pos;
			}

//for (size_t i = 0; i < pos; ++i)
//	std::cout << modules[tried[i]].first << "/" << modules[tried[i]].second << " ";
//std::cout << std::endl;

			// remove last module
			tried[pos] = 0;
			--pos;
			used[tried[pos]] = false;
			++tried[pos];
		}

		// module fits
		else
		{
//std::cout << "fitting module " << modules[next].first << "/" << modules[next].second << std::endl;
			tried[pos] = next;
			used[next] = true;
			if (modules[next].first == conn[pos])
				conn[pos+1] = modules[next].second;
			else
				conn[pos+1] = modules[next].first;
			++pos;
		}
	}

	writeSolution(maxStrength, longestStrength);
}


