/*
 * day09.h
 *
 *  Created on: 2024-12-09
 *      Author: mbreit
 */

template <>
void executeDay<9>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	int64_t resA = 0;
	int64_t resB = 0;

	std::string line;
	std::getline(infile, line);
	const auto sz = line.size();

	// part a
	{
		size_t i1 = 0;
		size_t i2 = sz + 1u;
		unsigned n = 0;

		size_t pos = 0;
		while (i1 < i2)
		{
			const unsigned n1 = line[i1] - '0';
			resA += (((2u * pos + n1 - 1u) * n1) / 2u) * (i1 / 2u);
			pos += n1;

			++i1;

			unsigned n2 = line[i1] - '0';
			while (n2 > 0)
			{
				if (n == 0)
				{
					i2 -= 2u;
					if (i1 >= i2)
						break;
					n = line[i2] - '0';
				}

				const auto num = std::min(n, n2);
				resA += (((2u * pos + num - 1u) * num) / 2u) * (i2 / 2u);
				pos += num;

				n -= num;
				n2 -= num;
			}

			++i1;
			if (i1 >= i2)
			{
				resA += (((2u * pos + n - 1u) * n) / 2u) * (i2 / 2u);
				break;
			}
		}
	}

	// part b
	std::vector<unsigned> pos(sz, 0u);
	for (size_t k = 1u; k < sz; ++k)
		pos[k] = pos[k-1] + (line[k-1] - '0');

	for (size_t i2 = sz - 1; i2 > 0; i2 -= 2u)
	{
		bool moved = false;
		const unsigned n2 = line[i2] - '0';
		for (size_t i1 = 1u; i1 < i2; i1 += 2u)
		{
			const unsigned n1 = line[i1] - '0';
			if (n1 >= n2)
			{
				resB += (((2u * pos[i1] + n2 - 1u) * n2) / 2u) * (i2 / 2u);
				pos[i1] += n2;
				line[i1] = '0' + (n1 - n2);
				moved = true;
				break;
			}
		}

		if (!moved)
			resB += (((2u * pos[i2] + n2 - 1u) * n2) / 2u) * (i2 / 2u);
	}


	writeSolution(resA, resB);
}


