/*
 * day08.h
 *
 *  Created on: 2018-12-08
 *      Author: mbreit
 */


struct Node
{
	~Node()
	{
		size_t sz = children.size();
		for (size_t i = 0; i < sz; ++i)
			delete children[i];
	}

	int nChildrenLeftToProcess;
	int nData;
	std::vector<Node*> children;
	int value;
};


template <>
void executeDay<8>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::string line;

	// part a
	int dataSum = 0;
	std::stack<Node*> stack;
	Node* node = new Node();
	infile >> node->nChildrenLeftToProcess;
	infile >> node->nData;
	node->value = 0;
	stack.push(node);
	while (!stack.empty())
	{
		Node* curNode = stack.top();
		if (curNode->nChildrenLeftToProcess == 0)
		{
			int tmp;
			for (int i = 0; i < curNode->nData; ++i)
			{
				infile >> tmp;

				if (curNode->children.size())
				{
					if (tmp-1 < curNode->children.size())
						curNode->value += curNode->children[tmp-1]->value;
				}
				else
					curNode->value += tmp;

				dataSum += tmp;
			}

			stack.pop();
		}
		else
		{
			--curNode->nChildrenLeftToProcess;
			Node* newNode = new Node();
			infile >> newNode->nChildrenLeftToProcess;
			infile >> newNode->nData;
			newNode->value = 0;
			stack.push(newNode);
			curNode->children.push_back(newNode);
		}
	}

	int solb = node->value;
	delete node;


	// solution output
	writeSolution(dataSum, solb);
}


