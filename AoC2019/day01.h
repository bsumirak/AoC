/*
 * day01.h
 *
 *  Created on: 2018-12-01
 *      Author: mbreit
 */


template <>
void executeDay<1>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::vector<int> list;
	int i;

	// part a
	int suma = 0;
	while (infile >> i)
	{
		suma += i;
		list.push_back(i);
	}

	// part b
	int b = 0;
	size_t l = list.size();
	std::vector<int> vList(1,0);
	while (true)
	{
		for (size_t k = 0; k < l; ++k)
		{
			int newVal = vList.back() + list[k];
			const size_t vListSz = vList.size();
			for (size_t j = 0; j < vListSz; ++j)
			{
				if (vList[j] == newVal)
				{
					b = newVal;
					goto result;
				}
			}
			vList.push_back(newVal);
		}
	}

result:
	writeSolution(suma, b);
}


