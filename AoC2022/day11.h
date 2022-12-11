/*
 * day11.h
 *
 *  Created on: 2022-12-11
 *      Author: mbreit
 */


template <>
void executeDay<11>(const std::string& fn)
{
	typedef uint64_t tp;

	struct Monkey
	{
		std::function<tp(tp)> fct;
		tp testDiv;
		std::array<size_t, 2> tgt;
	};

	constexpr size_t numMonkeys = 8;

	std::array<Monkey, numMonkeys> monkeys =
	{
	 Monkey{[&](tp v){return 3u * v;}, 11u, {2, 7}},
	 Monkey{[&](tp v){return v * v;}, 7u, {0, 2}},
	 Monkey{[&](tp v){return v + 1u;}, 3u, {7, 5}},
	 Monkey{[&](tp v){return v + 8u;}, 5u, {6, 4}},
	 Monkey{[&](tp v){return v + 3u;}, 17u, {1, 0}},
	 Monkey{[&](tp v){return v + 4u;}, 13u, {6, 3}},
	 Monkey{[&](tp v){return 17u * v;}, 19u, {4, 1}},
	 Monkey{[&](tp v){return v + 7u;}, 2u, {5, 3}}
	};

	std::array<std::vector<tp>, numMonkeys> items =
	{
	 std::vector<tp>{50u, 70u, 54u, 83u, 52u, 78u},
	 std::vector<tp>{71u, 52u, 58u, 60u, 71u},
	 std::vector<tp>{66u, 56u, 56u, 94u, 60u, 86u, 73u},
	 std::vector<tp>{83u, 99u},
	 std::vector<tp>{98u, 98u, 79u},
	 std::vector<tp>{76u},
	 std::vector<tp>{52u, 51u, 84u, 54u},
	 std::vector<tp>{82u, 86u, 91u, 79u, 94u, 92u, 59u, 94u}
	};
	auto itemsB = items;

	tp mod = 1u;
	for (size_t m = 0; m < numMonkeys; ++m)
		mod *= monkeys[m].testDiv;

	std::array<tp, numMonkeys> inspections;
	std::array<tp, numMonkeys> inspectionsB;
	std::fill(inspections.begin(), inspections.end(), 0u);
	std::fill(inspectionsB.begin(), inspectionsB.end(), 0u);
	for (size_t r = 0; r < 10000; ++r)
	{
		for (size_t m = 0; m < numMonkeys; ++m)
		{
			// part a
			if (r < 20)
			{
				for (auto item : items[m])
				{
					++inspections[m];
					item = monkeys[m].fct(item) / 3u;
					const size_t tgt = item % monkeys[m].testDiv == 0 ? monkeys[m].tgt[0] : monkeys[m].tgt[1];
					items[tgt].push_back(item);
				}
			}

			// part b
			for (auto item : itemsB[m])
			{
				++inspectionsB[m];
				item = monkeys[m].fct(item) % mod;
				const size_t tgt = item % monkeys[m].testDiv == 0 ? monkeys[m].tgt[0] : monkeys[m].tgt[1];
				itemsB[tgt].push_back(item);
			}
			items[m].clear();
			itemsB[m].clear();
		}
	}

	std::sort(inspections.begin(), inspections.end());
	tp resA = inspections[numMonkeys - 2] * inspections[numMonkeys - 1];

	std::sort(inspectionsB.begin(), inspectionsB.end());
	tp resB = inspectionsB[numMonkeys - 2] * inspectionsB[numMonkeys - 1];

	writeSolution(resA, resB);
}


