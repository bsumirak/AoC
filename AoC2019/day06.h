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


template <typename TNode>
std::size_t shortestPathLengthBetweenTreeNodes(TNode* n1, TNode* n2)
{
	std::size_t len = 1;
	TNode** continueSoloWith = NULL;

	// get up to root from both nodes simultaneously,
	// break if one hits the path of the other or if one ends up in root
	while (!continueSoloWith)
	{
		n1->visit = len;
		if (n1->parent)
		{
			n1 = n1->parent;
			if (n1->visit)
			{
				len += n1->visit - 1;
				break;
			}
		}
		else
			continueSoloWith = &n2;

		n2->visit = len;
		if (n2->parent)
		{
			n2 = n2->parent;
			if (n2->visit)
			{
				len += n2->visit - 1;
				continueSoloWith = NULL;
				break;
			}
		}
		else
			continueSoloWith = &n1;

		++len;
	}

	// if one node has ended up in root, continue solo with the other,
	// until it hits the path of the former
	if (continueSoloWith)
	{
		TNode* n = *continueSoloWith;
		n->visit = len;
		++len;
		while (n->parent)
		{
			n = n->parent;
			if (n->visit)
			{
				len += n->visit - 2;
				break;
			}
		}
		if (!n->visit)
		{
			std::cout << "No common root for nodes." << std::endl;
			throw std::runtime_error("");
		}
	}

	return len;
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


	// part b
	node6* me = nodeMap["YOU"]->parent;
	node6* santa = nodeMap["SAN"]->parent;
	std::size_t solb = shortestPathLengthBetweenTreeNodes(me, santa);

	writeSolution(sola, solb);
}


