/*
 * day22.h
 *
 *  Created on: 2024-12-22
 *      Author: mbreit
 */


template <>
void executeDay<22>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	uint64_t resA = 0u;
	unsigned resB = 0u;

	constexpr unsigned nCombo = 19u * 19u * 19u * 19u;
	std::vector<bool> occ(nCombo, false);
	std::vector<unsigned> seq(nCombo, 0u);

	uint64_t secret = 0u;
	while (infile >> secret)
	{
		occ.clear();
		occ.resize(nCombo, false);
		unsigned p1 = secret % 10u;
		unsigned p2 = p1;
		unsigned p3 = p1;
		unsigned p4 = p1;
		for (size_t k = 0; k < 2000u; ++k)
		{
			auto a = secret * 64u;
			secret = secret ^ a;
			secret = secret % 16777216u;

			auto b = secret / 32u;
			secret = secret ^ b;
			secret = secret % 16777216u;

			auto c = secret * 2048u;
			secret = secret ^ c;
			secret = secret % 16777216u;

			const auto price = secret % 10u;
			if (k >= 3u)
			{
				const auto v = p2 + 9u - p1
					+ 19u * (p3 + 9u - p2)
					+ 361u * (p4 + 9u - p3)
					+ 6859u * (price + 9u - p4);
				if (!occ[v])
				{
					occ[v] = true;
					seq[v] += price;
					resB = std::max(resB, seq[v]);
				}
			}

			p1 = p2;
			p2 = p3;
			p3 = p4;
			p4 = price;
		}
		resA += secret;
	}


	writeSolution(resA, resB);
}

