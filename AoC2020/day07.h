/*
 * day01.h
 *
 *  Created on: 2020-12-07
 *      Author: mbreit
 */


template <>
void executeDay<7>(const std::string& fn)
{
	// read input
	std::map<std::string, int> bagTypes;
	std::vector<std::vector<int> > containedIn;
	std::vector<std::vector<std::pair<int, int> > > contains;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		while (std::getline(infile, line))
		{
			std::istringstream iss(line);
			std::string a, b;
			iss >> a;
			iss >> b;
			a.append(" ");
			a.append(b);
			auto containerIdIt = bagTypes.find(a);
			if (containerIdIt == bagTypes.end())
			{
				bagTypes[a] = bagTypes.size();
				contains.resize(bagTypes.size());
				containedIn.resize(bagTypes.size());
			}
			int containerId = bagTypes[a];

			iss >> b;
			iss >> b;

			int c;
			while (iss >> c)
			{
				iss >> a;
				iss >> b;
				a.append(" ").append(b);
				auto bagIdIt = bagTypes.find(a);
				if (bagIdIt == bagTypes.end())
				{
					bagTypes[a] = bagTypes.size();
					contains.resize(bagTypes.size());
					containedIn.resize(bagTypes.size());
				}
				int bagId = bagTypes[a];

				iss >> b;

				contains[containerId].push_back(std::make_pair(bagId, c));
				containedIn[bagId].push_back(containerId);
			}
		}
		infile.close();
	}

	// part a
	std::size_t resA = 0;
	int s = bagTypes["shiny gold"];
	{
		std::vector<bool> hadIt(bagTypes.size(), false);

		std::queue<int> q;
		for (auto j : containedIn[s])
			q.push(j);
		while (!q.empty())
		{
			int i = q.front();
			q.pop();

			if (hadIt[i])
				continue;
			hadIt[i] = true;

			++resA;

			for (auto j : containedIn[i])
				q.push(j);
		}
	}

	// part b
	std::size_t resB = 0;
	{
		std::queue<std::pair<int, int> > q;
		q.push(std::make_pair(s, 1));
		while (!q.empty())
		{
			auto ctnr = q.front();
			q.pop();

			resB += ctnr.second;

			for (auto ctnd : contains[ctnr.first])
				q.push(std::make_pair(ctnd.first, ctnd.second * ctnr.second));
		}
	}
	--resB;

	writeSolution(resA, resB);
}


