/*
 * day17.h
 *
 *  Created on: 2022-12-17
 *      Author: mbreit
 */


template <>
void executeDay<17>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::string jets;
	{
		infile >> jets;
		infile.close();
	}

	struct State
	{
		std::vector<char> sfc;
		unsigned pc = 0;
		unsigned it = 0;
		unsigned h = 0;

		bool operator<(const State& s) const
		{
			if (sfc < s.sfc)
				return true;
			if (s.sfc < sfc)
				return false;

			if (pc % 5 < s.pc % 5)
				return true;
			if (s.pc % 5 < pc % 5)
				return false;

			return it < s.it;
		}
	};

	const std::array<std::vector<std::array<int, 2>>, 5> pieces =
	{
		std::vector<std::array<int, 2>>{{0, 0}, {1, 0}, {2, 0}, {3, 0}},
		std::vector<std::array<int, 2>>{{0, 0}, {1, 0}, {2, 0}, {1, 1}, {1, -1}},
		std::vector<std::array<int, 2>>{{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}},
		std::vector<std::array<int, 2>>{{0, 0}, {0, 1}, {0, 2}, {0, 3}},
		std::vector<std::array<int, 2>>{{0, 0}, {1, 0}, {0, 1}, {1, 1}}
	};
	const std::array<std::vector<std::array<int, 2>>, 5> leftFront =
	{
		std::vector<std::array<int, 2>>{{0, 0}},
		std::vector<std::array<int, 2>>{{0, 0}, {1, 1}, {1, -1}},
		std::vector<std::array<int, 2>>{{0, 0}, {2, 1}, {2, 2}},
		std::vector<std::array<int, 2>>{{0, 0}, {0, 1}, {0, 2}, {0, 3}},
		std::vector<std::array<int, 2>>{{0, 0}, {0, 1}}
	};
	const std::array<std::vector<std::array<int, 2>>, 5> rightFront =
	{
		std::vector<std::array<int, 2>>{{3, 0}},
		std::vector<std::array<int, 2>>{{2, 0}, {1, 1}, {1, -1}},
		std::vector<std::array<int, 2>>{{2, 0}, {2, 1}, {2, 2}},
		std::vector<std::array<int, 2>>{{0, 0}, {0, 1}, {0, 2}, {0, 3}},
		std::vector<std::array<int, 2>>{{1, 0}, {1, 1}}
	};
	const std::array<std::vector<std::array<int, 2>>, 5> bottomFront =
	{
		std::vector<std::array<int, 2>>{{0, 0}, {1, 0}, {2, 0}, {3, 0}},
		std::vector<std::array<int, 2>>{{0, 0}, {1, -1}, {2, 0}},
		std::vector<std::array<int, 2>>{{0, 0}, {1, 0}, {2, 0}},
		std::vector<std::array<int, 2>>{{0, 0}},
		std::vector<std::array<int, 2>>{{0, 0}, {1, 0}}
	};
	std::array<unsigned, 7> maxElongRight = {3, 2, 2, 0, 1};
	std::array<unsigned, 7> maxElongDown = {0, 1, 0, 0, 0};
	std::array<unsigned, 7> maxElongUp = {0, 1, 2, 3, 1};
	std::array<unsigned, 7> elongUp0 = {0, 0, 0, 3, 1};

	std::bitset<100 * 7> space;

	const auto leftMvmtOk = [&](unsigned pc, unsigned px, unsigned py)
	{
		if (px == 0)
			return false;

		for (const auto& front : leftFront[pc])
			if (space[(py + front[1]) * 7u + px + front[0] - 1u])
				return false;

		return true;
	};

	const auto rightMvmtOk = [&](unsigned pc, unsigned px, unsigned py)
	{
		if (px >= 6u - maxElongRight[pc])
			return false;

		for (const auto& front : rightFront[pc])
			if (space[(py + front[1]) * 7u + px + front[0] + 1u])
				return false;

		return true;
	};

	const auto downMvmtOk = [&](unsigned pc, unsigned px, unsigned py)
	{
		if (py <= maxElongDown[pc])
			return false;

		for (const auto& front : bottomFront[pc])
			if (space[(py + front[1] - 1u) * 7u + px + front[0]])
				return false;

		return true;
	};


	unsigned maxHeight = 0;
	unsigned elev0 = 0;
	unsigned maxElev = 0;

	unsigned resA = 0;

	std::set<State> states;
	State latestState;

	unsigned it = 0;
	unsigned pc = 0;
	while (true)
	{
		const unsigned piece = pc % 5u;
		unsigned posx = 2u;
		unsigned posy = maxElev + 3u + maxElongDown[piece];

		if (posy >= 100)
		{
			std::cout << "overflow" << std::endl;
			return;
		}

		while (true)
		{
			if (jets[it++ % jets.size()] == '<')
			{
				if (leftMvmtOk(piece, posx, posy))
					--posx;
			}
			else
			{
				if (rightMvmtOk(piece, posx, posy))
					++posx;
			}

			if (downMvmtOk(piece, posx, posy))
				--posy;
			else
			{
				unsigned addElev = posy + maxElongUp[piece] + 1u > maxElev ?
					posy + maxElongUp[piece] + 1u - maxElev : 0;
				maxElev += addElev;
				maxHeight += addElev;

				for (const auto& p : pieces[piece])
					space[(posy + p[1]) * 7u + posx + p[0]] = true;

				if (posx == 0)
					elev0 = posy + 1u + elongUp0[piece];

				break;
			}
		}

		++pc;
		if (pc == 2022)
			resA = maxHeight;

		// compute the heap surface shape and its min elevation
		std::vector<char> sfc;
		int px = 1;
		int py = elev0;
		int dx = 1;
		int dy = 0;
		unsigned minElev = py;
		while (px < 7)
		{
			int cx = px + (dx - dy - 1) / 2;
			int cy = py + (dx + dy - 1) / 2;
			if (7 * cy + cx < 0 || space[7 * cy + cx])
			{
				std::swap(dx, dy);
				dx = -dx;
			}
			else if (7 * (cy - dx) + cx + dy >= 0 && !space[7 * (cy - dx) + cx + dy])
			{
				std::swap(dx, dy);
				dy = -dy;
			}
			px += dx;
			py += dy;
			sfc.push_back((char)((3+3*dx+dy)/2));
			minElev = std::min(minElev, (unsigned)py);
		}

		/*
		if (pc < 20)
		{
			for (size_t i = maxElev; i < maxElev + 1; --i)
			{
				std::cout << "|";
				for (size_t k = 0; k < 7; ++k)
					std::cout << (space[7u * i + k] ? '#' : '.');
				std::cout << "|" << std::endl;
			}
			std::cout << "+-------+" << std::endl;
			std::cout << std::endl;
		}
		*/

		// throw away lines below the min elevation
		maxElev -= minElev;
		elev0 -= minElev;
		space >>= 7u * minElev;

		// save current state
		State state;
		state.sfc = sfc;
		state.pc = pc;
		state.it = it % jets.size();
		state.h = maxHeight;

		// if state has occurred before, we are finished for part b here
		if (!states.insert(state).second)
		{
			if (latestState.pc == 0)
				latestState = state;

			// if part a is also finished, leave
			if (pc >= 2022)
				break;
		}
	}

	// part b post-computation
	uint64_t resB = 0;
	const auto first = states.find(latestState);
	if (first != states.end())
	{
		uint64_t ha = first->h;
		uint64_t hb = latestState.h;
		uint64_t pca = first->pc;
		uint64_t pcb = latestState.pc;
		uint64_t periods = (uint64_t(1000000000000) - pca) / (pcb - pca);
		uint64_t dh = hb - ha;

		uint64_t rest = uint64_t(1000000000000) - (pca + periods * (pcb - pca));
		const auto restIt = std::find_if(states.begin(), states.end(),
			[&](const State& s){ return s.pc == first->pc + rest;});
		uint64_t hr = (restIt)->h;

		resB = dh * periods + hr;
	}


	writeSolution(resA, resB);
}


