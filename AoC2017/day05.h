/*
 * day05.h
 *
 *  Created on: 05.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<5>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	// read list
	int tmp;
	std::vector<int> jumpList;
	jumpList.reserve(1000);
	while (infile >> tmp)
		jumpList.push_back(tmp);

	// make a copy for b
	size_t sz = jumpList.size();
	std::vector<int> jumpListb(jumpList);

	// part a
	size_t nja = 0;
	int* jla = &jumpList[0];
	int* jlb = jla + jumpList.size();
	int* jlp = jla;
	while (jlp < jlb && jlp >= jla)
	{
		++nja;
		jlp += (*jlp)++; // jump-increment
	}

	// part b
	jumpList.swap(jumpListb);
	int njb = 0;
	jla = &jumpList[0];
	jlb = jla + jumpList.size();
	jlp = jla;
	while (jlp < jlb && jlp >= jla)
	{
		++njb;
		int jmp = *jlp;
		*jlp += (*jlp >= 3 ? -1 : 1); // in-/decrement
		jlp += jmp; // jump
	}

	writeSolution(nja, njb);
}


