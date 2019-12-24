/*
 * day24.h
 *
 *  Created on: 2019-12-24
 *      Author: mbreit
 */


template <>
void executeDay<24>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	uint sola = 0;
	{
		std::vector<std::string> map = {{".###.", "..#.#", "...##", "#.###", "..#.."}};
		std::vector<std::string> next(map);

		std::size_t nIt = 10000;
		std::vector<uint> ratings;
		for (std::size_t i = 0; i < nIt; ++i)
		{
			uint rating = 0;
			uint fac = 1;
			for (size_t r1 = 0; r1 < 5; ++r1)
			{
				for (size_t c1 = 0; c1 < 5; ++c1)
				{
					if (map[r1][c1] == '#')
						rating += fac;
					fac = fac << 1;
				}
			}

			bool doBreak = false;
			for (std::size_t j = 0; j < ratings.size(); ++j)
			{
				if (ratings[j] == rating)
				{
					doBreak = true;
					break;
				}
			}

			if (doBreak)
			{
				sola = rating;
				break;
			}

			ratings.push_back(rating);

			for (size_t r = 0; r < 5; ++r)
			{
				for (size_t c = 0; c < 5; ++c)
				{
					int cnt = 0;
					if (r > 0 && map[r-1][c] == '#')
						++cnt;
					if (r < 4 && map[r+1][c] == '#')
						++cnt;
					if (c > 0 && map[r][c-1] == '#')
						++cnt;
					if (c < 4 && map[r][c+1] == '#')
						++cnt;

					if (map[r][c] == '#')
					{
						if (cnt != 1)
							next[r][c] = '.';
						else
							next[r][c] = '#';
					}
					else
					{
						if (cnt == 1 || cnt == 2)
							next[r][c] = '#';
						else
							next[r][c] = '.';
					}
				}
			}

			map.swap(next);
		}
	}

	uint solb = 0;
	{
		std::vector<std::string> map = {{".###.", "..#.#", "...##", "#.###", "..#.."}};
		std::vector<std::vector<std::string> > levelMap(201);
		for (std::size_t l = 0; l < 201; ++l)
			levelMap[l] = std::vector<std::string>(5, ".....");
		levelMap[100] = map;
		std::vector<std::vector<std::string> > next(levelMap);

		std::size_t nIt = 200;
		for (std::size_t i = 0; i < nIt; ++i)
		{
			for (size_t l = 100-(i+2)/2; l < 101+(i+2)/2; ++l)
			{
				for (size_t r = 0; r < 5; ++r)
				{
					for (size_t c = 0; c < 5; ++c)
					{
						if (r == 2 && c == 2)
							continue;

						int cnt = 0;

						if (l > 0 && r == 0 && levelMap[l-1][1][2] == '#')
							++cnt;
						if (r > 0 && levelMap[l][r-1][c] == '#')
							++cnt;
						if (r == 3 && c == 2 && l < 200)
						{
							for (size_t j = 0; j < 5; ++j)
								if (levelMap[l+1][4][j] == '#')
									++cnt;
						}

						if (l > 0 && r == 4 && levelMap[l-1][3][2] == '#')
							++cnt;
						if (r < 4 && levelMap[l][r+1][c] == '#')
							++cnt;
						if (r == 1 && c == 2 && l < 200)
						{
							for (size_t j = 0; j < 5; ++j)
								if (levelMap[l+1][0][j] == '#')
									++cnt;
						}

						if (l > 0 && c == 0 && levelMap[l-1][2][1] == '#')
							++cnt;
						if (c > 0 && levelMap[l][r][c-1] == '#')
							++cnt;
						if (c == 3 && r == 2 && l < 200)
						{
							for (size_t j = 0; j < 5; ++j)
								if (levelMap[l+1][j][4] == '#')
									++cnt;
						}

						if (l > 0 && c == 4 && levelMap[l-1][2][3] == '#')
							++cnt;
						if (c < 4 && levelMap[l][r][c+1] == '#')
							++cnt;
						if (c == 1 && r == 2 && l < 200)
						{
							for (size_t j = 0; j < 5; ++j)
								if (levelMap[l+1][j][0] == '#')
									++cnt;
						}


						if (levelMap[l][r][c] == '#')
						{
							if (cnt != 1)
								next[l][r][c] = '.';
							else
								next[l][r][c] = '#';
						}
						else
						{
							if (cnt == 1 || cnt == 2)
								next[l][r][c] = '#';
							else
								next[l][r][c] = '.';
						}
					}
				}
			}

			levelMap.swap(next);
		}

		solb = 0;
		for (size_t l = 0; l < 201; ++l)
			for (size_t r = 0; r < 5; ++r)
				for (size_t c = 0; c < 5; ++c)
					if (levelMap[l][r][c] == '#')
						++solb;
	}

	writeSolution(sola, solb);
}


