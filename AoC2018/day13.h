/*
 * day13.h
 *
 *  Created on: 2018-12-13
 *      Author: mbreit
 */

struct CartCmp
{
	CartCmp(const std::vector<std::pair<size_t, size_t> >& _cartPos)
		: cartPos(_cartPos) {}

	bool operator()(const size_t& a, const size_t& b) const
	{
		return cartPos[a] < cartPos[b];
	}

	private:
		const std::vector<std::pair<size_t, size_t> >& cartPos;
};


template <>
void executeDay<13>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::vector<std::string> path;

	// read labyrinth
	std::string line;
	while (std::getline(infile, line))
		path.push_back(line);

	std::vector<std::pair<size_t, size_t> > cartPos;
	std::vector<int> cartFacing;

	const size_t height = path.size();
	const size_t width = path[0].size();
	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			if (path[y][x] == '>')
			{
				cartPos.push_back(std::make_pair(y, x));
				cartFacing.push_back(0);
				path[y][x] = '-';
			}
			else if (path[y][x] == '^')
			{
				cartPos.push_back(std::make_pair(y, x));
				cartFacing.push_back(1);
				path[y][x] = '|';
			}
			else if (path[y][x] == '<')
			{
				cartPos.push_back(std::make_pair(y, x));
				cartFacing.push_back(2);
				path[y][x] = '-';
			}
			else if (path[y][x] == 'v')
			{
				cartPos.push_back(std::make_pair(y, x));
				cartFacing.push_back(3);
				path[y][x] = '|';
			}
		}
	}
	const size_t nCarts = cartPos.size();
	std::vector<int> nextTurn(nCarts, 1);

	std::vector<size_t> cartOrder(nCarts);
	for (size_t i = 0; i < nCarts; ++i)
		cartOrder[i] = i;

	std::vector<bool> crashed(nCarts, false);
	size_t nCrashed = 0;

	std::pair<size_t, size_t> solA;
	int tick = 0;
	while (nCrashed < nCarts - 1)
	{
		++tick;
		std::sort(cartOrder.begin(), cartOrder.end(), CartCmp(cartPos));

//std::cout << std::endl;

		for (size_t i = 0; i < nCarts; ++i)
		{
			const size_t c = cartOrder[i];

			// crashed carts cannot move
			if (crashed[c])
				continue;

			size_t& y = cartPos[c].first;
			size_t& x = cartPos[c].second;

			// advance cart
			switch (cartFacing[c])
			{
				case 0:
					++x;
					break;
				case 1:
					--y;
					break;
				case 2:
					--x;
					break;
				case 3:
					++y;
					break;
				default:
				{
					std::cout << "Invalid direction " << cartFacing[c] << "!" << std::endl;
					exit(0);
				}
			}
//std::cout << "Cart " << c << " at (x,y) = (" << x << "," << y << ")" << std::endl;

			// update direction
			switch (path[y][x])
			{
				case '-':
				case '|':
					break;
				case '+':
					cartFacing[c] = (cartFacing[c] + nextTurn[c] + 4) % 4;
					nextTurn[c] = ((nextTurn[c] + 3) % 3) - 1;
					break;
				case '/':
					if (cartFacing[c] == 0)
						cartFacing[c] = 1;
					else if (cartFacing[c] == 1)
						cartFacing[c] = 0;
					else if (cartFacing[c] == 2)
						cartFacing[c] = 3;
					else if (cartFacing[c] == 3)
						cartFacing[c] = 2;
					break;
				case '\\':
					if (cartFacing[c] == 0)
						cartFacing[c] = 3;
					else if (cartFacing[c] == 1)
						cartFacing[c] = 2;
					else if (cartFacing[c] == 2)
						cartFacing[c] = 1;
					else if (cartFacing[c] == 3)
						cartFacing[c] = 0;
					break;
				default:
				{
					std::cout << "Invalid track tile " << path[y][x]
						<< "for cart " << c << " at " << "(x,y) = (" << x << "," << y << ")!" << std::endl;
					exit(0);
				}
			}

			// check for collision
			for (size_t c1 = 0; c1 < nCarts; ++c1)
			{
				if (c1 == c)
					continue;

				if (cartPos[c1].first == y && cartPos[c1].second == x && !crashed[c1])
				{
					if (!nCrashed)
					{
						solA.first = x;
						solA.second = y;
					}

std::cout << "CRASH!   cart " << c << " into cart " << c1 << " on tick "
	<< tick << std::endl;

					crashed[c] = true;
					crashed[c1] = true;
					nCrashed += 2;
				}
			}
		}
	}

	std::ostringstream ossa;
	ossa << solA.first << "," << solA.second;

	size_t c = 0;
	for (; c < nCarts; ++c)
		if (!crashed[c])
			break;
	std::ostringstream ossb;
	ossb << cartPos[c].second << "," << cartPos[c].first;


	writeSolution(ossa.str(), ossb.str());
}


