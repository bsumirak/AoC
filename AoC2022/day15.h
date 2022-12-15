/*
 * day15.h
 *
 *  Created on: 2022-12-15
 *      Author: mbreit
 */


template <>
void executeDay<15>(const std::string& fn)
{
	// read input
	struct Vec2
	{
		int x;
		int y;
	};

	std::array<Vec2, 33> sensors;
	std::array<Vec2, 33> beacons;

	{
		std::ifstream infile(fn.c_str());
		for (size_t k = 0; k < 33; ++k)
		{
			infile >> sensors[k].x;
			infile >> sensors[k].y;
			infile >> beacons[k].x;
			infile >> beacons[k].y;
		}
		infile.close();
	}


	// part a
	std::size_t resA = 0;
	{
		std::vector<bool> v(100000000, true);
		int y = 2000000;
		for (size_t k = 0; k < 33; ++k)
		{
			int dx = abs(sensors[k].x - beacons[k].x);
			int dy = abs(sensors[k].y - beacons[k].y);
			int d = dx + dy;
			int ds = abs(y - sensors[k].y);
			for (int l = 0; l <= d - ds; ++l)
			{
				v[sensors[k].x + 50000000 + l] = false;
				v[sensors[k].x + 50000000 - l] = false;
			}
			if (beacons[k].y == y)
				v[beacons[k].x + 50000000] = true;
		}
		for (auto p : v)
			resA += 1 - p;
	}

	// part b
	uint64_t resB = 0;
	{
		std::array<Vec2, 33> onLine;
		for (int y = 0; y < 4000000; ++y)
		{
			for (size_t k = 0; k < 33; ++k)
			{
				int d = abs(sensors[k].x - beacons[k].x) + abs(sensors[k].y - beacons[k].y);
				int delta = d - abs(y - sensors[k].y);
				onLine[k].x = sensors[k].x - delta;
				onLine[k].y = sensors[k].x + delta;
			}

			for (int x = 0; x < 4000000;)
			{
				auto it = std::find_if(onLine.begin(), onLine.end(),
					[&](const Vec2& v){return x >= v.x && x <= v.y;});
				if (it == onLine.end())
				{
					resB = uint64_t(4000000) * uint64_t(x) + uint64_t(y);
					break;
				}
				x = it->y + 1;
			}

			if (resB != 0)
				break;
		}
	}

	writeSolution(resA, resB);
}


