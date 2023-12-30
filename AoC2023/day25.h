/*
 * day25.h
 *
 *  Created on: 2023-12-25
 *      Author: mbreit
 */

	
struct Node25
{
	Node25(const std::string& _name) : name(_name){}

	std::string name;
	unsigned alreadyChecked = 0;
	std::vector<std::shared_ptr<Node25>> c;
	std::vector<unsigned> invalid;
};


bool findPath25(std::shared_ptr<Node25> from, std::shared_ptr<Node25> to,
	std::vector<std::shared_ptr<Node25>>& path, unsigned flowId, unsigned pathId)
{
	if (from == to)
	{
		path.push_back(from);
		return true;
	}
	
	from->alreadyChecked = pathId;
	
	const size_t nCh = from->c.size();
	for (size_t k = 0; k < nCh; ++k)
	{
		if (from->invalid[k] == flowId || from->c[k]->alreadyChecked == pathId)
			continue;
		
		if (findPath25(from->c[k], to, path, flowId, pathId))
		{
			path.push_back(from);
			return true;
		}
	}
	
	return false;
}



template <>
void executeDay<25>(const std::string& fn)
{
	// parse input
	std::ifstream infile(fn.c_str());
	
	std::map<std::string, std::shared_ptr<Node25>> nodes;
	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
	
		std::string s;
		iss >> s;
		s.erase(s.end() - 1);
		
		auto& nd = nodes[s];
		if (!nd)
			nd = std::make_shared<Node25>(s);
		
		while (iss >> s)
		{
			auto& ch = nodes[s];
			if (!ch)
				ch = std::make_shared<Node25>(s);
			nd->c.push_back(ch);
			ch->c.push_back(nd);
			nd->invalid.push_back(0);
			ch->invalid.push_back(0);
		}
	}


	// part a
	unsigned flowIt = 0u;
	unsigned pathIt = 0u;

	auto t = nodes.rbegin()->second;
	
	const auto getMaxFlow = [&](std::shared_ptr<Node25> s)
	{
		unsigned maxFlow = 0;
		std::vector<std::shared_ptr<Node25>> path;
		while (true)
		{
			++pathIt;
			
			// find augmenting path			
			if (findPath25(s, t, path, flowIt, pathIt))
			{
				++maxFlow;
				
				// invalidate augmenting path
				const size_t sz = path.size();
				for (size_t k = sz - 1; k > 0; --k)
				{
					auto curr = path[k];
					auto next = path[k - 1];
					
					auto itN = std::find(next->c.begin(), next->c.end(), curr);
					auto idxN = std::distance(next->c.begin(), itN);
					if (next->invalid[idxN] == flowIt) // backward-forward flow elimination
						next->invalid[idxN] = flowIt - 1;
					else
					{
						auto itC = std::find(curr->c.begin(), curr->c.end(), next);
						auto idxC = std::distance(curr->c.begin(), itC);
						curr->invalid[idxC] = flowIt;					
					}
					
				}
				path.clear();
			}
			else
				return maxFlow;
		}
	};
	
	unsigned nCis = 1;
	unsigned nTrans = 0;
	for (auto it : nodes)
	{
		auto s = it.second;
		
		if (s == t)
			continue;
		
		++flowIt;
		
		const unsigned maxFlow = getMaxFlow(s);
		if (maxFlow == 3)
			++nTrans;
		else
			++nCis;
	}
	
	unsigned resA = nCis * nTrans;
		
	
	writeSolution(resA, 0);
}


