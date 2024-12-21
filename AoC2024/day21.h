/*
 * day21.h
 *
 *  Created on: 2024-12-21
 *      Author: mbreit
 */


template <>
void executeDay<21>(const std::string& fn)
{
	uint64_t resA = 0u;
	uint64_t resB = 0u;
	
	std::map<std::array<char, 2>, std::string> replace;
	replace[{'<', '<'}] = "A";
	replace[{'<', 'v'}] = ">A";
	replace[{'<', '^'}] = ">^A";
	replace[{'<', '>'}] = ">>A";
	replace[{'<', 'A'}] = ">>^A";

	replace[{'v', '<'}] = "<A";
	replace[{'v', 'v'}] = "A";
	replace[{'v', '^'}] = "^A";
	replace[{'v', '>'}] = ">A";
	replace[{'v', 'A'}] = "^>A"; // seems to be better than ">^A"

	replace[{'^', '<'}] = "v<A";
	replace[{'^', 'v'}] = "vA";
	replace[{'^', '^'}] = "A";
	replace[{'^', '>'}] = "v>A"; // seems to be better than ">vA"
	replace[{'^', 'A'}] = ">A";

	replace[{'>', '<'}] = "<<A";
	replace[{'>', 'v'}] = "<A";
	replace[{'>', '^'}] = "<^A"; // seems to be better than "^<A"
	replace[{'>', '>'}] = "A";
	replace[{'>', 'A'}] = "^A";

	replace[{'A', '<'}] = "v<<A";
	replace[{'A', 'v'}] = "<vA"; // seems to be better than "v<A"
	replace[{'A', '^'}] = "<A";
	replace[{'A', '>'}] = "vA";
	replace[{'A', 'A'}] = "A";
	
	const std::array<unsigned, 6> num = {129u, 974u, 805u, 671u, 386u};
	
	unsigned cnt = 0u;
	for (const auto& code : {
		std::string("A^<<A>A^^>AvvvA"),
		std::string("A^^^A<<AvA>>vvA"),
		std::string("A<^^^AvvvA^^Avv>A"),
		std::string("A^^A<<^AvvA>>vA"),
		std::string("A^A<^^Av>AvvA")})
	{
		const auto sz = code.size();
		std::map<std::array<char, 2>, uint64_t> pairs;
		for (size_t k = 1; k < sz; ++k)
			++pairs[{code[k-1], code[k]}];
		
		for (size_t l = 0; l < 25; ++l)
		{
			std::map<std::array<char, 2>, uint64_t> newPairs;
			for (auto& p : pairs)
			{
				const auto repl = std::string("A") + replace[p.first];
				for (size_t k = 1u; k < repl.size(); ++k)
					newPairs[{repl[k-1], repl[k]}] += p.second;
			}
			pairs.swap(newPairs);
			
			if (l == 1u)
			{
				for (auto& p : pairs)
					resA += p.second * num[cnt];
			}
		}
		
		for (auto& p : pairs)
			resB += p.second * num[cnt];
		
		++cnt;
	}

	
	writeSolution(resA, resB);
}


