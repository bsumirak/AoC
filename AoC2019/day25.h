/*
 * day25.h
 *
 *  Created on: 25.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<25>(const std::string& fn)
{
	int state = 0;
	int pos = 0;

	std::map<int, bool> tape;

	for (size_t i = 0; i < 12656374; ++i)
	{
		switch (state)
		{
		case 0:
			if (!tape[pos])
			{
				tape[pos] = 1;
				++pos;
				state = 1;
			}
			else
			{
				tape[pos] = 0;
				--pos;
				state = 2;
			}
			break;
		case 1:
			if (!tape[pos])
			{
				tape[pos] = 1;
				--pos;
				state = 0;
			}
			else
			{
				tape[pos] = 1;
				--pos;
				state = 3;
			}
			break;
		case 2:
			if (!tape[pos])
			{
				tape[pos] = 1;
				++pos;
				state = 3;
			}
			else
			{
				tape[pos] = 0;
				++pos;
				state = 2;
			}
			break;
		case 3:
			if (!tape[pos])
			{
				tape[pos] = 0;
				--pos;
				state = 1;
			}
			else
			{
				tape[pos] = 0;
				++pos;
				state = 4;
			}
			break;
		case 4:
			if (!tape[pos])
			{
				tape[pos] = 1;
				++pos;
				state = 2;
			}
			else
			{
				tape[pos] = 1;
				--pos;
				state = 5;
			}
			break;
		case 5:
			if (!tape[pos])
			{
				tape[pos] = 1;
				--pos;
				state = 4;
			}
			else
			{
				tape[pos] = 1;
				++pos;
				state = 0;
			}
			break;
		}
	}

	size_t cnt = 0;
	std::map<int, bool>::const_iterator it = tape.begin();
	std::map<int, bool>::const_iterator itEnd = tape.end();
	for (; it != itEnd; ++it)
		if (it->second)
			++cnt;

	writeSolution(cnt, (int) 0);
}


