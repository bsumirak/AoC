/*
 * day25.h
 *
 *  Created on: 2022-12-25
 *      Author: mbreit
 */


template <>
void executeDay<25>(const std::string& fn)
{
	// read input
	int64_t sum = 0;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		while (std::getline(infile, line))
		{
			int64_t res = 0;
			int64_t fct = 1;
			for (unsigned k = line.size(); k > 0; --k)
			{
				char c = line[k - 1];
				if (c >= '1' && c <= '2')
					res += fct * (c - '0');
				else if (c == '-')
					res -= fct;
				else if (c == '=')
					res -= 2 * fct;

				fct *= 5;
			}
			sum += res;
		}
		infile.close();
	}

	// part a
	std::string resA;
	while (sum > 0)
	{
		auto r = sum % 5;
		if (r < 3)
			resA.insert(0, 1, '0' + r);
		else
		{
			resA.insert(0, 1, r == 3 ? '=' : '-');
			sum += 5;
		}
		sum /= 5;
	}


	writeSolution(resA, 0);
}


