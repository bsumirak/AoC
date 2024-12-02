/*
 * day02.h
 *
 *  Created on: 2024-12-02
 *      Author: mbreit
 */

template <>
void executeDay<2>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	unsigned resA = 0;
	unsigned resB = 0;

	auto check = [](const std::vector<unsigned>& v)
	{
		bool unsafe = false;

		unsigned last = v[0];
		unsigned type = 0u;

		const auto sz = v.size();
		for (size_t k = 1u; k < sz; ++k)
		{
			unsigned u = v[k];

			if (type == 0u)
				type = u < last ? 1u : 2u;

			if ((type == 1u && (u >= last || last - u > 3u))
				|| (type == 2u && (u <= last || u - last > 3u)))
			{
				unsafe = true;
				break;
			}

			last = u;
		}

		return !unsafe;
	};


	std::vector<unsigned> v;

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		unsigned u = 0u;
		v.clear();
		while (iss >> u)
			v.push_back(u);

		if (check(v))
		{
			++resA;
			++resB;
			continue;
		}

		auto w = v;
		const auto sz = v.size();
		for (size_t k = 0; k < sz; ++k)
		{
			w = v;
			w.erase(w.begin() + k);
			if (check(w))
			{
				++resB;
				break;
			}
		}
	}


	writeSolution(resA, resB);
}


