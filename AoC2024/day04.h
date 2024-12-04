/*
 * day04.h
 *
 *  Created on: 2024-12-04
 *      Author: mbreit
 */

template <>
void executeDay<4>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	
	std::vector<char> letters;
	size_t nCol = 1u;
	size_t nRow = 0u;

	std::string line;
	while (std::getline(infile, line))
	{
		nCol = line.size();
		letters.insert(letters.end(), line.begin(), line.end());
		++nRow;
	}

	const size_t sz =  letters.size();
	// part a
	
	const auto check = [&letters](size_t k, int j)
	{
		if (letters[k + j] != 'M')
			return 0u;
		if (letters[k + 2 * j] != 'A')
			return 0u;
		return letters[k + 3 * j] == 'S' ? 1u : 0u;
	};
	
	unsigned resA = 0;
	for (size_t k = 0; k < sz; ++k)
	{
		if (letters[k] != 'X')
			continue;
	
		const size_t r = k / nCol;
		const size_t c = k % nCol;
	
		if (c >= 3u)	
			resA += check(k, -1);
		if (c < nCol - 3u)
			resA += check(k, 1);
		if (r >= 3u)
			resA += check(k, -nCol);
		if (r < nRow - 3u)
			resA += check(k, nCol);
		if (c >= 3u && r >= 3u)
			resA += check(k, -(nCol + 1));
		if (c < nCol - 3u && r < nRow - 3u)
			resA += check(k, nCol + 1);
		if (c < nCol - 3u && r >= 3u)
			resA += check(k, -(nCol - 1));
		if (c >= 3u && r < nRow - 3u)
			resA += check(k, nCol - 1);
	}

	// part n
	unsigned resB = 0;
	for (size_t k = 0; k < sz; ++k)
	{
		const size_t r = k / nCol;
		const size_t c = k % nCol;
		
		if (r == 0u || r == nRow - 1 || c == 0u || c == nCol - 1)
			continue;

		if (letters[k] != 'A')
			continue;
		
		if (((letters[k - nCol - 1] == 'M' && letters[k + nCol + 1] == 'S')
			|| (letters[k - nCol - 1] == 'S' && letters[k + nCol + 1] == 'M'))
			&& ((letters[k - nCol + 1] == 'M' && letters[k + nCol - 1] == 'S')
			|| (letters[k - nCol + 1] == 'S' && letters[k + nCol - 1] == 'M')))
		{
			++resB;
		}
	}
	

	writeSolution(resA, resB);
}


