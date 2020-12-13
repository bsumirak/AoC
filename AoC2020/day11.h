/*
 * day11.h
 *
 *  Created on: 2020-12-11
 *      Author: mbreit
 */


template <>
void executeDay<11>(const std::string& fn)
{
	// read input
	std::vector<std::string> seats;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		while (std::getline(infile, line))
			seats.push_back(line);
		infile.close();
	}
	const std::size_t nRows = seats.size();
	const std::size_t nCols = seats[0].size();
	std::vector<std::string> seatsCopy = seats;


	// part a
	std::size_t resA = 0;
	std::vector<std::string> newSeats = seats;
	bool changed = false;
	do
	{
		changed = false;
		for (size_t i = 0; i < nRows; ++i)
		{
			for (size_t j = 0; j < nCols; ++j)
			{
				newSeats[i][j] = seats[i][j];
				if (seats[i][j] == '.')
					continue;
				else if (seats[i][j] == 'L')
				{
					if (i > 0 && j > 0 && seats[i-1][j-1] == '#')
						continue;
					if (i > 0 && seats[i-1][j] == '#')
						continue;
					if (i > 0 && j < nCols-1 && seats[i-1][j+1] == '#')
						continue;
					if (j > 0 && seats[i][j-1] == '#')
						continue;
					if (j < nCols-1 && seats[i][j+1] == '#')
						continue;
					if (i < nRows-1 && j > 0 && seats[i+1][j-1] == '#')
						continue;
					if (i < nRows-1 && seats[i+1][j] == '#')
						continue;
					if (i < nRows-1 && j < nCols-1 && seats[i+1][j+1] == '#')
						continue;
					newSeats[i][j] = '#';
					changed = true;
				}
				else if (seats[i][j] == '#')
				{
					int cnt = 0;
					if (i > 0 && j > 0 && seats[i-1][j-1] == '#')
						++cnt;
					if (i > 0 && seats[i-1][j] == '#')
						++cnt;
					if (i > 0 && j < nCols-1 && seats[i-1][j+1] == '#')
						++cnt;
					if (j > 0 && seats[i][j-1] == '#')
						++cnt;
					if (j < nCols-1 && seats[i][j+1] == '#')
						++cnt;
					if (i < nRows-1 && j > 0 && seats[i+1][j-1] == '#')
						++cnt;
					if (i < nRows-1 && seats[i+1][j] == '#')
						++cnt;
					if (i < nRows-1 && j < nCols-1 && seats[i+1][j+1] == '#')
						++cnt;
					if (cnt >= 4)
					{
						newSeats[i][j] = 'L';
						changed = true;
					}
				}
			}
		}
		newSeats.swap(seats);
	}
	while (changed);

	for (size_t i = 0; i < nRows; ++i)
		for (size_t j = 0; j < nCols; ++j)
			if (seats[i][j] == '#')
				++resA;


	// part b
	seats = seatsCopy;
	do
	{
		changed = false;
		for (size_t i = 0; i < nRows; ++i)
		{
			for (size_t j = 0; j < nCols; ++j)
			{
				newSeats[i][j] = seats[i][j];
				if (seats[i][j] == '.')
					continue;
				else if (seats[i][j] == 'L')
				{
					for (size_t k = 1; k <= i; ++k)
						if (seats[i-k][j] == '#')
							goto nextSeat;
						else if (seats[i-k][j] == 'L')
							break;
					for (size_t k = i+1; k < nRows; ++k)
						if (seats[k][j] == '#')
							goto nextSeat;
						else if (seats[k][j] == 'L')
							break;
					for (size_t k = 1; k <= j; ++k)
						if (seats[i][j-k] == '#')
							goto nextSeat;
						else if (seats[i][j-k] == 'L')
							break;
					for (size_t k = j+1; k < nCols; ++k)
						if (seats[i][k] == '#')
							goto nextSeat;
						else if (seats[i][k] == 'L')
							break;

					for (size_t k = 1; k <= i; ++k)
						if (j-k < nCols && seats[i-k][j-k] == '#')
							goto nextSeat;
						else if (j-k < nCols && seats[i-k][j-k] == 'L')
							break;
					for (size_t k = 1; k <= i; ++k)
						if (j+k < nCols && seats[i-k][j+k] == '#')
							goto nextSeat;
						else if (j+k < nCols && seats[i-k][j+k] == 'L')
							break;
					for (size_t k = 1; k < nRows - i; ++k)
						if (j-k < nCols && seats[i+k][j-k] == '#')
							goto nextSeat;
						else if (j-k < nCols && seats[i+k][j-k] == 'L')
							break;
					for (size_t k = 1; k < nRows - i; ++k)
						if (j+k < nCols && seats[i+k][j+k] == '#')
							goto nextSeat;
						else if (j+k < nCols && seats[i+k][j+k] == 'L')
							break;

					newSeats[i][j] = '#';
					changed = true;
				}
				else if (seats[i][j] == '#')
				{
					int cnt = 0;
					for (size_t k = 1; k <= i; ++k)
						if (seats[i-k][j] == '#')
							{++cnt; break;}
						else if (seats[i-k][j] == 'L')
							break;
					for (size_t k = i+1; k < nRows; ++k)
						if (seats[k][j] == '#')
							{++cnt; break;}
						else if (seats[k][j] == 'L')
							break;
					for (size_t k = 1; k <= j; ++k)
						if (seats[i][j-k] == '#')
							{++cnt; break;}
						else if (seats[i][j-k] == 'L')
							break;
					for (size_t k = j+1; k < nCols; ++k)
						if (seats[i][k] == '#')
							{++cnt; break;}
						else if (seats[i][k] == 'L')
							break;

					for (size_t k = 1; k <= i; ++k)
						if (j-k < nCols && seats[i-k][j-k] == '#')
							{++cnt; break;}
						else if (j-k < nCols && seats[i-k][j-k] == 'L')
							break;
					for (size_t k = 1; k <= i; ++k)
						if (j+k < nCols && seats[i-k][j+k] == '#')
							{++cnt; break;}
						else if (j+k < nCols && seats[i-k][j+k] == 'L')
							break;
					for (size_t k = 1; k < nRows - i; ++k)
						if (j-k < nCols && seats[i+k][j-k] == '#')
							{++cnt; break;}
						else if (j-k < nCols && seats[i+k][j-k] == 'L')
							break;
					for (size_t k = 1; k < nRows - i; ++k)
						if (j+k < nCols && seats[i+k][j+k] == '#')
							{++cnt; break;}
						else if (j+k < nCols && seats[i+k][j+k] == 'L')
							break;

					if (cnt >= 5)
					{
						newSeats[i][j] = 'L';
						changed = true;
					}
				}

			nextSeat:
				continue;
			}
		}
		newSeats.swap(seats);
	}
	while (changed);


	std::size_t resB = 0;
	for (size_t i = 0; i < nRows; ++i)
		for (size_t j = 0; j < nCols; ++j)
			if (seats[i][j] == '#')
				++resB;



	writeSolution(resA, resB);
}


