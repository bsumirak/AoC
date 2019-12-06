/*
 * day06.h
 *
 *  Created on: 2019-12-06
 *      Author: mbreit
 */

#include <functional>

struct node6
{
	node6() : parent(NULL), totalWeight(0), visit(0) {}
	~node6()
	{
		size_t sz = children.size();
		for (size_t i = 0; i < sz; ++i)
			delete children[i];
	}

	std::vector<node6*> children;
	node6* parent;
	int totalWeight;
	int visit;
};



template <typename TNode, typename TFct>
void traverseDF(TNode* node, TFct& fct)
{
	fct(node);
	const std::size_t nCh = node->children.size();
	for (std::size_t c = 0; c < nCh; ++c)
		traverseDF(node->children[c], fct);
}


template <>
void executeDay<6>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::string a, b;

	// read input
	std::map<std::string, node6*> nodeMap;
	node6* root;
	while (infile >> a)
	{
		infile >> b;
		auto nodeItA = nodeMap.find(a);
		auto nodeItB = nodeMap.find(b);

		node6*& nodeA = nodeMap[a];
		node6*& nodeB = nodeMap[b];

		if (nodeItA == nodeMap.end())
			nodeA = new node6();
		if (nodeItB == nodeMap.end())
			nodeB = new node6();

		if (nodeB->parent)
		{
			std::cout << b << " already orbits " << a << "." << std::endl;
			throw std::runtime_error("");
		}
		nodeB->parent = nodeA;
		nodeA->children.push_back(nodeB);

		if (a == "COM")
		{
			//std::cout << "com found" << std::endl;
			root = nodeA;
		}

	}

	// part a
	node6* node = root;
	node->totalWeight = 0;
	int sola = 0;
	auto lambda = [&] (node6* n) -> void
	{
		sola += n->totalWeight = n->parent ? n->parent->totalWeight + 1 : 0;
	};
	traverseDF(node, lambda);

	// part b (note: this breadth-first search is unnecessarily complex)
	int solb;
	node6* me = nodeMap["YOU"]->parent;
	node6* santa = nodeMap["SAN"]->parent;

	std::queue<std::pair<node6*, int> > q;
	q.push(std::make_pair(me, 0));
	while (!q.empty())
	{
		std::pair<node6*, int> cur = q.front();
		q.pop();

		cur.first->visit = 1;
		node6* p = cur.first->parent;
		if (p == santa)
		{
			solb = cur.second + 1;
			break;
		}
		if (p && p->visit != 1)
			q.push(std::make_pair(p, cur.second+1));

		bool santaFound = false;
		const std::size_t nCh = cur.first->children.size();
		for (std::size_t c = 0; c < nCh; ++c)
		{
			node6* ch = cur.first->children[c];
			if (ch == santa)
			{
				solb = cur.second + 1;
				santaFound = true;
				break;
			}
			if (ch->visit != 1)
				q.push(std::make_pair(ch, cur.second+1));
		}
		if (santaFound)
			break;
	}

	writeSolution(sola, solb);
}


