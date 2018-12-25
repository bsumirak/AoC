/*
 * day25.h
 *
 *  Created on: 2018-12-25
 *      Author: mbreit
 */


struct vector4
{
	int coord[4];
};

template <>
void executeDay<25>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::vector<vector4> coords;

	// part a
	vector4 tmp;
	while (infile >> tmp.coord[0])
	{
		infile >> tmp.coord[1];
		infile >> tmp.coord[2];
		infile >> tmp.coord[3];
		coords.push_back(tmp);
	}
	const size_t sz = coords.size();
	std::vector<std::vector<vector4> > constell;

	for (size_t i = 0; i < sz; ++i)
	{
		std::vector<size_t> merge;
		for (size_t j = 0; j < constell.size(); ++j)
		{
			std::vector<vector4>& c = constell[j];
			for (size_t k = 0; k < c.size(); ++k)
			{
				if (abs(c[k].coord[0]-coords[i].coord[0])
						+ abs(c[k].coord[1]-coords[i].coord[1])
						+ abs(c[k].coord[2]-coords[i].coord[2])
						+ abs(c[k].coord[3]-coords[i].coord[3]) <= 3)
				{
					c.push_back(coords[i]);
					merge.push_back(j);
					break;
				}
			}
		}
		if (merge.size())
		{
			constell[merge[0]].push_back(coords[i]);
			for (size_t j = 1; j < merge.size(); ++j)
			{
				for (size_t k = 0; k < constell[merge[j]].size(); ++k)
					constell[merge[0]].push_back(constell[merge[j]][k]);
			}

			for (size_t j = merge.size() -1; j > 0; --j)
				constell.erase(constell.begin() + merge[j]);
		}
		else
		{
			constell.push_back(std::vector<vector4>(1));
			constell.back().back() = coords[i];
		}
	}

	writeSolution(constell.size(), 0);
}


