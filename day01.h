/*
 * day01.h
 *
 *  Created on: 01.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<1>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::string sSeq;
	char c;

	// part a
	int suma = 0;
	char last = '\0';
	while (infile.get(c))
	{
		if (c == last)
			suma += c - '0';

		last = c;

		// save to string (easier for part b)
		sSeq += c;
	}
	infile.close();
	size_t n = sSeq.size();

	// do not forget wrapping
	if (sSeq[n-1] == sSeq[0])
		suma += sSeq[n-1] - '0';

	const char* seq = sSeq.c_str();

	// part b
	int sumb = 0;
	int p = n / 2;
	for (size_t i = 0; i < n; ++i)
	{
		if (seq[i] == seq[(i+p) % n])
			sumb += seq[i] - '0';
	}

	writeSolution(suma, sumb);
}


