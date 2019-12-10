/*
 * day10.h
 *
 *  Created on: 2019-12-10
 *      Author: mbreit
 */



template <>
void executeDay<10>(const std::string& fn)
{
	std::vector<std::vector<int> > map;

	// read input
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		while (std::getline(infile, line))
		{
			map.resize(map.size() + 1);
			std::istringstream iss(line);

			char token;
			while (iss >> token)
			{
				if (token == '#')
					map.back().push_back(1);
				else
					map.back().push_back(0);
			}
		}
	}
	const std::size_t nRows = map.size();
	const std::size_t nCols = map.back().size();

	// part a
	int max = -1;
	std::pair<std::size_t, std::size_t> maxCoords(0, 0);
	for (std::size_t r = 0; r < nRows; ++r)
	{
		for (std::size_t c = 0; c < nCols; ++c)
		{
			if (!map[r][c])
				continue;

			int cnt = 0;
			for (std::size_t r1 = 0; r1 < nRows; ++r1)
			{
				for (std::size_t c1 = 0; c1 < nCols; ++c1)
				{
					if (!map[r1][c1])
						continue;

					if (r1 == r && c1 == c)
						continue;

					int dx = abs((int) c1 - (int) c);
					int dy = abs((int) r1 - (int) r);

					int stepX = dx;
					int stepY = dy;
					if (dx && dy)
					{
						while (dx != dy)
						{
							if (dx > dy)
								dx -= dy;
							else
								dy -= dx;
						}
						stepX = ((int) c1 - (int) c) / dx;
						stepY = ((int) r1 - (int) r) / dy;
					}
					else
					{
						if (dx == 0)
						{
							dx = dy;
							stepY = r1 > r ? 1 : -1;
						}
						else
							stepX = c1 > c ? 1 : -1;
					}

					bool shadowed = false;
					for (int i = 1; i < dx; ++i)
					{
						if (map[r+i*stepY][c+i*stepX])
						{
							shadowed = true;
							break;
						}
					}
					if (!shadowed)
						++cnt;
				}
			}

			if (cnt > max)
			{
				max = cnt;
				maxCoords = std::make_pair(c, r);
			}
		}
	}
	int sola = max;


	// part b
	struct asteroid
	{
		int x;
		int y;
		int shadowedBy;
		float angle;

		bool operator< (const asteroid& a) const
		{
			if (shadowedBy < a.shadowedBy)
				return true;
			if (shadowedBy > a.shadowedBy)
				return false;

			return (angle < a.angle);
		}
	};

	// collect asteroid objects
	std::vector<asteroid> vAst;
	const std::size_t r = maxCoords.second;
	const std::size_t c = maxCoords.first;
	for (std::size_t r1 = 0; r1 < nRows; ++r1)
	{
		for (std::size_t c1 = 0; c1 < nCols; ++c1)
		{
			if (!map[r1][c1])
				continue;

			if (r1 == r && c1 == c)
				continue;

			// count shadowing objects
			int dx = abs((int) c1 - (int) c);
			int dy = abs((int) r1 - (int) r);

			int stepX = dx;
			int stepY = dy;
			if (dx && dy)
			{
				while (dx != dy)
				{
					if (dx > dy)
						dx -= dy;
					else
						dy -= dx;
				}
				stepX = ((int) c1 - (int) c) / dx;
				stepY = ((int) r1 - (int) r) / dy;
			}
			else
			{
				if (dx == 0)
				{
					dx = dy;
					stepY = r1 > r ? 1 : -1;
				}
				else
					stepX = c1 > c ? 1 : -1;
			}

			for (int i = 1; i < dx; ++i)
				if (map[r+i*stepY][c+i*stepX])
					++map[r1][c1];

			// calculate angle
			float angle;
			if (r1 == r)
				angle = c1 > c ? 0.5*M_PI : 1.5*M_PI;
			else
			{
				angle = -atan(((float)c1-(float)c)/((float)r1-(float)r));
				if (r1 > r)
					angle += M_PI;
				if (angle < 0)
					angle += 2*M_PI;
			}

			// push back asteroid object
			asteroid a = {int(c1-c), int(r1-r), map[r1][c1] - 1, angle};
			vAst.push_back(a);
		}
	}

	std::sort(vAst.begin(), vAst.end());
	int solb = 100*(vAst[199].x + c) + vAst[199].y + r;


	writeSolution(sola, solb);
}


