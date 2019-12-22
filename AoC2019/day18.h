/*
 * day18.h
 *
 *  Created on: 2019-12-18
 *      Author: mbreit
 */



struct PosInfo
{
	std::vector<char> accessibleKeys;
	std::vector<int> distToKeys;
	std::vector<std::string> doorsOnPath;
	std::vector<std::string> keysOnPath;
	std::map<std::size_t, std::size_t> keyPos;
};

std::ostream& operator<<(std::ostream& os, const PosInfo& pi)
{
	const std::size_t sz = pi.accessibleKeys.size();
	for (std::size_t i = 0; i < sz; ++i)
	{
		os << "accessible key: " << (char)pi.accessibleKeys[i] << " at d = "
			<< pi.distToKeys[i] << ", required keys: " << pi.doorsOnPath[i]
			<< ", keys on path: " << pi.keysOnPath[i] << std::endl;
	}

	return os;
}


void findPathToKeys
(
	const std::vector<std::string>& map,
	std::vector<std::vector<int> >& searchMap,
	const std::pair<std::size_t, std::size_t>& curPos,
	PosInfo& posInfo
)
{
	static int s = 0;
	++s;

	posInfo.accessibleKeys.clear();
	posInfo.distToKeys.clear();
	posInfo.doorsOnPath.clear();
	posInfo.keysOnPath.clear();
	posInfo.keyPos.clear();

	struct PathInfo
	{
		PathInfo(std::size_t _r, std::size_t _c, int _l,
			const std::string& _d, const std::string& _k) :
			r(_r), c(_c), l(_l), d(_d), k(_k) {}

		std::size_t r;
		std::size_t c;
		int l;
		std::string d;
		std::string k;
	};

	char initVal = map[curPos.first][curPos.second];

	std::queue<PathInfo> q;
	q.push(PathInfo(curPos.first, curPos.second, 0, "", ""));
	while (!q.empty())
	{
		PathInfo pi = q.front();
		q.pop();

		if (searchMap[pi.r][pi.c] == s)
			continue;
		searchMap[pi.r][pi.c] = s;

		// found a key
		char posValue = map[pi.r][pi.c];
		if (posValue >= 'a' && posValue <= 'z' && posValue != initVal)
		{
			posInfo.accessibleKeys.push_back(posValue);
			posInfo.distToKeys.push_back(pi.l);
			posInfo.doorsOnPath.push_back(pi.d);
			posInfo.keysOnPath.push_back(pi.k);
			posInfo.keyPos[posValue-'a'] = posInfo.accessibleKeys.size()-1;
			pi.k += posValue;
			//continue; // do not find keys that contain others in their min path
		}

		// add a door
		if (posValue >= 'A' && posValue <= 'Z')
			pi.d += posValue - 'A' + 'a';

		// next tile
		if (pi.r > 0)
		{
			posValue = map[pi.r-1][pi.c];
			if (searchMap[pi.r-1][pi.c] != s && posValue != '#')
				q.push(PathInfo(pi.r-1, pi.c, pi.l+1, pi.d, pi.k));
		}
		if (pi.r < map.size()-1)
		{
			posValue = map[pi.r+1][pi.c];
			if (searchMap[pi.r+1][pi.c] != s && posValue != '#')
			q.push(PathInfo(pi.r+1, pi.c, pi.l+1, pi.d, pi.k));
		}
		if (pi.c > 0)
		{
			posValue = map[pi.r][pi.c-1];
			if (searchMap[pi.r][pi.c-1] != s && posValue != '#')
			q.push(PathInfo(pi.r, pi.c-1, pi.l+1, pi.d, pi.k));
		}
		if (pi.c < map[0].size()-1)
		{
			posValue = map[pi.r][pi.c+1];
			if (searchMap[pi.r][pi.c+1] != s && posValue != '#')
			q.push(PathInfo(pi.r, pi.c+1, pi.l+1, pi.d, pi.k));
		}
	}
}


template <>
void executeDay<18>(const std::string& fn)
{
	// read input
	std::vector<std::string> map(1);
	{
		std::ifstream infile(fn.c_str());
		while (std::getline(infile, map.back()))
			map.resize(map.size() + 1);
		map.resize(map.size() - 1);
	}
	std::size_t nRows = map.size();
	std::size_t nCols = map[0].size();


	// find current position and key positions
	std::vector<std::vector<int> > searchMap(nRows, std::vector<int>(nCols, 0));
	typedef std::pair<std::size_t, std::size_t> Coord;
	Coord curPos;
	std::map<char, Coord> keyPos;
	for (std::size_t r = 0; r < nRows; ++r)
	{
		for (std::size_t c = 0; c < nRows; ++c)
		{
			if (map[r][c] == '@')
			{
				curPos.first = r;
				curPos.second = c;
			}
			else if (map[r][c] >= 'a' && map[r][c] <= 'z')
				keyPos[map[r][c]] = std::make_pair(r, c);
			else if (map[r][c] == '#')
				searchMap[r][c] = -1;
		}
	}

	// part a
	int sola = -1;
#if 0
	{
		// find distances from every significant point (key or start) to every key
		std::vector<PosInfo> posInfos(27);
		for (char c = 'a'; c <= 'z'; ++c)
			findPathToKeys(map, searchMap, keyPos[c], posInfos[c-'a']);
		findPathToKeys(map, searchMap, curPos, posInfos[26]);

		for (std::size_t i = 0; i < 27; ++i)
		{
			std::cout << "pos info for " << ('a' + i) << ":" << std::endl
				<< posInfos[i] << std::endl;
		}

		int dist = 0;
		int minDist = std::numeric_limits<int>::max();
		std::vector<int> nnDist(26);
		for (std::size_t i = 0; i < 26; ++i)
			nnDist[i] = posInfos[i].distToKeys[0];

		int minRemDist = 0;
		for (std::size_t i = 0; i < 26; ++i)
		{
			const int keyPos = posInfos[26].accessibleKeys[i] - 'a';
			nnDist[keyPos] = std::min(nnDist[keyPos], posInfos[26].distToKeys[i]);
			minRemDist += nnDist[keyPos];
		}

		std::array<bool, 26> keys;
		std::fill(keys.begin(), keys.end(), false);

		struct DecisionInfo
		{
			std::size_t curPos;
			std::size_t nextKeyInd;
		};

		std::stack<DecisionInfo> stack;
		stack.push(DecisionInfo());
		stack.top().curPos = 26;
		stack.top().nextKeyInd = std::size_t(-1);

		while (!stack.empty())
		{
			DecisionInfo& di = stack.top();
			++di.nextKeyInd;

			// backtracking corrections
			if (di.nextKeyInd)
			{
				dist -= posInfos[di.curPos].distToKeys[di.nextKeyInd - 1];
				keys[posInfos[di.curPos].accessibleKeys[di.nextKeyInd - 1] - 'a'] = false;
				minRemDist += nnDist[posInfos[di.curPos].accessibleKeys[di.nextKeyInd - 1] - 'a'];
			}

			// find next accessible key that is not yet picked up
			bool foundNextKey = false;
			while (di.nextKeyInd < posInfos[di.curPos].accessibleKeys.size())
			{
				const char nextKey = posInfos[di.curPos].accessibleKeys[di.nextKeyInd];

				// already picked up
				if (keys[nextKey - 'a'])
				{
				//	std::cout << std::string(stack.size(), ' ')
				//		<< "Key " << nextKey << " already picked up." << std::endl;
					++di.nextKeyInd;
					continue;
				}

				// check accessibility
				const std::string& reqKeys = posInfos[di.curPos].doorsOnPath[di.nextKeyInd];
				std::size_t sz = reqKeys.size();
				bool accessible = true;
				for (std::size_t c = 0; c < sz; ++c)
				{
					if (!keys[reqKeys[c] - 'a'])
					{
					//	std::cout << std::string(stack.size(), ' ')
					//		<< "Key " << nextKey << " not yet accessible "
					//		<< "(missing key " << reqKeys[c] << ")." << std::endl;
						accessible = false;
						break;
					}
				}

				if (!accessible)
				{
					++di.nextKeyInd;
					continue;
				}

				// check that minimal path does not contain another (unpicked) key
				const std::string& betterKeys = posInfos[di.curPos].keysOnPath[di.nextKeyInd];
				sz = betterKeys.size();
				bool unpickedKeyOnPath = false;
				for (std::size_t c = 0; c < sz; ++c)
				{
					if (!keys[betterKeys[c] - 'a'])
					{
					//	std::cout << std::string(stack.size(), ' ')
					//		<< "Key " << nextKey << " not yet accessible "
					//		<< "(missing key " << reqKeys[c] << ")." << std::endl;
						unpickedKeyOnPath = true;
						break;
					}
				}

				if (unpickedKeyOnPath)
				{
					++di.nextKeyInd;
					continue;
				}

				// check if distance is too large, we need not bother
				if (dist + posInfos[di.curPos].distToKeys[di.nextKeyInd] + minRemDist
					- nnDist[posInfos[di.curPos].accessibleKeys[di.nextKeyInd] - 'a'] >= minDist)
				{
				//	std::cout << std::string(stack.size(), ' ')
				//		<< "Key " << nextKey << " too far away." << std::endl;

					++di.nextKeyInd;
					continue;
				}


				foundNextKey = true;
				break;
			}

			// no more keys
			if (!foundNextKey)
			{
				if (stack.size() == 27)
				{
					minDist = dist;
					//std::cout << "current minDist: " << minDist << std::endl;
				}
				else
				{
				//	std::cout << std::string(stack.size(), ' ')
				//		<< "No more keys to test." << std::endl;
				}

				stack.pop();
				continue;
			}

			// pick up next key
			stack.push(DecisionInfo());
			stack.top().curPos = posInfos[di.curPos].accessibleKeys[di.nextKeyInd] - 'a';
			stack.top().nextKeyInd = std::size_t(-1);
			dist += posInfos[di.curPos].distToKeys[di.nextKeyInd];
			minRemDist -= nnDist[stack.top().curPos];
			keys[stack.top().curPos] = true;
			//std::cout << std::string(stack.size(), ' ')
			//	<< "Picking up key " << (char)(stack.top().curPos + 'a') << "." << std::endl;
		}

		sola = minDist;
	}
#endif

	// part b
	int solb = -1;
	{
		map[curPos.first][curPos.second] = '#';
		map[curPos.first-1][curPos.second] = '#';
		map[curPos.first+1][curPos.second] = '#';
		map[curPos.first][curPos.second-1] = '#';
		map[curPos.first][curPos.second+1] = '#';
		Coord curPos1 = {curPos.first-1, curPos.second-1};
		Coord curPos2 = {curPos.first-1, curPos.second+1};
		Coord curPos3 = {curPos.first+1, curPos.second-1};
		Coord curPos4 = {curPos.first+1, curPos.second+1};

		std::map<int, std::size_t> robotForKey;

		// find distances from every significant point (key or start) to every key
		std::vector<PosInfo> posInfos(30);
		for (char c = 'a'; c <= 'z'; ++c)
			findPathToKeys(map, searchMap, keyPos[c], posInfos[c-'a']);
		findPathToKeys(map, searchMap, curPos1, posInfos[26]);
		findPathToKeys(map, searchMap, curPos2, posInfos[27]);
		findPathToKeys(map, searchMap, curPos3, posInfos[28]);
		findPathToKeys(map, searchMap, curPos4, posInfos[29]);
		for (std::size_t k = 0; k < 4; ++k)
		{
			const std::size_t sz = posInfos[26+k].accessibleKeys.size();
			for (std::size_t c = 0; c < sz; ++c)
				robotForKey[posInfos[26+k].accessibleKeys[c] - 'a'] = k;
		}

		for (std::size_t i = 0; i < 30; ++i)
		{
			std::cout << "pos info for " << ('a' + i) << ":" << std::endl
				<< posInfos[i] << std::endl;
		}

		int dist = 0;
		int minDist = std::numeric_limits<int>::max();
		std::vector<int> nnDist(26);
		for (std::size_t i = 0; i < 26; ++i)
			nnDist[i] = posInfos[i].distToKeys[0];

		int minRemDist = 0;

		for (std::size_t k = 0; k < 4; ++k)
		{
			for (std::size_t i = 0; i < posInfos[26+k].accessibleKeys.size(); ++i)
			{
				const int keyPos = posInfos[26+k].accessibleKeys[i] - 'a';
				nnDist[keyPos] = std::min(nnDist[keyPos], posInfos[26+k].distToKeys[i]);
				minRemDist += nnDist[keyPos];
			}
		}

		std::array<bool, 26> keys;
		std::fill(keys.begin(), keys.end(), false);

		struct DecisionInfo
		{
			std::array<std::size_t, 4> curPos;
			std::size_t nextKey;
		};

		std::stack<DecisionInfo> stack;
		stack.push({ {{std::size_t(26), std::size_t(27),
			std::size_t(28), std::size_t(29)}}, std::size_t(-1)});

		while (!stack.empty())
		{
			DecisionInfo& di = stack.top();
			++di.nextKey;

			// backtracking corrections
			if (di.nextKey)
			{
				const std::size_t rob = robotForKey[di.nextKey - 1];
				const std::size_t pos = posInfos[di.curPos[rob]].keyPos[di.nextKey - 1];
				dist -= posInfos[di.curPos[rob]].distToKeys[pos];
				keys[di.nextKey] = false;
				minRemDist += nnDist[di.nextKey];
			}

			// find next accessible key that is not yet picked up
			bool foundNextKey = false;
			while (di.nextKey < 26)
			{
				const std::size_t rob = robotForKey[di.nextKey];
				const std::size_t pos = posInfos[di.curPos[rob]].keyPos[di.nextKey];

				// already picked up
				if (keys[di.nextKey])
				{
				//	std::cout << std::string(stack.size(), ' ')
				//		<< "Key " << nextKey << " already picked up." << std::endl;
					++di.nextKey;
					continue;
				}

				// check accessibility
				const std::string& reqKeys = posInfos[di.curPos[rob]].doorsOnPath[pos];
				std::size_t sz = reqKeys.size();
				bool accessible = true;
				for (std::size_t c = 0; c < sz; ++c)
				{
					if (!keys[reqKeys[c] - 'a'])
					{
					//	std::cout << std::string(stack.size(), ' ')
					//		<< "Key " << nextKey << " not yet accessible "
					//		<< "(missing key " << reqKeys[c] << ")." << std::endl;
						accessible = false;
						break;
					}
				}

				if (!accessible)
				{
					++di.nextKey;
					continue;
				}

				// check that minimal path does not contain another (unpicked) key
				const std::string& betterKeys = posInfos[di.curPos[rob]].keysOnPath[pos];
				sz = betterKeys.size();
				bool unpickedKeyOnPath = false;
				for (std::size_t c = 0; c < sz; ++c)
				{
					if (!keys[betterKeys[c] - 'a'])
					{
					//	std::cout << std::string(stack.size(), ' ')
					//		<< "Key " << nextKey << " not yet accessible "
					//		<< "(missing key " << reqKeys[c] << ")." << std::endl;
						unpickedKeyOnPath = true;
						break;
					}
				}

				if (unpickedKeyOnPath)
				{
					++di.nextKey;
					continue;
				}

				// if distance is too large, we need not bother
				if (dist + posInfos[di.curPos[rob]].distToKeys[pos] + minRemDist
					- nnDist[di.nextKey] >= minDist)
				{
				//	std::cout << std::string(stack.size(), ' ')
				//		<< "Key " << nextKey << " too far away." << std::endl;

					++di.nextKey;
					continue;
				}


				foundNextKey = true;
				break;
			}

			// no more keys
			if (!foundNextKey)
			{
				if (stack.size() == 27)
				{
					minDist = dist;
					//std::cout << "current minDist: " << minDist << std::endl;
				}
				else
				{
				//	std::cout << std::string(stack.size(), ' ')
				//		<< "No more keys to test." << std::endl;
				}

				stack.pop();
				continue;
			}

			// pick up next key
			const std::size_t rob = robotForKey[di.nextKey - 1];
			const std::size_t pos = posInfos[di.curPos[rob]].keyPos[di.nextKey];
			stack.push({di.curPos, std::size_t(-1)});
			stack.top().curPos[rob] = di.nextKey;
			dist += posInfos[di.curPos[rob]].distToKeys[pos];
			minRemDist -= nnDist[di.nextKey];
			keys[di.nextKey] = true;
			//std::cout << std::string(stack.size(), ' ')
			//	<< "Picking up key " << (char)(stack.top().curPos + 'a') << "." << std::endl;
		}

		solb = minDist;
	}


	writeSolution(sola, solb);
}


