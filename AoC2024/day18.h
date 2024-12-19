/*
 * day18.h
 *
 *  Created on: 2024-12-18
 *      Author: mbreit
 */

template <>
void executeDay<18>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::vector<unsigned> pos;

	std::string line;
	while (std::getline(infile, line))
	{
		std::regex re("(\\d*),(\\d*)");
		std::smatch match;
		if (!std::regex_match(line, match, re))
			break;
		unsigned p = 71u * std::stoul(match.str(2)) + std::stoul(match.str(1));
		pos.push_back(p);
	}

	auto findWay = [&](size_t numBytes)
	{
		constexpr auto mx = std::numeric_limits<unsigned>::max();
		std::array<unsigned, 71u*71u> mem;
		std::fill(mem.begin(), mem.end(), mx);
		
		for (size_t k = 0u; k < numBytes; ++k)
			mem[pos[k]] = 0u;

		std::queue<std::array<unsigned, 2>> q;
		q.push({0u, 0u});
		while (!q.empty())
		{
			auto& [p, n] = q.front();
			q.pop();
			
			if (mem[p] <= n)
				continue;
				
			mem[p] = n;
			
			if (p == 71u * 71u - 1u)
				continue;
			
			if (p > 70u && mem[p - 71u] > n + 1u)
				q.push({p - 71u, n + 1u});
			if (p < 70u * 71u && mem[p + 71u] > n + 1u)
				q.push({p + 71u, n + 1u});
			if (p % 71u > 0u && mem[p - 1u] > n + 1u)
				q.push({p - 1u, n + 1u});
			if (p % 71u < 70u && mem[p + 1u] > n + 1u)
				q.push({p + 1u, n + 1u});
		}

		return mem.back();
	};
	
	
	// part a
	unsigned resA = findWay(1024u);
	
	// part b
	const unsigned sz = pos.size();
	const auto it = std::ranges::lower_bound(std::ranges::iota_view(1025u, sz), true,
		[](unsigned u, bool b){return b && (u != std::numeric_limits<unsigned>::max() && u != 0u);},
		[&](unsigned v){return findWay(v);});
	auto resB = std::to_string(pos[*it - 1u] % 71u) + "," + std::to_string(pos[*it - 1u] / 71u);


	writeSolution(resA, resB);
}


