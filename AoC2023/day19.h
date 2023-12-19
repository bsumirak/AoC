/*
 * day19.h
 *
 *  Created on: 2023-12-19
 *      Author: mbreit
 */

template <>
void executeDay<19>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	
	struct Rule
	{
		unsigned op;
		int cmp;
		std::string target;
	};
	
	std::map<std::string, std::vector<Rule>> workflow;
	
	std::string line;
	while (std::getline(infile, line))
	{
		if (line.empty())
			break;
		
		std::istringstream iss(line);
		
		std::string name;
		iss >> name;
		auto& rules = workflow[name];
		
		std::string op;
		while (iss >> op)
		{
			if (op.size() == 1 || (op[1] != '<' && op[1] != '>'))
			{
				Rule r;
				r.op = 1;
				r.cmp = 0;
				r.target = op;
				rules.push_back(r);
				break;
			}
					
			int opCode = 0;
			switch (op[0])
			{
				case 'x': opCode = 0; break;
				case 'm': opCode = 2; break;
				case 'a': opCode = 4; break;
				case 's': opCode = 6; break;
			}
			
			if (op[1] == '>')
				++opCode;
			
			int cmp;
			iss >> cmp;
			
			std::string trg;
			iss >> trg;
			
			Rule r;
			r.op = opCode;
			r.cmp = cmp;
			r.target = trg;
			
			rules.push_back(r);
		}
	}
	
	std::vector<std::array<int, 4>> parts;
	
	int v;
	while (infile >> v)
	{
		parts.emplace_back();
		parts.back()[0] = v;
		infile >> parts.back()[1];
		infile >> parts.back()[2];
		infile >> parts.back()[3];
	}
	

	// part a
	unsigned resA = 0;
	for (const auto& pt : parts)
	{
		std::string nextRule = "in";
		while (true)
		{
			if (workflow.find(nextRule) == workflow.end())
			{
				std::cout << "no rule named " << nextRule << " in workflow" << std::endl;
				return;
			}
			
			auto& curRules = workflow[nextRule];
			for (const Rule& r : curRules)
			{
				const bool lt = r.op % 2 == 0;
				const int val = pt[r.op / 2];
				const bool opRes = lt ? val < r.cmp : val > r.cmp;
				if (opRes)
				{
					nextRule = r.target;
					break;
				}
			}
			
			if (nextRule == "A")
			{
				resA += pt[0] + pt[1] + pt[2] + pt[3];
				break;
			}
			if (nextRule == "R")
				break;
			
			//std::cout << pt[0] << " " << pt[1] << " " << pt[2] << " " << pt[3] << std::endl;
			//for (const Rule& r : curRules)
			//	std::cout << r.op << " " << r.cmp << " " << r.target << std::endl;
		}
	}


	// part b
	uint64_t resB = 0;
	std::stack<std::array<std::array<unsigned, 2>, 4>> stack;
	stack.push({std::array<unsigned, 2>{0, 4000}, std::array<unsigned, 2>{0, 4000},
		std::array<unsigned, 2>{0, 4000}, std::array<unsigned, 2>{0, 4000}});
	
	std::stack<std::string> ruleStack;
	ruleStack.push("in");
	
	while (!stack.empty())
	{
		auto hyperQuad = stack.top();
		stack.pop();
		
		const auto& ruleName = ruleStack.top();
		if (workflow.find(ruleName) == workflow.end())
		{
			std::cout << "no rule named " << ruleName << " in workflow" << std::endl;
			return;
		}
		const auto& rule = workflow[ruleName];
		ruleStack.pop();
		
		for (const auto& test : rule)
		{
			unsigned rangeInd = test.op / 2;
			auto range = hyperQuad[rangeInd];
			if (test.op % 2 == 0) // < case
			{
				unsigned b = std::min(range[1], (unsigned)test.cmp - 1);
				if (b > range[0])
				{
					hyperQuad[rangeInd][1] = b;
					
					if (test.target == "A")
					{
						resB += uint64_t(hyperQuad[0][1] - hyperQuad[0][0]) * uint64_t(hyperQuad[1][1] - hyperQuad[1][0])
							* uint64_t(hyperQuad[2][1] - hyperQuad[2][0]) * uint64_t(hyperQuad[3][1] - hyperQuad[3][0]);
					}
					else if (test.target != "R")
					{
						stack.push(hyperQuad);
						ruleStack.push(test.target);
					}
						
					hyperQuad[rangeInd][1] = range[1];	
				}
				unsigned a = std::max(range[0], (unsigned)test.cmp - 1);
				if (a < range[1])
				{
					hyperQuad[rangeInd][0] = a;
					continue;
				}
			}
			else // > case
			{
				unsigned a = std::max(range[0], (unsigned)test.cmp);
				if (a < range[1])
				{
					hyperQuad[rangeInd][0] = a;

					if (test.target == "A")
					{
						resB += uint64_t(hyperQuad[0][1] - hyperQuad[0][0]) * uint64_t(hyperQuad[1][1] - hyperQuad[1][0])
							* uint64_t(hyperQuad[2][1] - hyperQuad[2][0]) * uint64_t(hyperQuad[3][1] - hyperQuad[3][0]);
					}
					else if (test.target != "R")
					{
						stack.push(hyperQuad);
						ruleStack.push(test.target);
					}
					hyperQuad[rangeInd][0] = range[0];
				}
				unsigned b = std::min(range[1], (unsigned)test.cmp);
				if (b > range[0])
				{
					hyperQuad[rangeInd][1] = b;
					continue;
				}
			}
			break;
		}
	}
	
	
	writeSolution(resA, resB);
}


