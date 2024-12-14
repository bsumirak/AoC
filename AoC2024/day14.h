/*
 * day14.h
 *
 *  Created on: 2024-12-14
 *      Author: mbreit
 */


template <>
void executeDay<14>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	
	struct Robot
	{
		std::array<int, 2> p{0, 0};
		std::array<int, 2> v{0, 0};
	};

	std::vector<Robot> rob;
	Robot rr;
	while (infile >> rr.p[0])
	{
		infile >> rr.p[1];
		infile >> rr.v[0];
		infile >> rr.v[1];
		rob.push_back(rr);
	}


	// part a
	std::array<unsigned, 4> quadrants{0u, 0u, 0u, 0u};
	for (const auto& r : rob)
	{
		const auto x = (r.p[0] + 100 * r.v[0] + 101 * std::abs(r.v[0])) % 101;
		const auto y = (r.p[1] + 100 * r.v[1] + 103 * std::abs(r.v[1])) % 103;

		if (x == 50 || y == 51)
			continue;

		unsigned q = 0u;
		if (x < 50)
			q += 1u;
		if (y < 51)
			q += 2u;
		++quadrants[q];
	}

	auto resA = quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3];


	// part b
	unsigned resB = 0;
	std::vector<std::string> room(103, std::string(101, ' '));
	for (unsigned k = 0u; k < 101u * 103u; ++k)
	{
		for (auto& line : room)
			line = std::string(101, ' ');

		for (auto& r : rob)
		{
			auto x = (r.p[0] + k * r.v[0] + k * 101 * std::abs(r.v[0])) % 101;
			auto y = (r.p[1] + k * r.v[1] + k * 103 * std::abs(r.v[1])) % 103;

			room[y][x] = 'o';
			if (x >= 2 && y >= 2 && x < 99 && y < 101
				&& room[y-1][x-1] == 'o' && room[y-1][x] == 'o' && room[y-1][x+1] == 'o'
				&& room[y][x-1] == 'o' && room[y][x+1] == 'o'
				&& room[y+1][x-1] == 'o' && room[y+1][x] == 'o' && room[y+1][x+1] == 'o')
			{
				resB = k;
			}
		}

		if (resB > 0u)
		{
			for (size_t l = 47; l < 80; ++l)
			{
				for (size_t m = 40; m < 71; ++m)
					std::cout << room[l][m];
				std::cout << std::endl;
			}
			break;
		}
	}


	writeSolution(resA, resB);
}

