/*
 * day12.h
 *
 *  Created on: 2023-12-12
 *      Author: mbreit
 */


bool findFirstPossibility12(const std::string& record, const std::vector<size_t>& ctrl, std::vector<size_t>& ret,
	size_t pos, size_t idx, size_t endPos, size_t endIdx)
{
	if (idx == endIdx)
	{
		for (size_t k = pos; k < endPos; ++k)
			if (record[k] == '#')
				return false;
		return true;
	}

	const size_t len = ctrl[idx];
	for (size_t k = pos; k < endPos - len + 1; ++k)
	{
		bool fits = true;
		for (size_t j = 0; j < len; ++j)
		{
			if (record[k + j] == '.')
			{
				fits = false;
				break;
			}
		}
		fits &= (k + len == endPos || record[k + len] != '#');
		if (fits && findFirstPossibility12(record, ctrl, ret, k + len + 1, idx + 1, endPos, endIdx))
		{
			ret[idx] = k;
			return true;
		}

		if (record[k] == '#')
			break;
	}

	return false;
}


bool findLastPossibility12(const std::string& record, const std::vector<size_t>& ctrl, std::vector<size_t>& ret,
	size_t pos, size_t idx, size_t endPos, size_t endIdx)
{
	if (endIdx == idx)
	{
		for (size_t k = endPos + 1; k > pos; --k)
			if (record[k - 1] == '#')
				return false;
		return true;
	}

	const size_t len = ctrl[endIdx - 1];
	for (size_t k = endPos; k > pos + len - 1; --k)
	{
		bool fits = true;
		for (size_t j = 0; j < len; ++j)
		{
			if (record[k - j - 1] == '.')
			{
				fits = false;
				break;
			}
		}
		fits &= (k - len == pos || record[k - len - 1] != '#');
		if (fits && findLastPossibility12(record, ctrl, ret, pos, idx, k - len - 1, endIdx - 1))
		{
			ret[endIdx - 1] = k - 1;
			return true;
		}

		if (record[k - 1] == '#')
			break;
	}

	return false;
}


size_t findAllPossibilities12(const std::string& record, const std::vector<size_t>& ctrl,
	std::array<std::vector<size_t>, 2>& fl,
	size_t pos, size_t idx, size_t endPos, size_t endIdx)
{
	if (idx == endIdx)
	{
		for (size_t k = pos; k < endPos; ++k)
			if (record[k] == '#')
				return 0;
		return 1;
	}

	if (!findFirstPossibility12(record, ctrl, fl[0], pos, idx, endPos, endIdx))
		return 0;
	findLastPossibility12(record, ctrl, fl[1], pos, idx, endPos, endIdx);

	size_t curIdx = idx + (endIdx - idx) / 2;
	size_t ret = 0;
	const size_t len = ctrl[curIdx];
	for (size_t k = fl[0][curIdx]; k <= fl[1][curIdx] - len + 1; ++k)
	{
		bool fits = true;
		for (size_t j = 0; j < len; ++j)
		{
			if (record[k + j] == '.')
			{
				fits = false;
				break;
			}
		}
		fits &= (k + len == endPos || record[k + len] != '#') && (k == 0 || record[k - 1] != '#');
		if (fits)
		{
			// divide and conquer!
			size_t before = findAllPossibilities12(record, ctrl, fl, pos, idx, k > 0 ? k - 1 : 0, curIdx);
			size_t after = findAllPossibilities12(record, ctrl, fl, k + len + 1, curIdx + 1, endPos, endIdx);

			ret += before * after;
		}
	}

	return ret;
}



template <>
void executeDay<12>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::vector<std::string> springRecords;
	std::vector<std::vector<size_t>> ctrl;
	std::string s;
	while (std::getline(infile, s))
	{
		springRecords.emplace_back();
		ctrl.emplace_back();

		std::istringstream iss(s);
		iss >> springRecords.back();

		size_t u;
		while (iss >> u)
			ctrl.back().push_back(u);
	}


	// part a
	size_t resA = 0;
	for (size_t k = 0; k < springRecords.size(); ++k)
	{
		std::array<std::vector<size_t>, 2> fl{std::vector<size_t>(ctrl[k].size()), std::vector<size_t>(ctrl[k].size())};
		resA += findAllPossibilities12(springRecords[k], ctrl[k], fl, 0, 0, springRecords[k].size(), ctrl[k].size());
	}


	// part b
	for (auto& rec : springRecords)
	{
		auto cp = rec;
		rec.append("?");
		rec.append(rec);
		rec.append(rec);
		rec.append(cp);
	}
	for (auto& c : ctrl)
	{
		const size_t sz = c.size();
		c.resize(5u * sz);
		for (size_t k = sz; k < 5 * sz; ++k)
			c[k] = c[k % sz];
	}

	size_t resB = 0;
	for (size_t k = 0; k < springRecords.size(); ++k)
	{
		std::array<std::vector<size_t>, 2> fl{std::vector<size_t>(ctrl[k].size()), std::vector<size_t>(ctrl[k].size())};
		resB += findAllPossibilities12(springRecords[k], ctrl[k], fl, 0, 0, springRecords[k].size(), ctrl[k].size());
	}


	writeSolution(resA, resB);
}


