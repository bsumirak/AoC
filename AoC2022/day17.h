/*
 * day17.h
 *
 *  Created on: 2022-12-17
 *      Author: mbreit
 */


struct State17
{
	std::vector<char> sfc;
	unsigned pc = 0;
	unsigned it = 0;
	unsigned h = 0;

	bool operator==(const State17& s) const
	{
		return sfc == s.sfc && (pc - s.pc) % 5 == 0 && (it - s.it) % js == 0;
	}

	bool operator<(const State17& s) const
	{
		if (sfc < s.sfc)
			return true;
		if (s.sfc < sfc)
			return false;

		if (pc % 5 < s.pc % 5)
			return true;
		if (s.pc % 5 < pc % 5)
			return false;

		return it % js < s.it % js;
	}

	static unsigned js;
};
unsigned State17::js = 1;


template <>
void executeDay<17>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::string jets;
	{
		infile >> jets;
		infile.close();
	}
	State17::js = jets.size();
	std::set<State17> states;
	State17 latestState;


	std::bitset<100 * 7> space;

	unsigned maxH = 0;
	unsigned elev0 = 0;
	unsigned minElev = 0;
	unsigned maxElev = 0;

	unsigned resA = 0;

	unsigned it = 0;
	unsigned pc = 0;
	while (pc < jets.size() * 5 * 5000)
	{
		unsigned posx = 2u;
		unsigned posy = maxElev + 3u;
		if (pc % 5u == 1)
			posy += 1;

		if (posy >= 100)
		{
			std::cout << "overflow" << std::endl;
			return;
		}

		while (true)
		{
			bool left = jets[it++ % jets.size()] == '<';

			if (pc % 5u == 0)
			{
				if (left)
				{
					if (posx > 0u && !space[posy * 7u + posx - 1u])
						--posx;
				}
				else
				{
					if (posx < 3u && !space[posy * 7u + posx + 4u])
						++posx;
				}

				if (posy > 0 && !space[(posy - 1u) * 7u + posx] && !space[(posy - 1u) * 7u + posx + 1u]
					&&!space[(posy - 1u) * 7u + posx + 2u] && !space[(posy - 1u) * 7u + posx + 3u])
					--posy;
				else
				{
					maxH = std::max(maxH, maxH + posy + 1u - maxElev);
					space[posy * 7u + posx] = true;
					space[posy * 7u + posx + 1u] = true;
					space[posy * 7u + posx + 2u] = true;
					space[posy * 7u + posx + 3u] = true;
					if (posx == 0)
						elev0 = posy + 1u;
					break;
				}
			}
			else if (pc % 5u == 1)
			{
				if (left)
				{
					if (posx > 0u && !space[posy * 7u + posx - 1u]
						&& !space[(posy + 1u) * 7u + posx] && !space[(posy - 1u) * 7u + posx])
						--posx;
				}
				else
				{
					if (posx < 4u && !space[posy * 7u + posx + 3u]
						&& !space[(posy + 1u) * 7u + posx + 2u] && !space[(posy - 1u) * 7u + posx + 2u])
						++posx;
				}

				if (posy > 1u && !space[(posy - 1u) * 7u + posx] && !space[(posy - 2u) * 7u + posx + 1u]
					&&!space[(posy - 1u) * 7u + posx + 2u])
					--posy;
				else
				{
					maxH = std::max(maxH, maxH + posy + 2u - maxElev);
					space[posy * 7u + posx] = true;
					space[posy * 7u + posx + 1u] = true;
					space[posy * 7u + posx + 2u] = true;
					space[(posy + 1u) * 7u + posx + 1u] = true;
					space[(posy - 1u) * 7u + posx + 1u] = true;
					if (posx == 0)
						elev0 = posy + 1u;
					break;
				}
			}
			else if (pc % 5u == 2)
			{
				if (left)
				{
					if (posx > 0u && !space[posy * 7u + posx - 1u]
						&& !space[(posy + 1u) * 7u + posx + 1u] && !space[(posy + 2u) * 7u + posx + 1u])
						--posx;
				}
				else
				{
					if (posx < 4u && !space[posy * 7u + posx + 3u]
						&& !space[(posy + 1u) * 7u + posx + 3u] && !space[(posy + 2u) * 7u + posx + 3u])
						++posx;
				}

				if (posy > 0 && !space[(posy - 1u) * 7u + posx] && !space[(posy - 1u) * 7u + posx + 1u]
					&&!space[(posy - 1u) * 7u + posx + 2u])
					--posy;
				else
				{
					maxH = std::max(maxH, maxH + posy + 3u - maxElev);
					space[posy * 7u + posx] = true;
					space[posy * 7u + posx + 1u] = true;
					space[posy * 7u + posx + 2u] = true;
					space[(posy + 1u) * 7u + posx + 2u] = true;
					space[(posy + 2u) * 7u + posx + 2u] = true;
					if (posx == 0)
						elev0 = posy + 1u;
					break;
				}
			}
			else if (pc % 5u == 3)
			{
				if (left)
				{
					if (posx > 0u && !space[posy * 7u + posx - 1u] && !space[(posy + 1u) * 7u + posx - 1u]
						&& !space[(posy + 2u) * 7u + posx - 1u] && !space[(posy + 3u) * 7u + posx - 1u])
						--posx;
				}
				else
				{
					if (posx < 6u && !space[posy * 7u + posx + 1u] && !space[(posy + 1u) * 7u + posx + 1u]
						&& !space[(posy + 2u) * 7u + posx + 1u] && !space[(posy + 3u) * 7u + posx + 1u])
						++posx;
				}

				if (posy > 0 && !space[(posy - 1u) * 7u + posx])
					--posy;
				else
				{
					maxH = std::max(maxH, maxH + posy + 4u - maxElev);
					space[posy * 7u + posx] = true;
					space[(posy + 1u) * 7u + posx] = true;
					space[(posy + 2u) * 7u + posx] = true;
					space[(posy + 3u) * 7u + posx] = true;
					if (posx == 0)
						elev0 = posy + 4u;
					break;
				}
			}
			else if (pc % 5u == 4)
			{
				if (left)
				{
					if (posx > 0u && !space[posy * 7u + posx - 1u] && !space[(posy + 1u) * 7u + posx - 1u])
						--posx;
				}
				else
				{
					if (posx < 5u && !space[posy * 7u + posx + 2u] && !space[(posy + 1u) * 7u + posx + 2u])
						++posx;
				}

				if (posy > 0 && !space[(posy - 1u) * 7u + posx] && !space[(posy - 1u) * 7u + posx + 1u])
					--posy;
				else
				{
					maxH = std::max(maxH, maxH + posy + 2u - maxElev);
					space[posy * 7u + posx] = true;
					space[posy * 7u + posx + 1u] = true;
					space[(posy + 1u) * 7u + posx] = true;
					space[(posy + 1u) * 7u + posx + 1u] = true;
					if (posx == 0)
						elev0 = posy + 2u;
					break;
				}
			}
		}

		++pc;
		if (pc == 2022)
			resA = maxH;

		// compute the heap surface shape and its min and max elevation
		std::vector<char> sfc;
		int px = 1;
		int py = elev0;
		minElev = py;
		maxElev = py;
		int dx = 1;
		int dy = 0;
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
			maxElev = std::max(maxElev, (unsigned)py);
		}

		// throw away lines below the min elevation
		maxElev -= minElev;
		elev0 -= minElev;
		space >>= 7u * minElev;

		// save current state
		State17 state;
		state.sfc = sfc;
		state.pc = pc;
		state.it = it;
		state.h = maxH;

		// if state has occurred before, part b is finished
		if (!states.insert(state).second)
		{
			if (latestState.pc == 0)
				latestState = state;

			if (pc >= 2022)
				break;
		}
	}

	// part b
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
			[&](const State17& s){ return s.pc == first->pc + rest;});
		uint64_t hr = (restIt)->h;

		resB = dh * periods + hr;
	}


	writeSolution(resA, resB);
}


