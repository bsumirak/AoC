/*
 * day17.h
 *
 *  Created on: 2024-12-17
 *      Author: mbreit
 */


template <>
void executeDay<17>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	uint64_t resB = 0u;

	std::array<int64_t, 3> reg;

	for (size_t k = 0; k< 3; ++k)
		infile >> reg[k];

	std::vector<int8_t> code;
	int c = 0;
	while (infile >> c)
		code.push_back(c);

	size_t pc = 0;
	auto run = [&](const std::vector<int8_t>& input, std::vector<int64_t>& output)
	{
		const size_t sz = input.size();
		while (pc < sz)
		{
			int64_t oc = input[pc];
			int64_t op = input[pc + 1];
			pc += 2;
			switch (oc)
			{
				case 0:
					if (op > 3u)
						op = reg[op - 4u];
					reg[0] = reg[0] / (int64_t(1) << op);
					break;
				case 1:
					reg[1] = reg[1] ^ op;
					break;
				case 2:
					if (op > 3u)
						op = reg[op - 4u];
					reg[1] = op % 8u;
					break;
				case 3:
					if (reg[0] != 0)
						pc = op;
					break;
				case 4:
					reg[1] = reg[1] ^ reg[2];
					break;
				case 5:
					if (op > 3u)
						op = reg[op - 4u];
					output.push_back(op % 8u);
					break;
				case 6:
					if (op > 3u)
						op = reg[op - 4u];
					reg[1] = reg[0] / (int64_t(1) << op);
					break;
				case 7:
					if (op > 3u)
						op = reg[op - 4u];
					reg[2] = reg[0] / (int64_t(1) << op);
					break;
			}
		}
	};

	std::vector<int64_t> output;
	run(code, output);
	std::string resA;
	for (auto v : output)
		resA += std::to_string(v) + ",";


	std::vector<uint64_t> baseA = {0u};
	for (auto it = code.rbegin(); it != code.rend(); ++it)
	{
		std::vector<uint64_t> next;
		for (auto ba : baseA)
		{
			uint64_t v = *it;
			for (uint64_t k = 0; k < 8u; ++k)
			{
				auto a = ba + k;
				auto b = k ^ 5u;
				auto c = a / (uint64_t(1) << b);
				b = b ^ c;
				b = b ^ 6;
				b = b % 8u;
				if (b == v)
					next.push_back(8u * a);
			}
		}
		if (next.empty())
			std::cout << "zero" << std::endl;
		baseA.swap(next);
	}

	resB = baseA.front() / 8u;

	writeSolution(resA, resB);
}

