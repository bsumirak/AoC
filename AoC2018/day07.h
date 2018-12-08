/*
 * day07.h
 *
 *  Created on: 07.12.2017
 *      Author: mbreit
 */



template <>
void executeDay<7>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());
	std::map<char, std::vector<char> > deps;
	char first, second;
	while (infile >> first)
	{
		infile >> second;
		deps[second].push_back(first);
		deps[first];
	}

	std::map<char, std::vector<char> > copyDeps(deps);

	// part a
	std::string order;
	std::map<char, std::vector<char> >::const_iterator it = deps.begin();
	std::map<char, std::vector<char> >::const_iterator itEnd = deps.end();

	std::map<char, bool> used;
	for (; it != itEnd; ++it)
		used[it->first] = false;

	it = deps.begin();
	while (it != itEnd)
	{
		if (it->second.size() || used[it->first])
		{
			++it;
			continue;
		}

		char c = it->first;
		used[c] = true;
		order += c;

		std::map<char, std::vector<char> >::iterator it1 = deps.begin();
		for (; it1 != itEnd; ++it1)
		{
			const std::size_t sz = it1->second.size();
			for (std::size_t i = 0; i < sz; ++i)
				if (it1->second[i] == c)
				{
					it1->second.erase(it1->second.begin()+i);
					break;
				}
		}

		it = deps.begin();
	}


	// part b
	it = copyDeps.begin();
	itEnd = copyDeps.end();

	std::map<char, bool> workedOn;
	for (; it != itEnd; ++it)
	{
		used[it->first] = false;
		workedOn[it->first] = false;
	}
	int time = -1;
	int finishes[5] = {0,0,0,0,0};
	char curJob[5] = {'0', '0', '0', '0', '0'};
	while (true)
	{
		// who is finishing?
		int finisher = 0;
		int minFinish = 3000;
		for (int i = 0; i < 5; ++i)
			if (finishes[i] > time && finishes[i] < minFinish)
				minFinish = finishes[i];

		std::cout << minFinish << std::endl;
		time = minFinish;

		// all finishers' jobs are done
		for (int i = 0; i < 5; ++i)
		{
			if (finishes[i] == minFinish)
			{
				char c = curJob[i];
				//used[curJob[i]] = true;

				std::map<char, std::vector<char> >::iterator it1 = copyDeps.begin();
				for (; it1 != itEnd; ++it1)
				{
					const std::size_t sz = it1->second.size();
					for (std::size_t i = 0; i < sz; ++i)
						if (it1->second[i] == c)
						{
							it1->second.erase(it1->second.begin()+i);
							break;
						}
				}

				curJob[i] = '0';
			}
		}

		// all unoccupied workers can take new job
		int nextWorker = 0;
		it = copyDeps.begin();
		bool foundNewJob = false;
		while (nextWorker < 5)
		{
			if (curJob[nextWorker] != '0')
			{
				std::cout << "worker " << nextWorker << " is occupied" << std::endl;
				++nextWorker;
				continue;
			}

			while (it != itEnd && (it->second.size() || used[it->first]))
				++it;

			// no more jobs
			if (it == itEnd)
			{
				std::cout << "worker " << nextWorker << " is idle from time "
					<< time << " onwards" << std::endl;
				break;
			}

			foundNewJob = true;
			curJob[nextWorker] = it->first;
			finishes[nextWorker] = time + 60 + it->first - 'A' + 1;
			used[it->first] = true;

			std::cout << "worker " << nextWorker << " takes job "
				<< it->first << " at time " << time << std::endl;

			++it;
			++nextWorker;
		}

		if (!foundNewJob)
		{
			bool workersOccupied = false;
			for (int i = 0; i < 5; ++i)
			{
				if (curJob[i] != '0')
				{
					workersOccupied = true;
					break;
				}
			}

			if (!workersOccupied)
				break;
		}
	}



	writeSolution(order, time);
}


