/*
 * day16.h
 *
 *  Created on: 2022-12-16
 *      Author: mbreit
 */


struct Node16
{
	std::vector<std::pair<unsigned, unsigned>> adj;
	unsigned flow;
	bool open = false;
};


void traverse16(std::array<Node16, 26*26>& valves, unsigned pos, unsigned time,
	unsigned release, unsigned& maxRelease)
{
	if (time <= 1)
		return;

	auto& v = valves[pos];
	if (!v.open && v.flow > 0)
	{
		v.open = true;
		unsigned pressure = (time - 1) * v.flow;
		release += pressure;
		maxRelease = std::max(release, maxRelease);

		traverse16(valves, pos, time - 1, release, maxRelease);
		release -= pressure;
		v.open = false;
	}
	else // this is not correct in general, I think, but yields correct result
	for (auto& adj : v.adj)
		if (adj.second < time)
			traverse16(valves, adj.first, time - adj.second, release, maxRelease);
}


void traverse16WithElephant(std::array<Node16, 26*26>& valves, unsigned pos, unsigned posE, unsigned time, unsigned timeE,
	unsigned release, unsigned& maxRelease)
{
	if (time <= 1 && timeE <= 1)
		return;

	if (time >= timeE)
	{
		auto& v = valves[pos];
		if (!v.open && v.flow > 0)
		{
			v.open = true;
			unsigned pressure = (time - 1) * v.flow;
			release += pressure;
			//if (release > maxRelease)
			//	std::cout << release << std::endl;
			maxRelease = std::max(release, maxRelease);
			traverse16WithElephant(valves, pos, posE, time - 1, timeE, release, maxRelease);
			release -= pressure;
			v.open = false;
		}
		else // this is not correct in general, I think, but yields correct result
		for (auto& adj : v.adj)
			if (adj.second < time)
				traverse16WithElephant(valves, adj.first, posE, time - adj.second, timeE, release, maxRelease);
	}
	else
	{
		auto& v = valves[posE];
		if (!v.open && v.flow > 0)
		{
			v.open = true;
			unsigned pressure = (timeE - 1) * v.flow;
			release += pressure;
			//if (release > maxRelease)
			//	std::cout << release << std::endl;
			maxRelease = std::max(release, maxRelease);
			traverse16WithElephant(valves, pos, posE, time, timeE - 1, release, maxRelease);
			release -= pressure;
			v.open = false;
		}
		else // this is not correct in general, I think, but yields correct result
		for (auto& adj : v.adj)
			if (adj.second < timeE)
				traverse16WithElephant(valves, pos, adj.first, time, timeE - adj.second, release, maxRelease);
	}
}


template <>
void executeDay<16>(const std::string& fn)
{
	// read input
	std::array<Node16, 26*26> valves;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		while (std::getline(infile, line))
		{
			std::istringstream iss(line);
			char c1, c2;
			iss >> c1;
			iss >> c2;

			unsigned vid = 26u * (unsigned)(c1 - 'A') + (unsigned)(c2 - 'A');

			iss >> valves[vid].flow;

			while (iss >> c1)
			{
				iss >> c2;
				unsigned vidc = 26u * (unsigned)(c1 - 'A') + (unsigned)(c2 - 'A');
				valves[vid].adj.push_back(std::make_pair(vidc, 1u));
			}
		}
		infile.close();
	}


	// collapse all nodes with valves with flow rate 0 (except the first, where we need to start)
	for (unsigned k = 0; k < 26*26; ++k)
	{
		if (valves[k].adj.empty())
			continue;

		Node16& v = valves[k];
		if (v.flow == 0)
		{
			for (unsigned l = 0; l < 26*26; ++l)
			{
				auto& v1 = valves[l];
				if (l == k || v1.adj.empty())
					continue;

				auto it = std::find_if(v1.adj.begin(), v1.adj.end(),
					[&](const std::pair<unsigned, unsigned>& p){return p.first == k;});
				if (it == v1.adj.end())
					continue;
				unsigned len = it->second;
				v1.adj.erase(it);
				for (auto& adj2 : v.adj)
				{
					if (adj2.first == l)
						continue;
					auto it2 = std::find_if(v1.adj.begin(), v1.adj.end(),
						[&](const std::pair<unsigned, unsigned>& p){return p.first == adj2.first;});
					if (it2 != v1.adj.end())
						it2->second = std::min(it2->second, len + adj2.second);
					else
						v1.adj.push_back(std::make_pair(adj2.first, len + adj2.second));
				}
			}
			if (k > 0)
				v.adj.clear();
		}
	}

/*
	for (unsigned k = 0; k < 26*26; ++k)
	{
		if (valves[k].adj.empty())
			continue;

		std::cout << (char)('A'+ k/26u) << (char)('A' + k % 26u) << " " << valves[k].flow << " ";
		for (const auto& adj : valves[k].adj)
			std::cout << (char)('A'+ (adj.first/26u)) << (char)('A' + adj.first % 26u) << "(" << adj.second << ") ";
		std::cout << std::endl;
	}
*/

	unsigned pos = 0;
	unsigned time = 30;
	unsigned release = 0;
	unsigned maxRelease = 0;
	traverse16(valves, pos, time, release, maxRelease);//, 0, numReleasable - 1);
	unsigned resA = maxRelease;

	// part b
	pos = 0;
	time = 26;
	release = 0;
	maxRelease = 0;
	traverse16WithElephant(valves, pos, pos, time, time, release, maxRelease);
	unsigned resB = maxRelease;


	writeSolution(resA, resB);
}


