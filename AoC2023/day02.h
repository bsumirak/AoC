/*
 * day02.h
 *
 *  Created on: 2023-12-02
 *      Author: mbreit
 */

template <>
void executeDay<2>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	unsigned resA = 0;
	unsigned resB = 0;
	
	std::vector<std::vector<std::array<unsigned, 3>>> games;
	games.reserve(100);
	
	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		std::string s;
		unsigned u;
		
		games.emplace_back();
		auto& game = games.back();
		
		iss >> s;
		iss >> u;
		iss >> s;
		
		game.emplace_back();
		std::fill(game.back().begin(), game.back().end(), 0);
		while (iss >> u)
		{
			auto& tuple = game.back();
			
			iss >> s;
			if (s[0] == 'r')
				tuple[0] = u;
			else if (s[0] == 'g')
				tuple[1] = u;
			else if (s[0] == 'b')
				tuple[2] = u;
			
			if (s.back() == ';')
			{
				game.emplace_back();
				std::fill(game.back().begin(), game.back().end(), 0);
			}
		}
	}
	
	// part a
	unsigned id = 0;
	for (const auto& game : games)
	{
		++id;
		bool possible = true;
		for (const auto& draw : game)
		{
			if (draw[0] > 12u || draw[1] > 13u || draw[2] > 14u)
			{
				possible = false;
				break;
			}	
		}
		
		if (possible)
			resA += id;
	}
	
	// part b
	for (const auto& game : games)
	{
		std::array<unsigned, 3> min;
		std::fill(min.begin(), min.end(), 0);
		for (const auto& draw : game)
		{
			min[0] = std::max(min[0], draw[0]);
			min[1] = std::max(min[1], draw[1]);
			min[2] = std::max(min[2], draw[2]);
		}
		
		resB += min[0] * min[1] * min[2];
	}
	
	
	writeSolution(resA, resB);
}


