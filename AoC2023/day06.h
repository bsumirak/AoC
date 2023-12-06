/*
 * day06.h
 *
 *  Created on: 2023-12-06
 *      Author: mbreit
 */

template <>
void executeDay<6>(const std::string& fn)
{
	const auto computeNumberOfWaysToWin = [](uint64_t time, uint64_t record) -> uint64_t
	{
		const double rt = std::sqrt(0.25 * time * time - record);
		return std::floor(0.5 * time + rt) - std::ceil(0.5 * time - rt) + 1;
	};
	
	// part a
	std::array<uint64_t, 4> time = {48, 93, 85, 95};
	std::array<uint64_t, 4> record = {296, 1928, 1236, 1391};
	uint64_t resA = 1;
	for (size_t k = 0; k < 4; ++k)
		resA *= computeNumberOfWaysToWin(time[k], record[k]);
	
	// part b
	uint64_t resB = computeNumberOfWaysToWin(uint64_t(48938595), uint64_t(296192812361391));
	
	
	writeSolution(resA, resB);
}


