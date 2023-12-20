/*
 * day20.h
 *
 *  Created on: 2023-12-20
 *      Author: mbreit
 */

template <>
void executeDay<20>(const std::string& fn)
{
	// parse input
	std::ifstream infile(fn.c_str());
	
	struct Module
	{
		std::string name;
		char type;
		std::vector<bool> state;
		std::queue<std::pair<bool, size_t>> inputs;
		std::vector<size_t> targets;
		std::vector<size_t> sources;
	};
	
	std::vector<Module> modules;
	std::vector<std::vector<std::string>> tmpTargets;
	
	std::string line;
	while (std::getline(infile, line))
	{
		modules.emplace_back();
		auto& mod = modules.back();
		
		std::istringstream iss(line);
		std::string s;
		iss >> s;
		char c = s[0];
		mod.name = c == 'b' ? s : s.substr(1);
		mod.type = c;

		iss >> s;
		
		tmpTargets.emplace_back();
		while (iss >> s)
			tmpTargets.back().push_back(s.back() == ',' ? s.substr(0, s.size() - 1) : s);
	}

	size_t idx = 0;	
	for (auto& mod : modules)
	{
		const auto& targets = tmpTargets[idx];
		mod.targets.reserve(targets.size());
		for (const auto& tgt : targets)
		{
			const auto it = std::find_if(modules.begin(), modules.end(),
				[&](const Module& m){return m.name == tgt;});
			mod.targets.push_back(std::distance(modules.begin(), it));
			
			if (it != modules.end())
				it->sources.push_back(idx);
		}
		
		++idx;
	}
	for (auto& mod : modules)
	{	
		if (mod.type == '%')
			mod.state.push_back(false);
		else if (mod.type == '&')
			mod.state.resize(mod.sources.size(), false);
	}
	

	// part a
	uint64_t lowCnt = 0;
	uint64_t highCnt = 0;
	
	const auto bcIdx = std::distance(modules.begin(), std::find_if(modules.begin(), modules.end(),
			[&](const Module& m){return m.name == "broadcaster";}));
		
	for (size_t k = 0; k < 1000; ++k)
	{
		modules[bcIdx].inputs.push({0, 0});
	
		std::queue<size_t> q;
		q.push(bcIdx);
	
		while (!q.empty())
		{
			auto modIdx = q.front();
			auto& mod = modules[modIdx];
			q.pop();
		
			bool pulse = mod.inputs.front().first;
			size_t src = mod.inputs.front().second;
			mod.inputs.pop();
		
			switch (mod.type)
			{
				case 'b':
				{
					auto& cntr = pulse ? highCnt : lowCnt;
					cntr += mod.targets.size();
					for (auto trg : mod.targets)
					{
						if (trg >= modules.size())
							continue;
						modules[trg].inputs.push({pulse, modIdx});
						q.push(trg);
					}
					break;
				}
				case '%':
				{
					if (!pulse)
					{
						mod.state[0] = !mod.state[0];
						auto& cntr = mod.state[0] ? highCnt : lowCnt;
						cntr += mod.targets.size();
						for (auto& trg : mod.targets)
						{
							if (trg >= modules.size())
								continue;
							modules[trg].inputs.push({mod.state[0], modIdx});
							q.push(trg);
						}
					}
					break;
				}
				case '&':
				{
					auto srcIdx = std::distance(mod.sources.begin(),
						std::lower_bound(mod.sources.begin(), mod.sources.end(), src));
					mod.state[srcIdx] = pulse;
					bool allHigh = true;
					for (const auto s : mod.state)
						if (!s)
						{
							allHigh = false;
							break;
						}
					auto& cntr = !allHigh ? highCnt : lowCnt;
					cntr += mod.targets.size();
					for (auto& trg : mod.targets)
					{
						if (trg >= modules.size())
							continue;
						modules[trg].inputs.push({!allHigh, modIdx});
						q.push(trg);
					}
					break;
				}
			}
		}
	}
	
	uint64_t resA = (lowCnt + 1000u) * highCnt;


	// part b
	uint64_t resB = 1u;
	auto it = std::find_if(modules.begin(), modules.end(), [&](const Module& mod)
		{return std::find(mod.targets.begin(), mod.targets.end(), modules.size()) != mod.targets.end();});
	const auto& multipliers = it->sources;
	
	for (auto mul : multipliers)
	{
		const auto andIdx = modules[mul].sources[0];
		auto it2 = std::find_if(modules[bcIdx].targets.begin(), modules[bcIdx].targets.end(),
			[&](size_t tgt){return std::find(modules[tgt].targets.begin(), modules[tgt].targets.end(),
				andIdx) != modules[tgt].targets.end();});
		
		uint64_t fct = 0u;
		uint64_t add = 1u;
		size_t idx = *it2;
		
		while (true)
		{
			const auto& tgts = modules[idx].targets;
			if (tgts.size() == 2)
			{
				fct += add;
				idx = tgts[0] == andIdx ? tgts[1] : tgts[0];
			}
			else if (tgts[0] == andIdx)
			{
				fct += add;
				break;
			}
			else
			{
				idx = tgts[0];
			}
			
			add *= 2;
		}

		resB *= fct;
	}
	
	
	writeSolution(resA, resB);
}


