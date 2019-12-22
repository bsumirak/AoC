/*
 * day20.h
 *
 *  Created on: 2019-12-20
 *      Author: mbreit
 */


template <>
void executeDay<20>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::vector<std::string > map;

	std::string line;
	while (std::getline(infile, line))
		map.push_back(line);

	const std::size_t nRows = map.size();
	const std::size_t nCols = map[0].size();


	// identify portals
	typedef std::pair<std::size_t, std::size_t> Coord;
	std::map<Coord, Coord> portalMap;
	std::map<std::pair<char, char>, Coord> portalNameMap;

	Coord startPos;
	Coord endPos;

	for (std::size_t r = 0; r < nRows; ++r)
	{
		for (std::size_t c = 0; c < nCols; ++c)
		{
			if (map[r][c] == ' ' || map[r][c] == '.' || map[r][c] == '#')
				continue;

			char first, second;
			Coord portalCoord;
			if (c > 0 && map[r][c-1] == '.')
			{
				first = map[r][c];
				second = map[r][c+1];
				portalCoord = std::make_pair(r, c-1);
			}
			else if (c > 1 && map[r][c-1] >= 'A' && map[r][c-1] <= 'Z' && map[r][c-2] == '.')
			{
				first = map[r][c-1];
				second = map[r][c];
				portalCoord = std::make_pair(r, c-2);
			}
			else if (c < nCols-1 && map[r][c+1] == '.')
			{
				first = map[r][c-1];
				second = map[r][c];
				portalCoord = std::make_pair(r, c+1);
			}
			else if (c < nCols - 2 && map[r][c+1] >= 'A' && map[r][c+1] <= 'Z' && map[r][c+2] == '.')
			{
				first = map[r][c];
				second = map[r][c+1];
				portalCoord = std::make_pair(r, c+2);
			}
			else if (r > 0 && map[r-1][c] == '.')
			{
				first = map[r][c];
				second = map[r+1][c];
				portalCoord = std::make_pair(r-1, c);
			}
			else if (r > 1 && map[r-1][c] >= 'A' && map[r-1][c] <= 'Z' && map[r-2][c] == '.')
			{
				first = map[r-1][c];
				second = map[r][c];
				portalCoord = std::make_pair(r-2, c);
			}
			else if (r < nRows - 1 && map[r+1][c] == '.')
			{
				first = map[r-1][c];
				second = map[r][c];
				portalCoord = std::make_pair(r+1, c);
			}
			else if (r < nRows -2 && map[r+1][c] >= 'A' && map[r+1][c] <= 'Z' && map[r+2][c] == '.')
			{
				first = map[r][c];
				second = map[r+1][c];
				portalCoord = std::make_pair(r+2, c);
			}
			else
			{
				std::cout << "error finding portals" << std::endl;
				throw std::runtime_error("");
			}


			if (first == 'A' && second == 'A')
			{
				startPos = portalCoord;
				continue;
			}
			if (first == 'Z' && second == 'Z')
			{
				endPos = portalCoord;
				continue;
			}

			if (portalNameMap.find(std::make_pair(first, second)) != portalNameMap.end())
			{
				const Coord otherPortalCoord = portalNameMap[std::make_pair(first, second)];
				if (otherPortalCoord != portalCoord)
				{
					portalMap[otherPortalCoord] = portalCoord;
					portalMap[portalCoord] = otherPortalCoord;
				}
			}
			else
				portalNameMap[std::make_pair(first, second)] = portalCoord;
		}
	}
#if 0
	std::cout << portalMap.size() << std::endl;
	for (auto mapIt = portalMap.begin(); mapIt != portalMap.end(); ++mapIt)
	{
		std::cout << mapIt->first.first << "," << mapIt->first.second << " -> "
			<< mapIt->second.first << "," << mapIt->second.second << std::endl;
	}
#endif

	// part a
	int sola = -1;

	{
		struct PathInfo
		{
			PathInfo(const Coord& c, int l) :
				coord(c), length(l) {}

			Coord coord;
			int length;
		};

		std::queue<PathInfo> q;
		q.push(PathInfo(startPos, 0));

		std::vector<std::vector<bool> > visitMap(map.size(),
			std::vector<bool>(map[0].size(), false));

		while (!q.empty())
		{
			PathInfo pi = q.front();
			q.pop();

			const std::size_t& r = pi.coord.first;
			const std::size_t& c = pi.coord.second;
			if (visitMap[r][c])
				continue;
			visitMap[r][c] = true;

			// if this is the end point
			if (pi.coord == endPos)
			{
				sola = pi.length;
				break;
			}

			// if this is a portal point
			auto it = portalMap.find(pi.coord);
			if (it != portalMap.end())
			{
				const Coord& otherSide = it->second;
				if (!visitMap[otherSide.first][otherSide.second])
				{
					q.push(PathInfo(otherSide, pi.length+1));
					continue;
				}
			}

			// otherwise
			if (c > 0 && !visitMap[r][c-1] && map[r][c-1] == '.')
				q.push(PathInfo(std::make_pair(r, c-1), pi.length+1));
			if (c < nCols-1 && !visitMap[r][c+1] && map[r][c+1] == '.')
				q.push(PathInfo(std::make_pair(r, c+1), pi.length+1));
			if (r > 0 && !visitMap[r-1][c] && map[r-1][c] == '.')
				q.push(PathInfo(std::make_pair(r-1, c), pi.length+1));
			if (r < nRows-1 && !visitMap[r+1][c] && map[r+1][c] == '.')
				q.push(PathInfo(std::make_pair(r+1, c), pi.length+1));
		}
	}


	// part b
	int solb = -1;
	{
		struct PathInfo
		{
			PathInfo(const Coord& c, std::size_t lvl, int l) :
				coord(c), level(lvl), length(l) {}

			Coord coord;
			std::size_t level;
			int length;
		};

		std::queue<PathInfo> q;
		q.push(PathInfo(startPos, 0, 0));

		std::vector<std::vector<std::vector<bool> > > visitMap(1);
		visitMap[0].resize(nRows);
		for (std::size_t r = 0; r < nRows; ++r)
			visitMap[0][r].resize(nCols, false);

		while (!q.empty())
		{
			PathInfo pi = q.front();
			q.pop();

			const std::size_t& lvl = pi.level;
			const std::size_t& r = pi.coord.first;
			const std::size_t& c = pi.coord.second;
			if (visitMap[lvl][r][c])
				continue;
			visitMap[lvl][r][c] = true;

			// if this is the end point
			if (pi.coord == endPos && lvl == 0)
			{
				solb = pi.length;
				break;
			}

			// if this is a portal point
			auto it = portalMap.find(pi.coord);
			if (it != portalMap.end())
			{
				// outer portals on level 0 are closed
				if (lvl > 0 || (pi.coord.first != 2 && pi.coord.first != nRows - 3
					&& pi.coord.second != 2 && pi.coord.second != nCols - 3))
				{
					const Coord& otherSide = it->second;
					if (pi.coord.first == 2 || pi.coord.first == nRows - 3
						|| pi.coord.second == 2 || pi.coord.second == nCols - 3)
					{
						if (!visitMap[lvl-1][otherSide.first][otherSide.second])
						{
							q.push(PathInfo(otherSide, lvl-1, pi.length+1));
							continue;
						}
					}
					else
					{
						if (lvl+1 == visitMap.size())
						{
							visitMap.resize(visitMap.size()+1);
							visitMap.back().resize(nRows);
							for (std::size_t r = 0; r < nRows; ++r)
								visitMap.back()[r].resize(nCols, false);
						}

						if (!visitMap[lvl+1][otherSide.first][otherSide.second])
						{
							q.push(PathInfo(otherSide, lvl+1, pi.length+1));
							continue;
						}
					}
				}
			}

			// otherwise
			if (c > 0 && !visitMap[lvl][r][c-1] && map[r][c-1] == '.')
				q.push(PathInfo(std::make_pair(r, c-1), lvl, pi.length+1));
			if (c < nCols-1 && !visitMap[lvl][r][c+1] && map[r][c+1] == '.')
				q.push(PathInfo(std::make_pair(r, c+1), lvl, pi.length+1));
			if (r > 0 && !visitMap[lvl][r-1][c] && map[r-1][c] == '.')
				q.push(PathInfo(std::make_pair(r-1, c), lvl, pi.length+1));
			if (r < nRows-1 && !visitMap[lvl][r+1][c] && map[r+1][c] == '.')
				q.push(PathInfo(std::make_pair(r+1, c), lvl, pi.length+1));
		}
	}


	writeSolution(sola, solb);
}


