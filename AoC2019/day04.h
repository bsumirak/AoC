/*
 * day04.h
 *
 *  Created on: 2019-12-04
 *      Author: mbreit
 */


template <>
void executeDay<4>(const std::string& fn)
{
	std::vector<int> digits(6);
	int cnt1 = 0;
	int cnt2 = 0;
	for (int a = 146810; a <= 612564; ++a)
	{
		// part a
		int b = a;
		for (int i = 0; i < 6; ++i)
		{
			digits[5-i] = b % 10;
			b /= 10;
		}

		if (digits[0] > digits[1])
			continue;
		if (digits[1] > digits[2])
			continue;
		if (digits[2] > digits[3])
			continue;
		if (digits[3] > digits[4])
			continue;
		if (digits[4] > digits[5])
			continue;

		if (!(digits[0] == digits[1] || digits[1] == digits[2]
			|| digits[2] == digits[3] || digits[3] == digits[4]
			|| digits[4] == digits[5]))
			continue;

		++cnt1;


		// part b
		if (digits[0] == digits[1] && digits[1] != digits[2])
		{
			++cnt2;
			continue;
		}

		if (digits[1] == digits[2] && digits[0] != digits[1]
			&& digits[2] != digits[3])
		{
			++cnt2;
			continue;
		}

		if (digits[2] == digits[3] && digits[1] != digits[2]
			&& digits[3] != digits[4])
		{
			++cnt2;
			continue;
		}

		if (digits[3] == digits[4] && digits[2] != digits[3]
			&& digits[4] != digits[5])
		{
			++cnt2;
			continue;
		}

		if (digits[4] == digits[5] && digits[3] != digits[4])
		{
			++cnt2;
			continue;
		}
	}

	writeSolution(cnt1, cnt2);
}


