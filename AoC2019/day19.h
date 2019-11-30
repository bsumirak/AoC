/*
 * day19.h
 *
 *  Created on: 19.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<19>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::vector<std::string> path;
	std::map<std::pair<size_t, size_t>, char> tokens;

	// read labyrinth
	std::string line;
	while (std::getline(infile, line))
		path.push_back(line);


	// step through
	std::string sola = "";
	size_t nStep = 1;

	// find entrance
	size_t i = 0;
	size_t j = 0;
	for (; j < path[i].size(); ++j)
		if (path[i][j] == '|')
			break;

	int comingFrom = 1;
	while (true)
	{
		while (path[i][j] != '+')
		{
			if (path[i][j] == ' ')
			{
				//std::cout << "Path ended in space." << std::endl;
				--nStep;
				goto exitLabyrinth;
			}

			if (path[i][j] != '|' && path[i][j] != '-')
				sola += path[i][j];

			switch (comingFrom)
			{
				case 1: ++i; break;
				case 2: --j; break;
				case 3: --i; break;
				case 4: ++j;
			}

			++nStep;

			if (i == (size_t)-1 || i >= path.size() || j == (size_t)-1 || j >= path[i].size())
			{
				//std::cout << "Path ended in boundary." << std::endl;
				goto exitLabyrinth;
			}
		}

		// we hit a '+' - find possible directions to continue
		size_t it = i;
		size_t jt = j;
		if (comingFrom == 1 || comingFrom == 3)
		{
			while (jt < path[it].size() - 1 && path[i][++jt] == '|')
				;
			if (path[i][jt] != ' ' && path[i][jt] != '|')
			{
				nStep += jt-j;
				j = jt;
				comingFrom = 4;
			}
			else
			{
				jt = j;
				while (jt != 0 && path[i][--jt] == '|')
					;
				if (path[i][jt] != ' ' && path[i][jt] != '|')
				{
					nStep += j-jt;
					j = jt;
					comingFrom = 2;
				}
				else
				{
					//std::cout << "Path ended in +, coming from " << comingFrom << "." << std::endl;
					goto exitLabyrinth;
				}
			}
		}
		else
		{
			while (it < path.size() - 1 && path[++it][j] == '-')
				;
			if (path[it][j] != ' ' && path[it][jt] != '-')
			{
				nStep += it-i;
				i = it;
				comingFrom = 1;
			}
			else
			{
				it = i;
				while (it != 0 && path[--it][jt] == '-')
					;
				if (path[it][jt] != ' ' && path[it][jt] != '-')
				{
					nStep += i-it;
					i = it;
					comingFrom = 3;
				}
				else
				{
					//std::cout << "Path ended in +, coming from " << comingFrom << "." << std::endl;
					goto exitLabyrinth;
				}
			}
		}
	}

exitLabyrinth:

	writeSolution(sola, nStep);
}


