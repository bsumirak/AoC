/*
 * day20.h
 *
 *  Created on: 20.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<20>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	std::vector<std::vector<int> > p;
	std::vector<std::vector<int> > v;
	std::vector<std::vector<int> > a;

	p.resize(1000);
	v.resize(1000);
	a.resize(1000);

	for (size_t i = 0; i < 1000; ++i)
	{
		p[i].resize(3);
		v[i].resize(3);
		a[i].resize(3);
	}

	size_t cnt = 0;

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		iss >> p[cnt][0];
		iss >> p[cnt][1];
		iss >> p[cnt][2];

		iss >> v[cnt][0];
		iss >> v[cnt][1];
		iss >> v[cnt][2];

		iss >> a[cnt][0];
		iss >> a[cnt][1];
		iss >> a[cnt][2];

		++cnt;
	}

	//part a
	int minA = 1000;
	int minIndA = -1;
	for (size_t i = 0; i < 1000; ++i)
	{
		int oneNorm = std::abs(a[i][0]) + std::abs(a[i][1]) + std::abs(a[i][2]);
		if (oneNorm <= minA)
		{
			// in case of a tie: whose start velocity is bigger?
			if (oneNorm == minA)
			{
				int oneNormV0 = std::abs(v[minIndA][0]) + std::abs(v[minIndA][1]) + std::abs(v[minIndA][2]);
				int oneNormV1 = std::abs(v[i][0]) + std::abs(v[i][1]) + std::abs(v[i][2]);
				if (oneNormV1 <= oneNormV0)
				{
if (oneNormV1 == oneNormV0)
	std::cout << "equal v" << std::endl;

					minA = oneNorm;
					minIndA = i;
				}
			}
			else
			{
				minA = oneNorm;
				minIndA = i;
			}
		}
	}

	// part b
	std::map<int, std::vector<std::pair<int, int> > > collisions;
	for (size_t i = 0; i < 1000; ++i)
	{
		for (size_t j = i+1; j < 1000; ++j)
		{
			// will there be a collision? when?
			int times[2];
			bool valid[2] = {true, true};
			bool sol = true;
			for (size_t k = 0; k < 3; ++k)
			{
				if (a[j][k] == a[i][k])
				{
					if (v[j][k] == v[i][k])
					{
						if (p[j][k] == p[i][k])
						{
							if (k == 0)
								std::cout << "problem: exact same first coords" << std::endl;
						}
						else
						{
							sol = false;
							break;
						}
					}
					else
					{
						if ((p[j][k] - p[i][k]) % (v[j][k] - v[i][k]) != 0)
						{
							sol = false;
							break;
						}

						if (k == 0)
						{
							times[0] = -(p[j][k] - p[i][k]) / (v[j][k] - v[i][k]);
							valid[1] = false;
						}
						else
						{
							int time0 = -(p[j][k] - p[i][k]) / (v[j][k] - v[i][k]);
							if (time0 != times[0])
								valid[0] = false;
							if (time0 != times[1])
								valid[1] = false;
						}

					}
				}
				else
				{
					double underSqrt = ((double) (v[j][k] - v[i][k])) / (a[j][k] - a[i][k]) + 0.5;
					underSqrt = underSqrt * underSqrt;
					underSqrt -= 2 * (p[j][k] - p[i][k]) / (double) (a[j][k] - a[i][k]);

					if (underSqrt >= 0)
					{
						double time = - ((v[j][k] - v[i][k]) / (double) (a[j][k] - a[i][k]) + 0.5);

						if (k == 0)
						{
							times[0] = (int) round(time - sqrt(underSqrt));
							times[1] = (int) round(time + sqrt(underSqrt));
						}
						else
						{
							int time0 = (int) round(time - sqrt(underSqrt));
							int time1 = (int) round(time + sqrt(underSqrt));
							if (time0 != times[0] && time1 != times[0])
								valid[0] = false;
							if (time0 != times[1] && time1 != times[1])
								valid[1] = false;
						}
					}
					else
					{
						sol = false;
						break;
					}
				}

				if (!valid[0] && !valid[1])
				{
					sol = false;
					break;
				}
			}

			if (sol)
			{
				int t = valid[0] ? times[0] : times[1];

				// check that there is no rounding error
				int pi0t = p[i][0] + t*v[i][0] + t*(t+1)/2*a[i][0];
				int pi1t = p[i][1] + t*v[i][1] + t*(t+1)/2*a[i][1];
				int pi2t = p[i][2] + t*v[i][2] + t*(t+1)/2*a[i][2];

				int qi0t = p[j][0] + t*v[j][0] + t*(t+1)/2*a[j][0];
				int qi1t = p[j][1] + t*v[j][1] + t*(t+1)/2*a[j][1];
				int qi2t = p[j][2] + t*v[j][2] + t*(t+1)/2*a[j][2];

				if (pi0t == qi0t && pi1t == qi1t && pi2t == qi2t)
					collisions[t].push_back(std::make_pair(i,j));
				else if (valid[0] && valid[1])
				{
					t = times[1];
					pi0t = p[i][0] + t*v[i][0] + t*(t+1)/2*a[i][0];
					pi1t = p[i][1] + t*v[i][1] + t*(t+1)/2*a[i][1];
					pi2t = p[i][2] + t*v[i][2] + t*(t+1)/2*a[i][2];

					qi0t = p[j][0] + t*v[j][0] + t*(t+1)/2*a[j][0];
					qi1t = p[j][1] + t*v[j][1] + t*(t+1)/2*a[j][1];
					qi2t = p[j][2] + t*v[j][2] + t*(t+1)/2*a[j][2];

					if (pi0t == qi0t && pi1t == qi1t && pi2t == qi2t)
						collisions[t].push_back(std::make_pair(i,j));
				}
			}
		}
	}

	std::vector<bool> exists(1000, true);
	std::map<int, std::vector<std::pair<int, int> > >::const_iterator it = collisions.begin();
	std::map<int, std::vector<std::pair<int, int> > >::const_iterator it_end = collisions.end();
	for (; it != it_end; ++it)
	{
		if (it->first < 0)
			continue;

		std::vector<int> annihilationList;
		const std::vector<std::pair<int, int> >& collT = it->second;
		size_t sz = collT.size();
		for (size_t i = 0; i < sz; ++i)
		{
			if (exists[collT[i].first] && exists[collT[i].second])
			{
				annihilationList.push_back(collT[i].first);
				annihilationList.push_back(collT[i].second);
			}
		}

		for (size_t i = 0; i < annihilationList.size(); ++i)
			exists[annihilationList[i]] = false;
	}

	size_t remaining = 1000;
	for (size_t i = 0; i < 1000; ++i)
		if (!exists[i])
			--remaining;


	writeSolution(minIndA, remaining);
}


