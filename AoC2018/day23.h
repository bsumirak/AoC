/*
 * day23.h
 *
 *  Created on: 2019-01-06
 *      Author: mbreit
 */


struct NanoBot
{
	NanoBot(int x, int y, int z, uint _r)
	: r(_r)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}

	int pos[3];
	uint r;
};


bool nanoBotsIntersect(NanoBot* nb1, NanoBot* nb2)
{
	return abs(nb1->pos[0] - nb2->pos[0]) + abs(nb1->pos[1] - nb2->pos[1])
		+ abs(nb1->pos[2] - nb2->pos[2]) < nb1->r + nb2->r;
}


struct BeamRegion
{
	BeamRegion(const int64_t* _c1, uint _a, uint _n)
	: a(_a), n(_n)
	{
		for (int i = 0; i < 3; ++i)
			co[i] = _c1[i];
	}

	bool operator<(const BeamRegion& br) const
	{
		// less intersections?
		if (n < br.n)
			return true;
		if (n > br.n)
			return false;


		// greater size?
		if (a > br.a)
			return true;
		if (br.a > a)
			return false;

		// further from origin?
		int thisD = 0;
		int d = 0;
		for (int i = 0; i < 3; ++i)
		{
			if (co[i] + (int64_t) a < 0)
				thisD += -(co[i] + (int64_t) a);
			else if (co[i] > 0)
				thisD += co[i];

			if (br.co[i] + (int64_t) br.a < 0)
				d += -(br.co[i] + (int64_t) br.a);
			else if (br.co[i] > 0)
				d += br.co[i];
		}

		return thisD > d;
	}

	int64_t co[3];
	uint a;
	uint n;
};


void checkForIntersections(BeamRegion& br, const std::vector<NanoBot>& vNB)
{
	const int64_t* co = br.co;
	const uint& a = br.a;
	uint& n = br.n;

	n = 0;
	const size_t sz = vNB.size();
	for (size_t b = 0; b < sz; ++b)
	{
		const NanoBot& nb = vNB[b];
		int d = 0;
		for (int i = 0; i < 3; ++i)
		{
			const int* pos = nb.pos;
			if (co[i] + (int64_t) a < pos[i])
				d += pos[i] - (co[i] + (int64_t) a);
			else if (co[i] > pos[i])
				d += co[i] - pos[i];
		}
		if (d <= nb.r)
			++n;
	}
}


template <>
void executeDay<23>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());

	std::vector<NanoBot> vNB;

	int tmp;
	uint maxR = 0;
	size_t maxInd = 0;
	while (infile >> tmp)
	{
		int y, z;
		uint r;
		infile >> y;
		infile >> z;
		infile >> r;
		vNB.push_back(NanoBot(tmp, y, z, r));

		if (r > maxR)
		{
			maxR = r;
			maxInd = vNB.size() - 1;
		}
	}
	const size_t nNB = vNB.size();


	// part a
	size_t nInRange = 0;
	for (size_t i = 0; i < nNB; ++i)
	{
		uint dist = abs(vNB[i].pos[0] - vNB[maxInd].pos[0]);
		dist += abs(vNB[i].pos[1] - vNB[maxInd].pos[1]);
		dist += abs(vNB[i].pos[2] - vNB[maxInd].pos[2]);
		if (dist <= vNB[maxInd].r)
			++nInRange;
	}


	// part b
	int64_t lower[3] = {std::numeric_limits<int64_t>::max(),
					std::numeric_limits<int64_t>::max(),
					std::numeric_limits<int64_t>::max()};
	int64_t upper[3] = {-std::numeric_limits<int64_t>::max(),
					-std::numeric_limits<int64_t>::max(),
					-std::numeric_limits<int64_t>::max()};
	for (size_t i = 0; i < nNB; ++i)
	{
		lower[0] = std::min(lower[0], (int64_t) vNB[i].pos[0]);
		lower[1] = std::min(lower[1], (int64_t) vNB[i].pos[1]);
		lower[2] = std::min(lower[2], (int64_t) vNB[i].pos[2]);

		upper[0] = std::max(upper[0], (int64_t) vNB[i].pos[0]);
		upper[1] = std::max(upper[1], (int64_t) vNB[i].pos[1]);
		upper[2] = std::max(upper[2], (int64_t) vNB[i].pos[2]);
	}

	uint a = std::max(upper[0] - lower[0], std::max(upper[1] - lower[1], upper[2] - lower[2]));
	a = 1 << (int64_t) std::ceil(std::log2((double) a));
	for (int i = 0; i < 3; ++i)
		lower[i] = (lower[i] + upper[i] - (int64_t)a) / 2;

	BeamRegion bestPoint(lower, 0, 0);
	std::priority_queue<BeamRegion> pq;
	pq.push(BeamRegion(lower, a, nNB));
	while (!pq.empty())
	{
		const BeamRegion br = pq.top();
		pq.pop();

		// if this region is worse than the best,
		// then any remaining BR in the queue must also be worse
		if (br.n < bestPoint.n)
			break;

		// is this a single point?
		if (br.a == 0)
		{
			bestPoint = std::max(bestPoint, br);
			continue;
		}

		// divide and conquer!
		BeamRegion newBR(br.co, br.a >> 1, 0);
		checkForIntersections(newBR, vNB);
		if (!(newBR < bestPoint))
			pq.push(newBR);

		int64_t tmp[3] = {br.co[0] + (int64_t)(br.a+1)/2, br.co[1], br.co[2]};
		newBR = BeamRegion(tmp, br.a >> 1, 0);
		checkForIntersections(newBR, vNB);
		if (!(newBR < bestPoint))
			pq.push(newBR);

		tmp[0] = br.co[0]; tmp[1] = br.co[1] + (int64_t)(br.a+1)/2; tmp[2] = br.co[2];
		newBR = BeamRegion(tmp, br.a >> 1, 0);
		checkForIntersections(newBR, vNB);
		if (!(newBR < bestPoint))
			pq.push(newBR);

		tmp[0] = br.co[0] + (int64_t)(br.a+1)/2; tmp[1] = br.co[1] + (int64_t)(br.a+1)/2; tmp[2] = br.co[2];
		newBR = BeamRegion(tmp, br.a >> 1, 0);
		checkForIntersections(newBR, vNB);
		if (!(newBR < bestPoint))
			pq.push(newBR);

		tmp[0] = br.co[0]; tmp[1] = br.co[1]; tmp[2] = br.co[2] + (int64_t)(br.a+1)/2;
		newBR = BeamRegion(tmp, br.a >> 1, 0);
		checkForIntersections(newBR, vNB);
		if (!(newBR < bestPoint))
			pq.push(newBR);

		tmp[0] = br.co[0] + (int64_t)(br.a+1)/2; tmp[1] = br.co[1]; tmp[2] = br.co[2] + (int64_t)(br.a+1)/2;
		newBR = BeamRegion(tmp, br.a >> 1, 0);
		checkForIntersections(newBR, vNB);
		if (!(newBR < bestPoint))
			pq.push(newBR);

		tmp[0] = br.co[0]; tmp[1] = br.co[1] + (int64_t)(br.a+1)/2; tmp[2] = br.co[2] + (int64_t)(br.a+1)/2;
		newBR = BeamRegion(tmp, br.a >> 1, 0);
		checkForIntersections(newBR, vNB);
		if (!(newBR < bestPoint))
			pq.push(newBR);

		tmp[0] = br.co[0] + (int64_t)(br.a+1)/2; tmp[1] = br.co[1] + (int64_t)(br.a+1)/2; tmp[2] = br.co[2] + (int64_t)(br.a+1)/2;
		newBR = BeamRegion(tmp, br.a >> 1, 0);
		checkForIntersections(newBR, vNB);
		if (!(newBR < bestPoint))
			pq.push(newBR);

		//std::cout << br.n << "  " << br.a << "  " << br.co[0] << "," << br.co[1] << "," << br.co[2] << std::endl;
	}

	int64_t solb = abs(bestPoint.co[0]) + abs(bestPoint.co[1]) + abs(bestPoint.co[2]);

	writeSolution(nInRange, solb);
}


