/*
 * day14.h
 *
 *  Created on: 2018-12-14
 *      Author: mbreit
 */


static int addNextRecipes(int& cur0, int& cur1, std::string& board)
{
	int next = (board[cur0] - '0') + (board[cur1] - '0');
	std::ostringstream oss;
	oss << next;
	board += oss.str();

	cur0 = (cur0 + 1 + board[cur0] - '0') % board.size();
	cur1 = (cur1 + 1 + board[cur1] - '0') % board.size();

	return next;
}



template <>
void executeDay<14>(const std::string& fn)
{
	const int n = 920831;

	std::string board = "37";

	int cur0 = 0;
	int cur1 = 1;

	while (board.size() < n + 10)
		addNextRecipes(cur0, cur1, board);

	std::string sola = "";
	for (int i = 0; i < 10; ++i)
		sola += board[n+i];

	int solb;
	if ((solb = board.find("920831")) == std::string::npos)
	{
		int state = 0;
		while (true)//
		{
			int next = addNextRecipes(cur0, cur1, board);

			if (state == 0 && next == 9)
				state = 1;
			else if (state == 1 && next == 2)
				state = 2;
			else if (state == 2 && next == 0)
				state = 3;
			else if (state == 3 && next == 8)
				state = 4;
			else if (state == 4 && next == 3)
				state = 5;
			else if (state == 5 && (next == 1 || next > 9))
				break;
			else
			{
				solb = board.size();
				state = 0;
			}
		}
	}

	writeSolution(sola, solb);
}


