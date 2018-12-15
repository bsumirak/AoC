/*
 * day15.h
 *
 *  Created on: 15.12.2017
 *      Author: mbreit
 */


struct Warrior
{
	bool operator<(const Warrior& w2) const
	{
		return pos < w2.pos;
	}

	char type;
	int hp;
	std::pair<int, int> pos;
};

struct ReachablePos
{
	size_t curInd;
	std::pair<int, int> pos;
	std::vector<int> path;
};


void printMap(std::vector<std::string>& map)
{
	for (size_t i = 0; i < map.size(); ++i)
		std::cout << map[i] << std::endl;
	std::cout << std::endl;
}

template <>
void executeDay<15>(const std::string& fn)
{
	// read map
	std::ifstream infile(fn.c_str());
	std::vector<std::string> map;
	std::string line;
	while (std::getline(infile, line))
		map.push_back(line);
	const int nRows = map.size();
	const int nCols = map[0].size();

	std::vector<std::string> copyMap(map);


	int solb;
	int elveAttack = 3;
	for (; elveAttack < 100; ++elveAttack)
	{
		map = copyMap;

		// locate warriors
		std::vector<Warrior> units;
		for (int i = 0; i < nRows; ++i)
		{
			for (int j = 0; j < nCols; ++j)
			{
				if (map[i][j] == 'G' || map[i][j] == 'E')
				{
					units.resize(units.size()+1);
					Warrior& g = units.back();
					g.hp = 200;
					g.pos = std::make_pair(i, j);
					g.type = map[i][j];
				}
			}
		}

		bool elfDied = false;

		int round = 1;
		while (true)
		{
			// determine unit order
			std::sort(units.begin(), units.end());

			// start moving
			const size_t nW = units.size();
			for (size_t i = 0; i < nW; ++i)
			{
				Warrior& w = units[i];

				// still alive?
				if (w.hp <= 0)
					continue;

				std::pair<int, int>& pos = w.pos;
				int wType = w.type;

				// does a target exist at al?
				bool targetExists = false;
				for (size_t j = 0; j < nW; ++j)
				{
					Warrior& other = units[j];
					if (wType != other.type && other.hp > 0)
					{
						targetExists = true;
						break;
					}
				}

				if (!targetExists)
					goto endOfBattle;

				// determine nearest target
				std::pair<int, int> enemyPos;
				std::vector<std::pair<int, int> > path;

				std::vector<bool> visited(nRows*nCols, false);
				bool targetFound = false;
				std::queue<std::vector<std::pair<int, int> > > q;
				q.push(std::vector<std::pair<int, int> >(1));
				q.front()[0] = pos;
				visited[pos.first*nCols+pos.second] = true;
				while (!q.empty())
				{
					std::vector<std::pair<int, int> >& curPath = q.front();
					std::pair<int, int>& curPos = curPath.back();

					// foe attackable?
					if (curPos.first > 0 && map[curPos.first-1][curPos.second] == (2*'F')-wType)
					{
						enemyPos = std::make_pair(curPos.first-1, curPos.second);
						path = curPath;
						targetFound = true;
						break;
					}

					if (curPos.second > 0 && map[curPos.first][curPos.second-1] == (2*'F')-wType)
					{
						enemyPos = std::make_pair(curPos.first, curPos.second-1);
						path = curPath;
						targetFound = true;
						break;
					}

					if (curPos.second < nCols-1 && map[curPos.first][curPos.second+1] == (2*'F')-wType)
					{
						enemyPos = std::make_pair(curPos.first, curPos.second+1);
						path = curPath;
						targetFound = true;
						break;
					}

					if (curPos.first < nRows-1 && map[curPos.first+1][curPos.second] == (2*'F')-wType)
					{
						enemyPos = std::make_pair(curPos.first+1, curPos.second);
						path = curPath;
						targetFound = true;
						break;
					}

					// find possible moves
					if (curPos.first > 0 && map[curPos.first-1][curPos.second] == '.' && !visited[(curPos.first-1)*nCols + curPos.second])
					{
						std::vector<std::pair<int, int> > nextPath (curPath);
						nextPath.push_back(std::make_pair(curPos.first-1, curPos.second));
						q.push(nextPath);
						visited[(curPos.first-1)*nCols + curPos.second] = true;
					}
					if (curPos.second > 0 && map[curPos.first][curPos.second-1] == '.' && !visited[(curPos.first)*nCols + curPos.second-1])
					{
						std::vector<std::pair<int, int> > nextPath (curPath);
						nextPath.push_back(std::make_pair(curPos.first, curPos.second-1));
						q.push(nextPath);
						visited[(curPos.first)*nCols + curPos.second-1] = true;
					}
					if (curPos.second < nCols-1 && map[curPos.first][curPos.second+1] == '.' && !visited[(curPos.first)*nCols + curPos.second+1])
					{
						std::vector<std::pair<int, int> > nextPath (curPath);
						nextPath.push_back(std::make_pair(curPos.first, curPos.second+1));
						q.push(nextPath);
						visited[(curPos.first)*nCols + curPos.second+1] = true;
					}
					if (curPos.first < nRows-1 && map[curPos.first+1][curPos.second] == '.' && !visited[(curPos.first+1)*nCols + curPos.second])
					{
						std::vector<std::pair<int, int> > nextPath (curPath);
						nextPath.push_back(std::make_pair(curPos.first+1, curPos.second));
						q.push(nextPath);
						visited[(curPos.first+1)*nCols + curPos.second] = true;
					}

					q.pop();
				}

				// no target reachable
				if (!targetFound)
					continue;

				// we have to move
				if (path.size() > 1)
				{
					map[pos.first][pos.second] = '.';
					pos = path[1];
					map[pos.first][pos.second] = wType;
				}

				// fight ?
				if (path.size() < 3)
				{
					// fight the monster with lowest HP, otherwise reading order

					std::vector<std::pair<int, int> > vTestPos;
					if (pos.first > 0 && map[pos.first-1][pos.second] == (2*'F')-wType)
						vTestPos.push_back(std::make_pair(pos.first-1, pos.second));
					if (pos.second > 0 && map[pos.first][pos.second-1] == (2*'F')-wType)
						vTestPos.push_back(std::make_pair(pos.first, pos.second-1));
					if (pos.second < nCols-1 && map[pos.first][pos.second+1] == (2*'F')-wType)
						vTestPos.push_back(std::make_pair(pos.first, pos.second+1));
					if (pos.first < nRows-1 && map[pos.first+1][pos.second] == (2*'F')-wType)
						vTestPos.push_back(std::make_pair(pos.first+1, pos.second));

					if (!vTestPos.size())
					{
						std::cout << "error1" << std::endl;
						exit(0);
					}

					size_t minFoeInd = 0;
					int minHP = 201;
					for (size_t k = 0; k < vTestPos.size(); ++k)
					{
						std::pair<int, int>& testPos = vTestPos[k];

						// search in unit array
						size_t j = 0;
						for (; j < nW; ++j)
							if (units[j].pos == testPos)
								break;

						if (j == nW)
						{
							std::cout << "error" << std::endl;
							exit(0);
						}

						if (units[j].hp < minHP)
						{
							minHP = units[j].hp;
							minFoeInd = j;
						}
						else if (units[j].hp == minHP)
						{
							if (units[j].pos.first < units[minFoeInd].pos.first
								|| (units[j].pos.first == units[minFoeInd].pos.first
									&& units[j].pos.second < units[minFoeInd].pos.second))
							{
								minHP = units[j].hp;
								minFoeInd = j;
							}
						}
					}

					// strike
					if (wType == 'E')
						units[minFoeInd].hp -= elveAttack;
					else
						units[minFoeInd].hp -= 3;

					// killed?
					if (units[minFoeInd].hp <= 0)
					{
						map[units[minFoeInd].pos.first][units[minFoeInd].pos.second] = '.';
						if (units[minFoeInd].type == 'E')
						{
							elfDied = true;
							break;
						}
					}
				}
			}

			// an elf has died
			if (elfDied)
				break;

			// remaining units
			{
				std::vector<Warrior> remaining;
				for (size_t i = 0; i < nW; ++i)
				{
					if (units[i].hp > 0)
						remaining.push_back(units[i]);
				}

				remaining.swap(units);
			}

			if (round % 1 == 0)
			{
				std::cout << round << std::endl;
//				printMap(map);
			}

//			for (size_t i = 0; i < nW; ++i)
//				if (units[i].hp > 0)
//					std::cout << units[i].type << "(" << units[i].hp << ") " << std::endl;

			++round;
			continue;

	endOfBattle:
			printMap(map);

			// remaining units
			{
				std::vector<Warrior> remaining;
				for (size_t i = 0; i < nW; ++i)
				{
					if (units[i].hp > 0)
					{
//						std::cout << units[i].type << "(" << units[i].hp << ") " << std::endl;
						remaining.push_back(units[i]);
					}
				}

				remaining.swap(units);
			}
			break;
		}

		std::cout << elveAttack << std::endl;
		if (!elfDied)
		{
			int totalHP = 0;
			for (size_t i = 0; i < units.size(); ++i)
				totalHP += units[i].hp;

			solb = totalHP*(round-1);

			break;
		}
	}
/*
	int totalHP = 0;
	for (size_t i = 0; i < units.size(); ++i)
		totalHP += units[i].hp;

	int sola = totalHP*(round-1);
*/
	writeSolution(0, solb);
}


