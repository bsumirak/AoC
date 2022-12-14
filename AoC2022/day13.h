/*
 * day13.h
 *
 *  Created on: 2022-12-13
 *      Author: mbreit
 */

struct List13
{
	std::vector<List13*> c;
	unsigned v{0u - 1u};
};

List13* parseList13(const std::string& s, size_t& ind)
{
	assert(s[ind] == '[');

	List13* list = new List13();
	++ind;

	while (s[ind] != ']')
	{
		if (s[ind] == ',')
		{
			++ind;
			continue;
		}

		if (s[ind] == '[')
		{
			List13* l = parseList13(s, ind);
			list->c.push_back(l);
		}
		else
		{
			List13* l = new List13();
			char* next;
			l->v = strtoul(s.data() + ind, &next, 10);
			list->c.push_back(l);
			ind = next - s.data();
		}
	}
	++ind;

	return list;
}

int compareLists13(List13* l1, List13* l2)
{
	if (l1->v != 0u - 1u && l2->v != 0u - 1u)
	{
		if (l1->v < l2->v)
			return -1;
		if (l1->v > l2->v)
			return 1;
		return 0;
	}

	if (l1->v != 0u - 1u)
	{
		if (l2->c.empty())
			return 1;
		int res = compareLists13(l1, l2->c[0]);
		if (res != 0)
			return res;
		if (l2->c.size() > 1)
			return -1;
		return 0;
	}

	if (l2->v != 0u - 1u)
	{
		if (l1->c.empty())
			return -1;
		int res = compareLists13(l1->c[0], l2);
		if (res != 0)
			return res;
		if (l1->c.size() > 1)
			return 1;
		return 0;
	}

	size_t iMax = std::min(l1->c.size(), l2->c.size());
	for (size_t i = 0; i < iMax; ++i)
	{
		int res = compareLists13(l1->c[i], l2->c[i]);
		if (res != 0)
			return res;
	}
	if (l1->c.size() < l2->c.size())
		return -1;
	if (l1->c.size() > l2->c.size())
		return 1;
	return 0;
}

#if 0
void printList13(List13* l)
{
	if (l->v != 0u -1u)
	{
		std::cout << l->v;
		return;
	}
	std::cout << "[";
	const size_t sz = l->c.size();
	for (size_t k = 0; k < sz; ++k)
	{
		printList13(l->c[k]);
		if (k != sz - 1)
			std::cout << ",";
	}
	std::cout << "]";
}
#endif


template <>
void executeDay<13>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());
	std::string s1;
	std::string s2;

	unsigned resA = 0;
	unsigned k = 0;
	std::vector<List13*> packets;
	while (infile >> s1)
	{
		++k;
		infile >> s2;
		size_t ind = 0;
		List13* l1 = parseList13(s1, ind);
		ind = 0;
		List13* l2 = parseList13(s2, ind);

		// part a
		if (compareLists13(l1, l2) == -1)
			resA += k;

		packets.push_back(l1);
		packets.push_back(l2);
	}
	infile.close();

	// part b
	size_t ind = 0;
	List13* d1 = parseList13(std::string("[[2]]"), ind);
	ind = 0;
	List13* d2 = parseList13(std::string("[[6]]"), ind);
	packets.push_back(d1);
	packets.push_back(d2);

	std::sort(packets.begin(), packets.end(),
		[](List13* l1, List13* l2){return compareLists13(l1, l2) == -1;});

	const auto it1 = std::find(packets.begin(), packets.end(), d1);
	const auto it2 = std::find(packets.begin(), packets.end(), d2);
	const auto resB = (std::distance(packets.begin(), it1) + 1)
		* (std::distance(packets.begin(), it2) + 1);

#if 0
	for (auto p : packets)
	{
		printList13(p);
		std::cout << std::endl;
	}
#endif

	writeSolution(resA, resB);
}


