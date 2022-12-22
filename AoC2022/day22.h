/*
 * day22.h
 *
 *  Created on: 2022-12-22
 *      Author: mbreit
 */


template <>
void executeDay<22>(const std::string& fn)
{
	// read input
	std::vector<std::string> map(200);
	std::string mv;
	{
		std::ifstream infile(fn.c_str());
		for (size_t k = 0; k < 200; ++k)
			std::getline(infile, map[k]);

		std::getline(infile, mv);
		std::getline(infile, mv);

		infile.close();
	}

	// part a
	unsigned posx = std::distance(map[0].begin(), std::find(map[0].begin(), map[0].end(), '.'));
	unsigned posy = 0;

	unsigned head = 0;

	char* ptr = &mv[0];
	while (ptr < &mv[0] + mv.size())
	{
		const unsigned fwd = std::strtoul(ptr, &ptr, 10);
/*
		std::cout << "posx: " << posx << " posy: " << posy << " head: " << head << " fwd: " << fwd << std::endl;
		std::cout << map[(posy + map.size() - 1) % map.size()] << std::endl;
		std::string s = map[(posy + map.size()) % map.size()];
		s[posx] = '*';
		std::cout << s << std::endl;
		std::cout << map[(posy + map.size() + 1) % map.size()] << std::endl;
*/
		for (unsigned k = 0; k < fwd; ++k)
		{
			if (head == 0)
			{
				if (posx + 1 == map[posy].size() || map[posy][posx + 1] == ' ')
				{
					const auto it = std::find_if(map[posy].begin(), map[posy].end(), [](char c){return c != ' ';});
					if (*it == '#')
						break;
					posx = std::distance(map[posy].begin(), it);
				}
				else if (map[posy][posx + 1] == '#')
					break;
				else
					++posx;
			}
			else if (head == 2)
			{
				if (posx == 0 || map[posy][posx - 1] == ' ')
				{
					if (map[posy][map[posy].size() - 1] == '#')
						break;
					posx = map[posy].size() - 1;
				}
				else if (map[posy][posx - 1] == '#')
					break;
				else
					--posx;
			}
			else if (head == 1)
			{
				if (posy + 1 == map.size() || posx >= map[posy + 1].size() || map[posy + 1][posx] == ' ')
				{
					unsigned i = 0;
					for (; i <= posy; ++i)
						if (map[i].size() > posx && map[i][posx] != ' ')
							break;
					if (map[i][posx] == '#')
						break;
					posy = i;
				}
				else if (map[posy + 1][posx] == '#')
					break;
				else
					++posy;
			}
			else if (head == 3)
			{
				if (posy == 0 || posx >= map[posy - 1].size() || map[posy - 1][posx] == ' ')
				{
					unsigned i = map.size() - 1;
					for (; i >= posy; --i)
						if (map[i].size() > posx && map[i][posx] != ' ')
							break;
					if (map[i][posx] == '#')
						break;
					posy = i;
				}
				else if (map[posy - 1][posx] == '#')
					break;
				else
					--posy;
			}
		}

		if (ptr >= mv.data() + mv.size())
			break;

		const char turn = *ptr++;
		if (turn == 'L')
			head = (head + 3) % 4;
		else
			head = (head + 1) % 4;
	}

	unsigned resA = 1000 * (posy + 1) + 4 * (posx + 1) + head;


	// part b
	posx = std::distance(map[0].begin(), std::find(map[0].begin(), map[0].end(), '.'));
	posy = 0;
	head = 0;

	ptr = &mv[0];
	while (ptr < &mv[0] + mv.size())
	{
		const unsigned fwd = std::strtoul(ptr, &ptr, 10);

		for (unsigned k = 0; k < fwd; ++k)
		{
			if (head == 0)
			{
				if (posx + 1 == map[posy].size() || map[posy][posx + 1] == ' ')
				{
					if (posy < 50)
					{
						unsigned cx = 99;
						unsigned cy = 149 - posy;
						if (map[cy][cx] == '#')
							break;
						posx = cx;
						posy = cy;
						head = 2;
					}
					else if (posy < 100)
					{
						unsigned cx = 50 + posy;
						unsigned cy = 49;
						if (map[cy][cx] == '#')
							break;
						posx = cx;
						posy = cy;
						head = 3;
					}
					else if (posy < 150)
					{
						unsigned cx = 149;
						unsigned cy = 149 - posy;
						if (map[cy][cx] == '#')
							break;
						posx = cx;
						posy = cy;
						head = 2;
					}
					else
					{
						unsigned cx = posy - 100;
						unsigned cy = 149;
						if (map[cy][cx] == '#')
							break;
						posx = cx;
						posy = cy;
						head = 3;
					}
				}
				else if (map[posy][posx + 1] == '#')
					break;
				else
					++posx;
			}
			else if (head == 2)
			{
				if (posx == 0 || map[posy][posx - 1] == ' ')
				{
					if (posy < 50)
					{
						unsigned cx = 0;
						unsigned cy = 149 - posy;
						if (map[cy][cx] == '#')
							break;
						posx = cx;
						posy = cy;
						head = 0;
					}
					else if (posy < 100)
					{
						unsigned cx = posy - 50;
						unsigned cy = 100;
						if (map[cy][cx] == '#')
							break;
						posx = cx;
						posy = cy;
						head = 1;
					}
					else if (posy < 150)
					{
						unsigned cx = 50;
						unsigned cy = 149 - posy;
						if (map[cy][cx] == '#')
							break;
						posx = cx;
						posy = cy;
						head = 0;
					}
					else
					{
						unsigned cx = posy - 100;
						unsigned cy = 0;
						if (map[cy][cx] == '#')
							break;
						posx = cx;
						posy = cy;
						head = 1;
					}
				}
				else if (map[posy][posx - 1] == '#')
					break;
				else
					--posx;
			}
			else if (head == 1)
			{
				if (posy + 1 == map.size() || posx >= map[posy + 1].size() || map[posy + 1][posx] == ' ')
				{
					if (posx < 50)
					{
						unsigned cx = posx + 100;
						unsigned cy = 0;
						if (map[cy][cx] == '#')
							break;
						posx = cx;
						posy = cy;
						head = 1;
					}
					else if (posx < 100)
					{
						unsigned cx = 49;
						unsigned cy = posx + 100;
						if (map[cy][cx] == '#')
							break;
						posx = cx;
						posy = cy;
						head = 2;
					}
					else
					{
						unsigned cx = 99;
						unsigned cy = posx - 50;
						if (map[cy][cx] == '#')
							break;
						posx = cx;
						posy = cy;
						head = 2;
					}
				}
				else if (map[posy + 1][posx] == '#')
					break;
				else
					++posy;
			}
			else if (head == 3)
			{
				if (posy == 0 || posx >= map[posy - 1].size() || map[posy - 1][posx] == ' ')
				{
					if (posx < 50)
					{
						unsigned cx = 50;
						unsigned cy = posx + 50;
						if (map[cy][cx] == '#')
							break;
						posx = cx;
						posy = cy;
						head = 0;
					}
					else if (posx < 100)
					{
						unsigned cx = 0;
						unsigned cy = posx + 100;
						if (map[cy][cx] == '#')
							break;
						posx = cx;
						posy = cy;
						head = 0;
					}
					else
					{
						unsigned cx = posx - 100;
						unsigned cy = 199;
						if (map[cy][cx] == '#')
							break;
						posx = cx;
						posy = cy;
						head = 3;
					}
				}
				else if (map[posy - 1][posx] == '#')
					break;
				else
					--posy;
			}
		}

		if (ptr >= mv.data() + mv.size())
			break;

		const char turn = *ptr++;
		if (turn == 'L')
			head = (head + 3) % 4;
		else
			head = (head + 1) % 4;
	}

	unsigned resB = 1000 * (posy + 1) + 4 * (posx + 1) + head;



	writeSolution(resA, resB);
}


