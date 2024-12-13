/*
 * day13.h
 *
 *  Created on: 2024-12-13
 *      Author: mbreit
 */

template <>
void executeDay<13>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	struct Machine
	{
		std::array<int64_t, 2> btnA{0, 0};
		std::array<int64_t, 2> btnB{0, 0};
		std::array<int64_t, 2> prize{0, 0};
	} m;

	int64_t resA = 0u;
	int64_t resB = 0u;
	while (infile >> m.btnA[0])
	{
		infile >> m.btnA[1];
		infile >> m.btnB[0];
		infile >> m.btnB[1];
		infile >> m.prize[0];
		infile >> m.prize[1];

		const auto det = m.btnA[0] * m.btnB[1] - m.btnA[1] * m.btnB[0];
		if (det == 0u)
			std::cout << "linear dependency!" << std::endl;

		auto ad = m.prize[0] * m.btnB[1] - m.prize[1] * m.btnB[0];
		auto bd = m.prize[1] * m.btnA[0] - m.prize[0] * m.btnA[1];

		if (ad % det == 0 && bd % det == 0)
			resA += (3u * ad + bd) / det;

		auto p = m.prize;
		p[0] += int64_t(10000000000000u);
		p[1] += int64_t(10000000000000u);

		ad = p[0] * m.btnB[1] - p[1] * m.btnB[0];
		bd = p[1] * m.btnA[0] - p[0] * m.btnA[1];

		if (ad % det == 0 && bd % det == 0)
			resB += (3u * ad + bd) / det;
	}


	writeSolution(resA, resB);
}


