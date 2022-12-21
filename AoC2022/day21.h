/*
 * day21.h
 *
 *  Created on: 2022-12-21
 *      Author: mbreit
 */

struct Node21
{
	std::string id;
	std::array<Node21*, 2> c;
	char op = ' ';
	int64_t val = -1;
};


int64_t compute21(Node21* n)
{
	if (n->op == ' ')
		return n->val;

	switch (n->op)
	{
		case '+':
			return compute21(n->c[0]) + compute21(n->c[1]);
		case '-':
			return compute21(n->c[0]) - compute21(n->c[1]);
		case '*':
			return compute21(n->c[0]) * compute21(n->c[1]);
		case '/':
			return compute21(n->c[0]) / compute21(n->c[1]);
	}

	std::cout << "error" << std::endl;
	return 0;
}


bool containsHumn21(Node21* n)
{
	if (n->id == "humn")
		return true;

	if (n->op == ' ')
		return false;

	return containsHumn21(n->c[0]) || containsHumn21(n->c[1]);
}


template <>
void executeDay<21>(const std::string& fn)
{
	// read input
	std::map<std::string, Node21*> monkeys;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		while (std::getline(infile, line))
		{
			std::istringstream iss(line);
			std::string s;
			iss >> s;

			Node21* node;
			auto it = monkeys.lower_bound(s);
			if (it != monkeys.end() && it->first == s)
				node = it->second;
			else
			{
				node = new Node21();
				node->id = s;
				monkeys.insert(it, std::make_pair(s, node));
			}

			if (line[5] >= '0' && line[5] <= '9')
			{
				iss >> node->val;
				continue;
			}

			std::string s1;
			std::string s2;
			char op;
			iss >> s1;
			iss >> op;
			iss >> s2;

			Node21* node1;
			it = monkeys.lower_bound(s1);
			if (it != monkeys.end() && it->first == s1)
				node1 = it->second;
			else
			{
				node1 = new Node21();
				node->id = s1;
				monkeys.insert(it, std::make_pair(s1, node1));
			}

			Node21* node2;
			it = monkeys.lower_bound(s2);
			if (it != monkeys.end() && it->first == s2)
				node2 = it->second;
			else
			{
				node2 = new Node21();
				node->id = s2;
				monkeys.insert(it, std::make_pair(s2, node2));
			}

			node->c = {node1, node2};
			node->op = op;
		}
		infile.close();
	}


	// part a
	Node21* root = monkeys["root"];
	int64_t resA = compute21(root);


	// part b
	std::array<uint64_t, 2> resB;
	resB[1] = 1;
	Node21* nd = root;
	if (containsHumn21(root->c[0]))
	{
		resB[0] = compute21(root->c[1]);
		nd = root->c[0];
	}
	else
	{
		resB[0] = compute21(root->c[0]);
		nd = root->c[1];

	}

	while (nd->id != "humn")
	{
		bool left = containsHumn21(nd->c[0]);
		Node21* cmp = left ? nd->c[1] : nd->c[0];
		Node21* cnt = left ? nd->c[0] : nd->c[1];

		int64_t cmpRes = compute21(cmp);
		switch (nd->op)
		{
			case '+':
				resB[0] -= cmpRes * resB[1];
				break;
			case '-':
				resB[0] = left ? resB[0] + cmpRes * resB[1] : cmpRes * resB[1] - resB[0];
				break;
			case '*':
				if (resB[0] % cmpRes == 0)
					resB[0] /= cmpRes;
				else
					resB[1] *= cmpRes;
				break;
			case '/':
				if (left)
				{
					if (resB[1] % cmpRes == 0)
						resB[1] /= cmpRes;
					else
						resB[0] *= cmpRes;
				}
				else
				{
					std::swap(resB[0], resB[1]);
					if (resB[1] % cmpRes == 0)
						resB[1] /= cmpRes;
					else
						resB[0] *= cmpRes;
				}
				break;
		}

		nd = cnt;
	}

	assert(resB[1] == 1);

	writeSolution(resA, resB[0]);
}


