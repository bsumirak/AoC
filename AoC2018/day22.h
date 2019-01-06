/*
 * day22.h
 *
 *  Created on: 2019-01-06
 *      Author: mbreit
 */


struct WalkState
{
	WalkState(uint _x, uint _y, uint _t, uint _gear)
	: x(_x), y(_y), t(_t), gear(_gear) {}

	uint x;
	uint y;
	uint t;
	uint gear;
};


struct CompareWalkState
{
	CompareWalkState(uint _tx, uint _ty)
	: tx(_tx), ty(_ty) {}

	bool operator()(const WalkState* ws1, const WalkState* ws2) const
	{
		return ws1->t + 2*(abs(ws1->x - tx) + abs(ws1->y - ty))
			> ws2->t + 2*(abs(ws2->x - tx) + abs(ws2->y - ty)) ;
	}

	uint tx;
	uint ty;
};


template <>
void executeDay<22>(const std::string& fn)
{
	typedef std::pair<uint, uint> uvec2;
	uint depth = 9465;
	uvec2 target(13, 704);

	const uint tx = target.first;
	const uint ty = target.second;
	uint nX = target.first + 100;
	uint nY = target.second + 100;

	// part a
	std::vector<uint> erosionLvl(nX*nY, 0);
	for (uint i = 0; i < nX; ++i)
		erosionLvl[i] = (16807*i + depth) % 20183;

	for (uint j = 1; j < nY; ++j)
	{
		erosionLvl[j*nX] = (48271*j + depth) % 20183;
		for (uint i = 1; i < nX; ++i)
		{
			uint geolInd = erosionLvl[(j-1)*nX+i] * erosionLvl[j*nX+i-1];
			if (j == ty && i == tx)
				geolInd = 0;
			erosionLvl[j*nX+i] = (geolInd + depth) % 20183;
		}
	}

	uint totalRisk = 0;
	for (uint i = 0; i <= target.first; ++i)
		for (uint j = 0; j <= target.second; ++j)
			totalRisk += erosionLvl[j*nX+i] % 3;


	// part b
	WalkState* ws = new WalkState(0, 0, 0, 1);
	CompareWalkState cws(tx, ty);
	std::priority_queue<WalkState*, std::vector<WalkState*>, CompareWalkState> q(cws);
	q.push(ws);

	std::vector<std::vector<uint> > minTimes(3, std::vector<uint>(nX*nY, std::numeric_limits<uint>::max()));
	uint minTargetTime = 8 * (target.first + target.second) + 7;
	while (!q.empty())
	{
		WalkState* ws = q.top();
		q.pop();

		uint ind = ws->y * nX + ws->x;

		// has someone been here before us with the same gear?
		if (ws->t >= minTimes[ws->gear][ind])
		{
			delete ws;
			continue;
		}
		minTimes[ws->gear][ind] = ws->t;

		// are we at the target?
		uint targetDistance = abs(ws->x - tx) + abs(ws->y - ty);
		if (targetDistance == 0)
		{
			// do not forget to take out the torch
			if (ws->gear != 1)
				ws->t += 7;

			if (ws->t < minTargetTime)
			{
				//std::cout << "Found a way in " << ws->t << " minutes." << std::endl;
				minTargetTime = ws->t;
			}

			delete ws;
			continue;
		}

		// check whether target is still reachable in lower than minimal time
		uint targetTime = ws->t + targetDistance;
		if (targetTime >= minTargetTime)
		{
			delete ws;
			continue;
		}

		// check options to go on
		uint type = erosionLvl[ind] % 3;

		// south
		if (ws->y < nY - 1)
		{
			uint nextType = erosionLvl[ind + nX] % 3;
			bool needSwitchOfGear = nextType == ws->gear;
			uint nextGear = needSwitchOfGear ? 3 - (type + nextType) : ws->gear;
			uint nextDistance = ws->y >= ty ? targetDistance+1 : targetDistance-1;
			uint nextTime = needSwitchOfGear ? ws->t + 8 : ws->t + 1;
			if (nextTime + nextDistance < minTargetTime)
				q.push(new WalkState(ws->x, ws->y+1, nextTime, nextGear));
		}

		// east
		if (ws->x < nX - 1)
		{
			uint nextType = erosionLvl[ind + 1] % 3;
			bool needSwitchOfGear = nextType == ws->gear;
			uint nextGear = needSwitchOfGear ? 3 - (type + nextType) : ws->gear;
			uint nextDistance = ws->x >= tx ? targetDistance+1 : targetDistance-1;
			uint nextTime = needSwitchOfGear ? ws->t + 8 : ws->t + 1;
			if (nextTime + nextDistance < minTargetTime)
				q.push(new WalkState(ws->x+1, ws->y, nextTime, nextGear));
		}

		// north
		if (ws->y > 0)
		{
			uint nextType = erosionLvl[ind - nX] % 3;
			bool needSwitchOfGear = nextType == ws->gear;
			uint nextGear = needSwitchOfGear ? 3 - (type + nextType) : ws->gear;
			uint nextDistance = ws->y > ty ? targetDistance-1 : targetDistance+1;
			uint nextTime = needSwitchOfGear ? ws->t + 8 : ws->t + 1;
			if (nextTime + nextDistance < minTargetTime)
				q.push(new WalkState(ws->x, ws->y-1, nextTime, nextGear));
		}

		// west
		if (ws->x > 0)
		{
			uint nextType = erosionLvl[ind - 1] % 3;
			bool needSwitchOfGear = nextType == ws->gear;
			uint nextGear = needSwitchOfGear ? 3 - (type + nextType) : ws->gear;
			uint nextDistance = ws->x > tx ? targetDistance-1 : targetDistance+1;
			uint nextTime = needSwitchOfGear ? ws->t + 8 : ws->t + 1;
			if (nextTime + nextDistance < minTargetTime)
				q.push(new WalkState(ws->x-1, ws->y, nextTime, nextGear));
		}

		delete ws;
	}


	writeSolution(totalRisk, minTargetTime);
}


