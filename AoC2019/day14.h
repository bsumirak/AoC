/*
 * day14.h
 *
 *  Created on: 14.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<14>(const std::string& fn)
{
	std::string input = "jxqlasbh";

	size_t ones = 0;
	std::vector<std::vector<size_t> > mem(128);
	for (size_t i = 0; i < 128; ++i)
		mem[i].resize(128, 0);

	for (size_t i = 0; i < 128; ++i)
	{
		std::ostringstream oss;
		oss << input << "-" << i;

		std::string knotHash = calculate_knot_hash(oss.str());

		// count ones in knot hash
		std::vector<size_t>& row = mem[i];
		for (size_t j = 0; j < 32; ++j)
		{
			switch (knotHash[j])
			{
				case '0':
					break;
				case '1':
					ones += 1;
					row[4*j+3] = 1;
					break;
				case '2':
					ones += 1;
					row[4*j+2] = 1;
					break;
				case '3':
					ones += 2;
					row[4*j+3] = 1;
					row[4*j+2] = 1;
					break;
				case '4':
					ones += 1;
					row[4*j+1] = 1;
					break;
				case '5':
					ones += 2;
					row[4*j+3] = 1;
					row[4*j+1] = 1;
					break;
				case '6':
					ones += 2;
					row[4*j+2] = 1;
					row[4*j+1] = 1;
					break;
				case '7':
					ones += 3;
					row[4*j+3] = 1;
					row[4*j+2] = 1;
					row[4*j+1] = 1;
					break;
				case '8':
					ones += 1;
					row[4*j] = 1;
					break;
				case '9':
					ones += 2;
					row[4*j+3] = 1;
					row[4*j] = 1;
					break;
				case 'a':
					ones += 2;
					row[4*j+2] = 1;
					row[4*j] = 1;
					break;
				case 'b':
					ones += 3;
					row[4*j+3] = 1;
					row[4*j+2] = 1;
					row[4*j] = 1;
					break;
				case 'c':
					ones += 2;
					row[4*j+1] = 1;
					row[4*j] = 1;
					break;
				case 'd':
					ones += 3;
					row[4*j+3] = 1;
					row[4*j+1] = 1;
					row[4*j] = 1;
					break;
				case 'e':
					ones += 3;
					row[4*j+2] = 1;
					row[4*j+1] = 1;
					row[4*j] = 1;
					break;
				case 'f':
					ones += 4;
					row[4*j+3] = 1;
					row[4*j+2] = 1;
					row[4*j+1] = 1;
					row[4*j] = 1;
					break;
				default:
					std::cout << "Unexpected character in knot hash." << std::endl;
					throw;
			}
		}
	}

	// analyze contiguity
	size_t regCnt = 1;
	for (size_t i = 0; i < 128; ++i)
	{
		for (size_t j = 0; j < 128; ++j)
		{
			if (mem[i][j] != 1)
				continue;

			// start a new region
			++regCnt;
			std::queue<std::pair<size_t, size_t> > q;
			q.push(std::make_pair(i,j));

			// find whole region
			while (!q.empty())
			{
				const std::pair<size_t, size_t>& p = q.front();
				size_t k = p.first;
				size_t l = p.second;
				q.pop();

				// check for 1
				if (mem[k][l] != 1)
					continue;

				// assign region
				mem[k][l] = regCnt;

				// look left, right, top, bottom
				if (k > 0)
					q.push(std::make_pair(k-1, l));
				if (k < 127)
					q.push(std::make_pair(k+1, l));
				if (l > 0)
					q.push(std::make_pair(k, l-1));
				if (l < 127)
					q.push(std::make_pair(k, l+1));
			}
		}
	}

	--regCnt;

	writeSolution(ones, regCnt);
}


