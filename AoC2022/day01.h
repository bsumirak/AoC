/*
 * day01.h
 *
 *  Created on: 2022-12-01
 *      Author: mbreit
 */


template <>
void executeDay<1>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	int i;

	std::vector<int> v;
	while (infile >> i)
		v.push_back(i);
	infile.close();
	std::size_t sz = v.size();


	int resA = 0;



	int resB = 0;


	writeSolution(resA, resB);
}


