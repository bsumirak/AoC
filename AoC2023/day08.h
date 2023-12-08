/*
 * day08.h
 *
 *  Created on: 2023-12-08
 *      Author: mbreit
 */

template <>
void executeDay<8>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::string dirs;
	infile >> dirs;
	
	std::string node;
	std::map<std::string, std::array<std::string, 2>> nodes;
	while (infile >> node)
	{
		auto& nodeData = nodes[node];
		infile >> nodeData[0];
		infile >> nodeData[1];
	}
	
	// part a
	size_t resA = 0;
	for (auto nodeIt = nodes.find("AAA"); nodeIt->first != "ZZZ";)
	{
		if (dirs[resA % dirs.size()] == 'L')
			nodeIt = nodes.find(nodeIt->second[0]);
		else
			nodeIt = nodes.find(nodeIt->second[1]);
		
		++resA;
	}
	
	// part b
	std::vector<std::string> ghosts;
	for (const auto& node : nodes)
	{
		if (node.first[2] == 'A')
			ghosts.push_back(node.first);
	}
	std::vector<std::string> firstZ(ghosts.size(), "");
	std::vector<unsigned> firstZCnt(ghosts.size(), 0);
	std::vector<unsigned> len(ghosts.size(), 0);
	std::vector<bool> cycleComplete(ghosts.size(), false);
	
	unsigned cnt = 0;
	bool allZ = false;
	while (!allZ)
	{
		bool allCyclesComplete = true;
		allZ = true;
		const bool goLeft = dirs[cnt % dirs.size()] == 'L';
		unsigned k = 0;
		for (auto& ghost : ghosts)
		{
			ghost = nodes.find(ghost)->second[goLeft ? 0 : 1];
			if (ghost[2] != 'Z')
				allZ = false;
			else if (!cycleComplete[k])
			{
				if (firstZ[k] == "")
				{
					firstZ[k] = ghost;
					firstZCnt[k] = cnt + 1;
				}
				else if (firstZ[k] != ghost)
					std::cout << "more than one Z in path!" << std::endl;
			}
			if (!cycleComplete[k] && ghost == firstZ[k] && (cnt + 1 > firstZCnt[k]))// && (cnt - firstZCnt[k]) % dirs.size() == 0)
			{
				cycleComplete[k] = true;
				len[k] = cnt + 1 - firstZCnt[k];
			}
			
			if (!cycleComplete[k])
				allCyclesComplete = false;
				
			++k;
		}
		
		if (allCyclesComplete)
			break;
		
		++cnt;
	}
	
	for (size_t k = 0; k < ghosts.size(); ++k)
		if (firstZCnt[k] % len[k] != 0 || len[k] % dirs.size() != 0)
			std::cout << "This is unexpected." << std::endl;
	
	uint64_t resB = dirs.size();		
	for (auto l : len)
		resB *= l / dirs.size();
	
	writeSolution(resA, resB);
}


