/*
 * day20.h
 *
 *  Created on: 2020-12-20
 *      Author: mbreit
 */


template <>
void executeDay<20>(const std::string& fn)
{
	// read input
	struct Node
	{
		unsigned id;
		std::array<char, 100> image;
		unsigned offset;
		bool flipped;
		std::array<unsigned, 4> neighbors;
		std::array<unsigned, 4> borders;
	};
	std::vector<Node> nodes(144);
	{
		std::ifstream infile(fn.c_str());
		std::string line;

		for (size_t i = 0; i < 144; ++i)
		{
			std::getline(infile, line);
			std::istringstream iss(line);
			std::string dummy;
			iss >> dummy;
			iss >> nodes[i].id;

			for (size_t j = 0; j < 10; ++j)
			{
				std::getline(infile, line);
				for (size_t k = 0; k < 10; ++k)
				{
					nodes[i].image[10*j + k] = line[k];
				}
			}

			memset(nodes[i].borders.data(), 0, 4*sizeof(unsigned));
			for (size_t k = 0; k < 10; ++k)
			{
				if (nodes[i].image[k] == '#')
					nodes[i].borders[1] += 1 << k;
				if (nodes[i].image[99-k] == '#')
					nodes[i].borders[3] += 1 << k;
				if (nodes[i].image[10*(9-k)] == '#')
					nodes[i].borders[2] += 1 << k;
				if (nodes[i].image[10*k + 9] == '#')
					nodes[i].borders[0] += 1 << k;
			}
			nodes[i].offset = 0;
			nodes[i].flipped = false;

			std::getline(infile, line);
		}
		infile.close();
	}


	auto invert = [] (unsigned i)
	{
		unsigned j = (i % 2);
		for (size_t k = 0; k < 9; ++k)
		{
			j = j << 1;
			i = i >> 1;
			j += (i % 2);
		}
		return j;
	};


	auto matchUp = [&] (unsigned i, unsigned j) -> unsigned
	{
		for (unsigned oi = 0; oi < 4u; ++oi)
		{
			unsigned bi = nodes[i].borders[oi];

			for (size_t oj = 0; oj < 4; ++oj)
			{
				unsigned bj = nodes[j].borders[oj];

				if (bi == bj)
				{
					nodes[j].flipped = !nodes[i].flipped;
					return 5u*(oi + 1u) + oj + 1u;
				}
				if (bi == invert(bj))
				{
					nodes[j].flipped = nodes[i].flipped;
					return 5u*(oi + 1u) + oj + 1u;
				}
			}
		}
		return 0u;
	};


	// part a
	std::size_t resA = 1;
	unsigned topLeft(-1);
	for (size_t i = 0; i < 144; ++i)
	{
		std::array<unsigned, 2> ress;
		unsigned cnt = 0;
		for (size_t j = 0; j < 144; ++j)
		{
			if (i == j)
				continue;

			unsigned res;
			if ((res = matchUp(i, j)))
			{
				++cnt;
				if (cnt > 2)
					break;
				ress[cnt-1] = res;
			}
		}
		if (cnt == 2)
		{
			resA *=	nodes[i].id;
			if ((ress[0] / 5u == 1 && ress[1] / 5u == 2)
				|| (ress[0] / 5u == 2 && ress[1] / 5u == 1))
			{
				topLeft = i;
			}
		}
	}


	// part b
	// stitch together the image
	std::vector<bool> processed(144, false);
	std::array<unsigned, 144> order;
	order[0] = topLeft;
	processed[topLeft] = true;
	nodes[topLeft].flipped = true;
	bool foundRight = false;
	unsigned cur = 0;
	do
	{
		++cur;
		foundRight = false;
		auto& lastNode = nodes[order[cur-1]];
		for (unsigned i = 0; i < 144; ++i)
		{
			if (processed[i])
				continue;

			nodes[i].flipped = false;

			unsigned res;
			if ((res = matchUp(order[cur-1], i))
				&& res / 5u - 1u == (4u - lastNode.offset) % 4u)
			{
				order[cur] = i;
				nodes[i].offset = (6u - (res % 5u - 1u)) % 4u;
				processed[i] = true;
				foundRight = true;
				break;
			}
		}
	}
	while (foundRight);


	size_t nCols = cur;
	size_t nRows = 144 / nCols;
	for (size_t r = 1; r < nRows; ++r)
	{
		for (size_t c = 0; c < nCols; ++c)
		{
			auto& lastNode = nodes[order[cur-nCols]];
			for (size_t i = 0; i < 144; ++i)
			{
				if (processed[i])
					continue;

				nodes[i].flipped = false;

				unsigned res;
				if ((res = matchUp(order[cur-nCols], i))
					&& res / 5u - 1u == (lastNode.flipped ? (5u - lastNode.offset) % 4u : (3u - lastNode.offset) % 4u))
				{
					order[cur] = i;
					nodes[i].offset = nodes[i].flipped ? (3u - (res % 5u - 1u)) % 4u : (5u - (res % 5u - 1u)) % 4u;
					processed[i] = true;
					break;
				}
			}
			++cur;
		}
	}

	// remove the borders
	std::array<char, 96*96> image;
	for (unsigned r = 0; r < nRows; ++r)
	{
		for (unsigned c = 0; c < nCols; ++c)
		{
			const auto& node = nodes[order[nCols*r + c]];
			for (unsigned i = 0; i < 8; ++i)
			{
				for (unsigned j = 0; j < 8; ++j)
				{
					unsigned realI = i+1u;
					unsigned realJ = j+1u;

					if (node.flipped)
						realI = 9u - realI;

					switch (node.offset)
					{
						case 0:
							break;
						case 1:
						{
							unsigned tmp = realJ;
							realJ = 9u - realI;
							realI = tmp;
						} break;
						case 2:
						{
							realI = 9u - realI;
							realJ = 9u - realJ;
						} break;
						case 3:
						{
							unsigned tmp = realI;
							realI = 9u - realJ;
							realJ = tmp;
						} break;
					}

					image[(8*r+i)*96 + 8*c + j] = node.image[10*realI + realJ];
				}
			}
		}
	}


	// find the monsters
	unsigned monsterCnt = 0;
	for (int k = 0; k < 2; ++k)
	{
		unsigned rotateCnt = 0;
		do
		{
			for (unsigned i = 1; i < 95; ++i)
			{
				for (unsigned j = 0; j < 77; ++j)
				{
					if (image[96*i+j] != '.'
						&& image[96*(i+1)+(j+1)] != '.'
						&& image[96*(i+1)+(j+4)] != '.'
						&& image[96*(i)+(j+5)] != '.'
						&& image[96*(i)+(j+6)] != '.'
						&& image[96*(i+1)+(j+7)] != '.'
						&& image[96*(i+1)+(j+10)] != '.'
						&& image[96*(i)+(j+11)] != '.'
						&& image[96*(i)+(j+12)] != '.'
						&& image[96*(i+1)+(j+13)] != '.'
						&& image[96*(i+1)+(j+16)] != '.'
						&& image[96*(i)+(j+17)] != '.'
						&& image[96*(i-1)+(j+18)] != '.'
						&& image[96*(i)+(j+18)] != '.'
						&& image[96*(i)+(j+19)] != '.')
					{
						image[96*i+j] = 'O';
						image[96*(i+1)+(j+1)] = 'O';
						image[96*(i+1)+(j+4)] = 'O';
						image[96*(i)+(j+5)] = 'O';
						image[96*(i)+(j+6)] = 'O';
						image[96*(i+1)+(j+7)] = 'O';
						image[96*(i+1)+(j+10)] = 'O';
						image[96*(i)+(j+11)] = 'O';
						image[96*(i)+(j+12)] = 'O';
						image[96*(i+1)+(j+13)] = 'O';
						image[96*(i+1)+(j+16)] = 'O';
						image[96*(i)+(j+17)] = 'O';
						image[96*(i-1)+(j+18)] = 'O';
						image[96*(i)+(j+18)] = 'O';
						image[96*(i)+(j+19)] = 'O';
						++monsterCnt;
					}
				}
			}

			// rotate image
			for (unsigned i = 0; i < 48; ++i)
			{
				for (unsigned j = 0; j < 48; ++j)
				{
					char tmp = image[96*i+j];
					image[96*i+j] = image[96*j+(95-i)];
					image[96*j+(95-i)] = image[96*(95-i) + (95-j)];
					image[96*(95-i) + (95-j)] = image[96*(95-j) + i];
					image[96*(95-j) + i] = tmp;
				}
			}
			++rotateCnt;
		}
		while (!monsterCnt && rotateCnt < 4);

		if (monsterCnt)
			break;

		// flip the image
		for (unsigned i = 0; i < 48; ++i)
			for (unsigned j = 0; j < 96; ++j)
				std::swap(image[96*i+j], image[96 * (95-i) + j]);
	}

	// count non-monster #
	unsigned resB = 0;
	for (unsigned i = 0; i < 96; ++i)
	{
		for (unsigned j = 0; j < 96; ++j)
		{
			if (image[96*i+j] == '#')
				++resB;
		}
	}


	writeSolution(resA, resB);
}


