/*
 * day18.h
 *
 *  Created on: 2018-12-28
 *      Author: mbreit
 */


template <>
void executeDay<18>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());

	std::vector<std::string> field(52);
	field[0] = field[51] = std::string('.', 52);
	for (size_t i = 1; i < 51; ++i)
	{
		infile >> field[i];
		field[i].insert(0, 1, '.');
		field[i].append(1, '.');
	}

	std::vector<std::string> nextField(field);
	std::vector<std::vector<std::string> > allFields(1, field);

	size_t resourceValue10 = 0;
	size_t resourceValue1G = 0;
	size_t k = 0;
	while (true)
	{
		for (size_t i = 1; i < 51; ++i)
		{
			for (size_t j = 1; j < 51; ++j)
			{
				// evaluate adjacent acres
				size_t nAdjTree = 0;
				size_t nAdjLumb = 0;

				for (int m = -1; m <= 1; ++m)
				{
					for (int n = -1; n <= 1; ++n)
					{
						if (m == 0 && n == 0)
							continue;
						if (field[i+m][j+n] == '|')
							++nAdjTree;
						else if (field[i+m][j+n] == '#')
							++nAdjLumb;
					}
				}

				// create new field
				switch (field[i][j])
				{
					case '.':
						if (nAdjTree >= 3)
							nextField[i][j] = '|';
						else
							nextField[i][j] = '.';
						break;
					case '|':
						if (nAdjLumb >= 3)
							nextField[i][j] = '#';
						else
							nextField[i][j] = '|';
						break;
					case '#':
						if (nAdjTree >= 1 && nAdjLumb >= 1)
							nextField[i][j] = '#';
						else
							nextField[i][j] = '.';
						break;
					default:
						std::cout << "Invalid acre value " << field[i][j] << "." << std::endl;
						exit(1);
				}
			}
		}
		field.swap(nextField);
		++k;


		// solution part a
		if (k == 10)
		{
			size_t nTree = 0;
			size_t nLumb = 0;
			for (size_t i = 1; i < 51; ++i)
			{
				for (size_t j = 1; j < 51; ++j)
				{
					if (field[i][j] == '|')
						++nTree;
					else if (field[i][j] == '#')
						++nLumb;
				}
			}
			resourceValue10 = nTree * nLumb;
		}


		// solution part b
		size_t sameField = k;
		for (size_t l = 0; l < k; ++l)
		{
			bool isIdentical = true;
			for (size_t i = 1; i < 51; ++i)
			{
				if (allFields[l][i] != field[i])
				{
					isIdentical = false;
					break;
				}
			}
			if (isIdentical)
				sameField = l;
		}
		if (sameField < k)
		{
			size_t period = k - sameField;
			size_t offset = ((size_t) 1000000000 - sameField) % period;

			size_t nTree = 0;
			size_t nLumb = 0;
			for (size_t i = 1; i < 51; ++i)
			{
				for (size_t j = 1; j < 51; ++j)
				{
					if (allFields[sameField+offset][i][j] == '|')
						++nTree;
					else if (allFields[sameField+offset][i][j] == '#')
						++nLumb;
				}
			}
			resourceValue1G = nTree * nLumb;

			break;
		}

		allFields.push_back(field);
	}

	writeSolution(resourceValue10, resourceValue1G);
}


