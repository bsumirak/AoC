/*
 * day20.h
 *
 *  Created on: 2022-12-20
 *      Author: mbreit
 */


template <>
void executeDay<20>(const std::string& fn)
{
	// read input
	std::vector<int> v;
	{
		std::ifstream infile(fn.c_str());
		int i;
		while (infile >> i)
			v.push_back(i);
		infile.close();
	}
	const size_t sz = v.size();
	unsigned pos0 = std::distance(v.begin(), std::find(v.begin(), v.end(), 0));


	// part a
	std::vector<int> pos(sz);
	for (size_t k = 0; k < sz; ++k)
		pos[k] = k;

	for (size_t k = 0; k < sz; ++k)
	{
		int mv = (v[k] + 2 * (int)(sz - 1)) % (int)(sz - 1);
		int tgt = (pos[k] + mv) % (int)(sz - 1);
		if (tgt < pos[k])
		{
			for (size_t l = 0; l < sz; ++l)
				if (pos[l] >= tgt && pos[l] < pos[k])
					++pos[l];
			pos[k] = tgt;
		}
		else
		{
			for (size_t l = 0; l < sz; ++l)
				if (pos[l] > pos[k] && pos[l] <= tgt)
					--pos[l];
			pos[k] = tgt;
		}
	}

	int resA = 0;
	for (unsigned k = 1; k <= 3; ++k)
	{
		const auto it = std::find(pos.begin(), pos.end(), (pos[pos0] + k * 1000) % sz);
		const auto p = std::distance(pos.begin(), it);
		resA += v[p];
	}


	// part b
	std::vector<int64_t> vb(sz);
	for (size_t k = 0; k < sz; ++k)
		vb[k] = (int64_t)v[k] * int64_t(811589153);
	std::vector<int> posb(sz);
	for (size_t k = 0; k < sz; ++k)
		posb[k] = k;

	for (size_t n = 0; n < 10; ++n)
	{
		for (size_t k = 0; k < sz; ++k)
		{
			int mv = (vb[k] + int64_t(811589153) * (int64_t)(2*(sz - 1))) % (int64_t)(sz - 1);
			int tgt = (posb[k] + mv) % (int)(sz - 1);
			if (tgt < posb[k])
			{
				for (size_t l = 0; l < sz; ++l)
					if (posb[l] >= tgt && posb[l] < posb[k])
						++posb[l];
				posb[k] = tgt;
			}
			else
			{
				for (size_t l = 0; l < sz; ++l)
					if (posb[l] > posb[k] && posb[l] <= tgt)
						--posb[l];
				posb[k] = tgt;
			}
		}
	}

	int64_t resB = 0;
	for (unsigned k = 1; k <= 3; ++k)
	{
		const auto it = std::find(posb.begin(), posb.end(), (posb[pos0] + k * 1000) % sz);
		const auto p = std::distance(posb.begin(), it);
		resB += vb[p];
	}


	writeSolution(resA, resB);
}


