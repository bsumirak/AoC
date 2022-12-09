/*
 * day09.h
 *
 *  Created on: 2022-12-09
 *      Author: mbreit
 */


template <>
void executeDay<9>(const std::string& fn)
{
	// part a
	std::size_t resA;
	{
		std::set<std::array<int,2>> track;
		std::array<int, 2> state = {0, 0};
		std::array<int, 2> pos = {0, 0};
		track.insert(pos);

		const auto update = [&]()
		{
			if (abs(state[0]) == 2)
			{
				state[0] /= 2;
				pos[0] -= state[0];
				pos[1] -= state[1];
				state[1] = 0;
			}
			else if (abs(state[1]) == 2)
			{
				state[1] /= 2;
				pos[1] -= state[1];
				pos[0] -= state[0];
				state[0] = 0;
			}
			track.insert(pos);
		};

		std::ifstream infile(fn.c_str());
		char c;
		while (infile >> c)
		{
			unsigned n;
			infile >> n;
			switch (c)
			{
				case 'L':
					for (unsigned i = 0; i < n; ++i)
					{
						++state[0];
						update();
					}
					break;
				case 'R':
					for (unsigned i = 0; i < n; ++i)
					{
						--state[0];
						update();
					}
					break;
				case 'D':
					for (unsigned i = 0; i < n; ++i)
					{
						++state[1];
						update();
					}
					break;
				case 'U':
					for (unsigned i = 0; i < n; ++i)
					{
						--state[1];
						update();
					}
					break;
				default:
					std::cout << "whut!?" << std::endl;
			}
		}
		infile.close();

		resA = track.size();
	}



	// part a
	std::size_t resB;
	{
		std::set<std::array<int,2>> track;
		std::array<std::array<int, 2>, 9> state;
		std::fill(state.begin(), state.end(), std::array<int, 2>{0, 0});
		std::array<std::array<int, 2>, 9> pos;
		std::fill(pos.begin(), pos.end(), std::array<int, 2>{0, 0});
		track.insert(pos[8]);

		const auto update = [&]()
		{
			for (unsigned s = 0; s < 9u; ++s)
			{
				if (abs(state[s][0]) == 2 || abs(state[s][1]) == 2)
				{
					if (state[s][0] < 0)
					{
						++pos[s][0];
						++state[s][0];
						if (s < 8u)
							--state[s+1][0];
					}
					else if (state[s][0] > 0)
					{
						--pos[s][0];
						--state[s][0];
						if (s < 8u)
							++state[s+1][0];
					}

					if (state[s][1] < 0)
					{
						++pos[s][1];
						++state[s][1];
						if (s < 8u)
							--state[s+1][1];
					}
					else if (state[s][1] > 0)
					{
						--pos[s][1];
						--state[s][1];
						if (s < 8u)
							++state[s+1][1];
					}
				}
			}
			track.insert(pos[8]);
		};

		std::ifstream infile(fn.c_str());
		char c;
		while (infile >> c)
		{
			unsigned n;
			infile >> n;
			switch (c)
			{
				case 'L':
					for (unsigned i = 0; i < n; ++i)
					{
						++state[0][0];
						update();
					}
					break;
				case 'R':
					for (unsigned i = 0; i < n; ++i)
					{
						--state[0][0];
						update();
					}
					break;
				case 'D':
					for (unsigned i = 0; i < n; ++i)
					{
						++state[0][1];
						update();
					}
					break;
				case 'U':
					for (unsigned i = 0; i < n; ++i)
					{
						--state[0][1];
						update();
					}
					break;
				default:
					std::cout << "whut!?" << std::endl;
			}
		}
		infile.close();

		resB = track.size();
	}


	writeSolution(resA, resB);
}


