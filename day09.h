/*
 * day09.h
 *
 *  Created on: 09.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<9>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	char c;
	int suma = 0;
	int sumb = 0;
	int curScore = 0;
	bool ignoreNext = false;
	bool inGarbage = false;
	while (infile.get(c))
	{
		if (ignoreNext)
		{
			ignoreNext = false;
			continue;
		}

		if (c == '!')
		{
			ignoreNext = true;
			continue;
		}

		if (inGarbage)
		{
			if (c == '>')
				inGarbage = false;
			else
				++sumb;

			continue;
		}

		if (c == '<')
		{
			inGarbage = true;
			continue;
		}

		if (c == '{')
		{
			curScore += 1;
			suma += curScore;
			continue;
		}

		if (c == '}')
		{
			curScore -= 1;
			continue;
		}
	}
	infile.close();

	// solution output
	writeSolution(suma, sumb);
}


