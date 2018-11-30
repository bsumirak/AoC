/*
 * day12.h
 *
 *  Created on: 12.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<12>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::string line;

	std::vector<std::vector<size_t> > vConn;
	vConn.reserve(2000);

	// read data
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		size_t proc;
		iss >> proc;
		vConn.resize(proc+1);

		std::string tmp;
		iss >> tmp; // throw away "<->"

		// read connections list
		while (iss >> tmp)
		{
			if (tmp[tmp.size()-1] == ',')
				tmp = tmp.substr(0, tmp.size()-1);

			int conn = atoi(tmp.c_str());

			vConn[proc].push_back((size_t) conn);
		}
	}

	// part a
	size_t sz = vConn.size();
	std::vector<size_t> flag(sz, 0);
	std::queue<size_t> q;
	size_t cnt0 = 0;
	size_t cntG = 0;
	for (size_t k = 0; k < sz; ++k)
	{
		if (flag[k])
			continue;

		q.push(k);
		++cntG;

		while (!q.empty())
		{
			size_t a = q.front();
			q.pop();

			flag[a] = cntG;
			if (cntG == 1) // count members of group 0
				++cnt0;

			size_t connSz = vConn[a].size();
			for (size_t i = 0; i < connSz; ++i)
				if (!flag[vConn[a][i]])
					q.push(vConn[a][i]);
		}
	}

	size_t sola = cnt0;
	size_t solb = cntG;
	writeSolution(sola, solb);
}


