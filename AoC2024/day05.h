/*
 * day05.h
 *
 *  Created on: 2024-12-05
 *      Author: mbreit
 */

template <>
void executeDay<5>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::map<unsigned, std::vector<unsigned>> rules;
	std::vector<std::vector<unsigned>> updates;

	std::string line;
	while (std::getline(infile, line))
	{
		std::regex re("(\\d*)\\|(\\d*)");
		std::smatch match;
		if (!std::regex_match(line, match, re))
			break;

		rules[std::stoul(match.str(2))].push_back(std::stoul(match.str(1)));
	}
	while (std::getline(infile, line))
	{
		updates.emplace_back();
		std::istringstream iss(line);
		std::string s;
		while (std::getline(iss, s, ','))
			updates.back().push_back(std::stoul(s));
	}

	uint64_t resA = 0;
	uint64_t resB = 0;

	for (auto& update : updates)
	{
		bool valid = true;
		const auto sz = update.size();
		for (size_t k = 0; k < sz; ++k)
		{
			auto it = rules.find(update[k]);
			if (it == rules.end())
				continue;

			const auto& precond = it->second;
			for (auto p : precond)
			{
				bool foundBefore = false;
				for (size_t l = 0; l < k; ++l)
				{
					if (update[l] == p)
					{
						foundBefore = true;
						break;
					}
				}

				bool foundAfter = false;
				for (size_t l = k + 1u; l < sz; ++l)
				{
					if (update[l] == p)
					{
						foundAfter = true;
						break;
					}
				}

				if (!foundBefore && foundAfter)
				{
					valid = false;
					break;
				}
			}

			if (!valid)
				break;
		}

		if (valid)
		{
			resA += update[update.size() / 2u];
			continue;
		}

		while (!valid)
		{
			valid = true;

			for (size_t k = 0; k < sz; ++k)
			{
				auto it = rules.find(update[k]);
				if (it == rules.end())
					continue;

				const auto& precond = it->second;
				for (auto p : precond)
				{
					bool foundBefore = false;
					for (size_t l = 0; l < k; ++l)
					{
						if (update[l] == p)
						{
							foundBefore = true;
							break;
						}
					}

					unsigned foundAfter = k;
					for (size_t l = k + 1u; l < sz; ++l)
					{
						if (update[l] == p)
						{
							foundAfter = l;
							break;
						}
					}

					if (!foundBefore && foundAfter > k)
					{
						for (size_t l = k; l < foundAfter; ++l)
							std::swap(update[l], update[l + 1u]);
						valid = false;
						break;
					}
				}
			}
		}

		resB += update[update.size() / 2u];
	}


	writeSolution(resA, resB);
}


