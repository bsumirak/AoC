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
	std::array<std::size_t, 26> keyPos;
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


template <int NRobots>
int findShortestPathToAllKeys
(
	const std::vector<std::string>& map,
	std::vector<std::vector<int> >& searchMap,
	const std::map<char, std::pair<std::size_t, std::size_t> >& keyPos,
	const std::array<std::pair<std::size_t, std::size_t>, NRobots>& curPos
)
{
	const std::size_t nKeys = keyPos.size();
	std::vector<std::size_t> robotForKey(nKeys);

	// find distances from every significant point (key or start) to every key
	std::vector<PosInfo> posInfos(nKeys + NRobots);
	for (auto it = keyPos.begin(); it != keyPos.end(); ++it)
		findPathToKeys(map, searchMap, it->second, posInfos[it->first-'a']);
	for (std::size_t i = 0; i < NRobots; ++i)
		findPathToKeys(map, searchMap, curPos[i], posInfos[nKeys+i]);

	for (std::size_t k = 0; k < NRobots; ++k)
	{
		const std::size_t sz = posInfos[nKeys+k].accessibleKeys.size();
		for (std::size_t c = 0; c < sz; ++c)
			robotForKey[posInfos[nKeys+k].accessibleKeys[c] - 'a'] = k;
	}

	int dist = 0;
	int minDist = std::numeric_limits<int>::max();
	std::vector<int> nnDist(nKeys, 0);
	for (std::size_t i = 0; i < nKeys; ++i)
		if (posInfos[i].distToKeys.size())
			nnDist[i] = posInfos[i].distToKeys[0];

	// calculate minimum remaining start dist and all minimal dists
	int minRemDist = 0;

	for (std::size_t k = 0; k < NRobots; ++k)
	{
		for (std::size_t i = 0; i < posInfos[nKeys+k].accessibleKeys.size(); ++i)
		{
			const int keyPos = posInfos[nKeys+k].accessibleKeys[i] - 'a';
			nnDist[keyPos] = std::min(nnDist[keyPos], posInfos[nKeys+k].distToKeys[i]);
			minRemDist += nnDist[keyPos];
		}
	}

	std::vector<bool> keys(nKeys, false);

	struct DecisionInfo
	{
		std::array<std::size_t, NRobots> curPos;
		std::size_t nextKey;
	};

	std::stack<DecisionInfo> stack;

	std::array<std::size_t, NRobots> startPos;
	for (std::size_t i = 0; i < NRobots; ++i)
		startPos[i] = nKeys + i;
	stack.push({startPos, std::size_t(-1)});

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
			keys[di.nextKey-1] = false;
			minRemDist += nnDist[di.nextKey-1];
		}

		// find next accessible key that is not yet picked up
		bool foundNextKey = false;
		while (di.nextKey < nKeys)
		{
			const std::size_t rob = robotForKey[di.nextKey];
			const std::size_t pos = posInfos[di.curPos[rob]].keyPos[di.nextKey];

			// already picked up
			if (keys[di.nextKey])
			{
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
				++di.nextKey;
				continue;
			}


			foundNextKey = true;
			break;
		}

		// no more keys
		if (!foundNextKey)
		{
			if (stack.size() == nKeys+1)
				minDist = dist;

			stack.pop();
			continue;
		}

		// pick up next key
		const std::size_t rob = robotForKey[di.nextKey];
		const std::size_t pos = posInfos[di.curPos[rob]].keyPos[di.nextKey];
		stack.push({di.curPos, std::size_t(-1)});
		stack.top().curPos[rob] = di.nextKey;
		dist += posInfos[di.curPos[rob]].distToKeys[pos];
		minRemDist -= nnDist[di.nextKey];
		keys[di.nextKey] = true;
	}

	return minDist;
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
		for (std::size_t c = 0; c < nCols; ++c)
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
	{
		std::array<Coord, 1> curPosAll = {{ curPos }};

		sola = findShortestPathToAllKeys<1>(map, searchMap, keyPos, curPosAll);
	}

	// part b
	int solb = -1;
	{
		map[curPos.first][curPos.second] = '#';
		map[curPos.first-1][curPos.second] = '#';
		map[curPos.first+1][curPos.second] = '#';
		map[curPos.first][curPos.second-1] = '#';
		map[curPos.first][curPos.second+1] = '#';

		std::array<Coord, 4> curPosAll = {{
			{curPos.first-1, curPos.second-1},
			{curPos.first-1, curPos.second+1},
			{curPos.first+1, curPos.second-1},
			{curPos.first+1, curPos.second+1}
		}};

		solb = findShortestPathToAllKeys<4>(map, searchMap, keyPos, curPosAll);
	}


	writeSolution(sola, solb);
}


