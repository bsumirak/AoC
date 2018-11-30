/*
 * day04.h
 *
 *  Created on: 04.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<4>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::string line;
	int suma = 0;
	int sumb = 0;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		// part a
		std::set<std::string> passphrase;
		std::string tmp;
		bool valid = true;
		while (iss >> tmp)
		{
			std::pair<std::set<std::string>::iterator, bool> res = passphrase.insert(tmp);
			if (!res.second)
			{
				valid = false;
				break;
			}
		}

		if (valid) ++suma;

		// part b
		std::vector<std::string> pp;
		valid = true;
		std::istringstream issb(line);
		while (issb >> tmp)
		{
			// compare with each already processed word in phrase
			size_t sz = pp.size();
			for (size_t i = 0; i < sz; ++i)
			{
				const std::string& cur = pp[i];
				size_t nChar = cur.size();

				if (tmp.size() != nChar)
					continue;

				// save all char frequencies in map for current and new string
				std::map<char, size_t> mTmp, mCur;
				for (size_t c = 0; c < nChar; ++c)
				{
					std::map<char, size_t>::iterator itTmp, itCur;

					if ((itTmp = mTmp.find(tmp[c])) != mTmp.end())
						++(itTmp->second);
					else
						mTmp[tmp[c]] = 1;

					if ((itCur = mCur.find(cur[c])) != mCur.end())
						++(itCur->second);
					else
						mCur[cur[c]] = 1;
				}

				// compare frequencies
				bool unequal = false;
				std::map<char, size_t>::const_iterator itTmp = mTmp.begin();
				std::map<char, size_t>::const_iterator itTmpEnd = mTmp.end();
				for (; itTmp != itTmpEnd; ++itTmp)
				{
					char c = itTmp->first;
					size_t cnt = itTmp->second;
					std::map<char, size_t>::iterator itCur;
					if ((itCur = mCur.find(c)) != mCur.end())
					{
						if (itCur->second != cnt)
						{
							unequal = true;
							break;
						}
					}
					else
					{
						unequal = true;
						break;
					}
				}


				if (!unequal)
				{
					valid = false;
					break;
				}
			}

			// if no double entry, add word to phrase; otherwise phrase invalid
			if (valid)
				pp.push_back(tmp);
			else
				break;
		}

		if (valid)
			++sumb;
	}

	writeSolution(suma, sumb);
}


