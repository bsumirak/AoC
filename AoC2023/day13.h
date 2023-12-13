/*
 * day13.h
 *
 *  Created on: 2023-12-13
 *      Author: mbreit
 */


template <>
void executeDay<13>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	
	std::vector<std::string> map;
	std::string line;
	
	size_t resA = 0;
	size_t resB = 0;
	while (std::getline(infile, line))
	{
		if (!line.empty())
			map.emplace_back(std::move(line));
		else
		{
			const size_t nr = map.size();
			const size_t nc = map[0].size();

			const auto mirrorErrorsInCol = [&](size_t a)
			{
				size_t ret = 0;
				const size_t numMirrorCols = std::min(a, nc - a);
				for (size_t r = 0; r < nr; ++r)
					for (size_t k = 0; k < numMirrorCols; ++k)
						if (map[r][a - k - 1] != map[r][a + k])
							++ret;
				return ret;
			};

			for (size_t a = 1; a < nc; ++a)
			{
				const size_t errors = mirrorErrorsInCol(a);
				if (errors == 0)
					resA += a;	
				else if (errors == 1)
					resB += a;
			}
			
			const auto mirrorErrorsInRow = [&](size_t a)
			{
				size_t ret = 0;
				const size_t numMirrorRows = std::min(a, nr - a);
				for (size_t k = 0; k < numMirrorRows; ++k)
					for (size_t c = 0; c < nc; ++c)
						if (map[a - k - 1][c] != map[a + k][c])
							++ret;
				return ret;
			};
			
			for (size_t a = 1; a < nr; ++a)
			{
				const size_t errors = mirrorErrorsInRow(a);
				if (errors == 0)
					resA += 100u * a;
				else if (errors == 1)
					resB += 100u * a;
			}
						
			map.clear();
		}
	}

	writeSolution(resA, resB);
}


