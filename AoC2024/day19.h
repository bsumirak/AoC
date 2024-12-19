/*
 * day19.h
 *
 *  Created on: 2024-12-19
 *      Author: mbreit
 */

uint64_t recurse19(const std::vector<std::string>& supply, const std::string_view patt)
{
	const auto sz = patt.size();
	if (sz == 0)
		return uint64_t(1);
	
	uint64_t num = 0u;
	
	const auto p = sz / 2u;
	const char ch = patt[p];
	for (const auto& s : supply)
	{
		if (s.size() > sz)
			break; // supply is sorted w.r.t. length

		auto it = s.begin() + std::max(sz, p + s.size()) - sz;
		const auto end = s.begin() + std::min(s.size(), p + 1u);
		while ((it = std::find(it, end, ch)) != end)
		{
			const auto m = (size_t)std::distance(s.begin(), it);
			++it;
		
			const std::string_view pv(patt.begin() + p - m, patt.begin() + p - m + s.size());
			if (pv != s)
				continue;
			
			uint64_t n1 = recurse19(supply, std::string_view(patt.begin(), patt.begin() + p - m));
			uint64_t n2 = recurse19(supply, std::string_view(patt.begin() + p - m + s.size(), patt.end()));
			num += n1 * n2;
		}
	}
	
	return num;
}


template <>
void executeDay<19>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	
	uint64_t resA = 0u;
	uint64_t resB = 0u;
	
	std::vector<std::string> supply;
	
	std::string line;
	std::getline(infile, line);
	std::istringstream iss(line);
	std::string s;
	while (iss >> s)
		supply.emplace_back(std::move(s));
	std::sort(supply.begin(), supply.end(),
		[](const auto& s1, const auto& s2) {return s1.size() < s2.size();});
	
	std::getline(infile, line);
	while (std::getline(infile, line))
	{
		const size_t num = recurse19(supply, line);
		if (num)
			++resA;
		resB += num;
	}


	writeSolution(resA, resB);
}


