/*
 * day04.h
 *
 *  Created on: 2018-12-04
 *      Author: mbreit
 */


struct GuardEvent
{
	bool operator<(const GuardEvent& gd2) const
	{
		if (month < gd2.month) return true;
		if (month > gd2.month) return false;
		if (day < gd2.day) return true;
		if (day > gd2.day) return false;
		if (hour < gd2.hour) return true;
		if (hour > gd2.hour) return false;
		if (minute < gd2.minute) return true;
		if (minute > gd2.minute) return false;
		return false;
	}

	int month, day, hour, minute;
	int event;
};

template <>
void executeDay<4>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::string line;
	int suma = 0;
	int sumb = 0;
	std::vector<GuardEvent> guardEvents(1028);
	std::size_t cnt = 0;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		iss >> guardEvents[cnt].month;
		iss >> guardEvents[cnt].day;
		iss >> guardEvents[cnt].hour;
		iss >> guardEvents[cnt].minute;
		iss >> guardEvents[cnt].event;

		++cnt;
	}

	std::sort(guardEvents.begin(), guardEvents.end());

	int curGuard = -1;
	std::map<int, std::vector<std::pair<int, int> > > guardSleeping;
	std::size_t i = 0;
	while (i < 1028)
	{
		// get current guard
		std::vector<std::pair<int, int> >& sleepList = guardSleeping[guardEvents[i].event];
		++i;

		// sleeping periods
		bool asleep = false;
		while (guardEvents[i].event < 0)
		{
			if (!asleep)
			{
				sleepList.push_back(std::make_pair(guardEvents[i].minute, 60));
				asleep = true;
			}
			else
			{
				sleepList.back().second = guardEvents[i].minute;
				asleep = false;
			}

			++i;
		}
	}

	// part a
	std::map<int, int> guardSleepingMinutes;
	std::map<int, std::vector<std::pair<int, int> > >::const_iterator it = guardSleeping.begin();
	std::map<int, std::vector<std::pair<int, int> > >::const_iterator itEnd = guardSleeping.end();
	for (; it != itEnd; ++it)
	{
		int guard = it->first;
		guardSleepingMinutes[guard];  // make sure this exists
		const std::size_t nSleeps = it->second.size();
		for (size_t i = 0; i < nSleeps; ++i)
			guardSleepingMinutes[guard] += it->second[i].second - it->second[i].first;
	}

	std::map<int, int>::const_iterator it1 = guardSleepingMinutes.begin();
	std::map<int, int>::const_iterator it1End = guardSleepingMinutes.end();
	int maxGuard = it1->first;
	int maxMinutes = it1->second;
	for (++it1; it1 != it1End; ++it1)
	{
		if (it1->second > maxMinutes)
		{
			maxMinutes = it1->second;
			maxGuard = it1->first;
		}
	}

	it = guardSleeping.find(maxGuard);
	int sleep[60];
	for (size_t i = 0; i < 60; ++i)
		sleep[i] = 0;
	const std::size_t nSleeps = it->second.size();
	for (size_t i = 0; i < nSleeps; ++i)
		for (size_t j = it->second[i].first; j < it->second[i].second; ++j)
			++sleep[j];
	int maxMinute = 0;
	int maxSleeps = sleep[0];
	for (size_t i = 1; i < 60; ++i)
	{
		if (sleep[i] > maxSleeps)
		{
			maxMinute = i;
			maxSleeps = sleep[i];
		}
	}

	int sola = maxGuard * maxMinute;


	// part b
	int globMaxGuard = 0;
	int globMaxMinute = 0;
	int globMaxSleep = 0;
	for (it1 = guardSleepingMinutes.begin(); it1 != it1End; ++it1)
	{
		it = guardSleeping.find(it1->first);

		int sleep[60];
		for (size_t i = 0; i < 60; ++i)
			sleep[i] = 0;
		const std::size_t nSleeps = it->second.size();
		for (size_t i = 0; i < nSleeps; ++i)
			for (size_t j = it->second[i].first; j < it->second[i].second; ++j)
				++sleep[j];
		int maxMinute = 0;
		int maxSleeps = sleep[0];
		for (size_t i = 1; i < 60; ++i)
		{
			if (sleep[i] > maxSleeps)
			{
				maxMinute = i;
				maxSleeps = sleep[i];
			}
		}

		if (maxSleeps > globMaxSleep)
		{
			globMaxSleep = maxSleeps;
			globMaxMinute = maxMinute;
			globMaxGuard = it1->first;
		}
	}


	int solb = globMaxGuard * globMaxMinute;


	writeSolution(sola, solb);
}


