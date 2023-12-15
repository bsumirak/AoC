/*
 * day15.h
 *
 *  Created on: 2023-12-15
 *      Author: mbreit
 */


template <>
void executeDay<15>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	
	std::string manual;
	infile >> manual;
	

	// part a
	unsigned resA = 0;

	unsigned char hash = 0;
	for (char c : manual)
	{
		if (c == ',')
		{
			resA += hash;
			hash = 0;
		}
		else
			hash = ((hash + (unsigned char)c) * (unsigned char)17);
	}
	resA += hash;
			
	
	// part b	
	std::array<std::vector<std::pair<std::string, unsigned>>, 256> setup;
	
	std::string label;
	hash = 0;
	unsigned fl = 0;
	
	std::string instr;
	std::istringstream iss(manual);
	while (std::getline(iss, instr, ','))	
	{
		if (instr.back() == '-')
			label = instr.substr(0, instr.size() - 1);
		else
		{
			label = instr.substr(0, instr.size() - 2);
			fl = instr.back() - '0';
		}

		hash = 0;		
		for (char c : label)
			hash = ((hash + (unsigned char)c) * (unsigned char)17);
		
		auto& box = setup[hash];
		if (instr.back() == '-')
		{
			auto it = std::find_if(box.begin(), box.end(), [&](std::pair<std::string, unsigned>& p){return p.first == label;});
			if (it != box.end())
				box.erase(it);
		}
		else
		{
			auto it = std::find_if(box.begin(), box.end(), [&](std::pair<std::string, unsigned>& p){return p.first == label;});
			if (it != box.end())
				it->second = fl;
			else
				box.push_back(std::make_pair(label, fl));
		}
	}

	size_t resB = 0;
	for (unsigned k = 0; k < 255; ++k)
		for (unsigned l = 0; l < setup[k].size(); ++l)
			resB += (k+1) * (l+1) * setup[k][l].second;
	
	
	writeSolution(resA, resB);
}


