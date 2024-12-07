/*
 * day07.h
 *
 *  Created on: 2024-12-07
 *      Author: mbreit
 */


bool recurse7(const std::vector<uint64_t>& ops, size_t k, uint64_t res, uint64_t r, bool partB)
{
	if (k == ops.size())
		return r == res;

	// part a
	auto r1 = r + ops[k];
	if (r1 <= res && recurse7(ops, k + 1u, res, r1, partB))
		return true;
	auto r2 = r * ops[k];
	if (r2 <= res && recurse7(ops, k + 1u, res, r2, partB))
		return true;

	if (!partB)
		return false;

	// part b
	auto r3 = std::pow(uint64_t(10), std::ceil(std::log10(ops[k] + 1))) * r + ops[k];
	if (r3 <= res && recurse7(ops, k + 1u, res, r3, true))
		return true;

	return false;
}


template <>
void executeDay<7>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	uint64_t resA = 0;
	uint64_t resB = 0;

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		uint64_t res;
		iss >> res;

		std::vector<uint64_t> ops;
		uint64_t op = 0u;
		while (iss >> op)
			ops.push_back(op);

		if (recurse7(ops, 1u, res, ops[0], false))
		{
			resA += res;
			resB += res;
			continue;
		}

		if (recurse7(ops, 1u, res, ops[0], true))
			resB += res;
	}


	writeSolution(resA, resB);
}


