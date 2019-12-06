/*
 * day07.h
 *
 *  Created on: 07.12.2017
 *      Author: mbreit
 */

struct node7
{
	~node7()
	{
		size_t sz = children.size();
		for (size_t i = 0; i < sz; ++i)
			delete children[i];
	}

	std::string name;
	std::vector<node7*> children;
	node7* parent;
	int weight;
	int totalWeight;
};


void build_tree7
(
	std::map<std::string, int>& weights,
	std::map<std::string, std::vector<std::string> >& children,
	std::map<std::string, std::string>& parent,
	node7* root
)
{
	const std::vector<std::string>& vCh = children[root->name];
	size_t sz = vCh.size();
	for (size_t i = 0; i < sz; ++i)
	{
		// set name, weight and parent by parent
		node7* ch = new node7();
		ch->name = vCh[i];
		ch->weight = weights[ch->name];
		ch->parent = root;

		// add child to parent
		root->children.push_back(ch);

		// recurse
		build_tree7(weights, children, parent, ch);
	}

	// add weights of children to totalWeight
	root->totalWeight = root->weight;
	for (size_t i = 0; i < sz; ++i)
		root->totalWeight += root->children[i]->totalWeight;
}

bool isEquilibrated(node7* node)
{
	size_t sz = node->children.size();
	if (!sz) return true;

	int w = node->children[0]->totalWeight;
	for (size_t i = 1; i < sz; ++i)
	{
		if (node->children[i]->totalWeight != w)
			return false;
	}
	return true;
}




template <>
void executeDay<7>(const std::string& fn)
{
	// read input
	std::ifstream infile(fn.c_str());
	std::string line;
	std::map<std::string, int> weights;
	std::map<std::string, std::vector<std::string> > children;
	std::map<std::string, std::string> parent;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		std::set<std::string> passphrase;
		std::string tmp;
		bool valid = true;

		std::string name;
		iss >> name;
		std::string weight;
		iss >> weight;
		tmp = weight.substr(1, weight.size()-2);
		int w = atoi(tmp.c_str());

		weights[name] = w;

		int cnt = 0;
		while (iss >> tmp)
		{
			// ignore "->"
			if (!cnt)
			{
				++cnt;
				continue;
			}

			// remove comma
			if (tmp.c_str()[tmp.size()-1] == ',')
				tmp = tmp.substr(0,tmp.size()-1);

			children[name].push_back(tmp);
			parent[tmp] = name;
		}
	}

	// part a
	std::map<std::string, std::string>::const_iterator it = parent.begin();
	while (parent.find(it->second) != parent.end())
		it = parent.find(it->second);
	std::string rootName = it->second;

	// part b

	// build a tree
	node7 root;
	root.name = rootName;
	root.weight = weights[rootName];
	root.parent = NULL;
	build_tree7(weights, children, parent, &root);

	// find deepest uneven weight
	node7* node = &root;
	while (true)
	{
		bool equiChild = true;
		size_t sz = node->children.size();
		for (size_t i = 0; i < sz; ++i)
		{
			if (!isEquilibrated(node->children[i]))
			{
				node = node->children[i];
				equiChild = false;
				break;
			}
		}

		if (equiChild)
			break;
	}

	// now we are in the child with the wrong weight

	if (node->children.size() == 2)
		std::cout << "This case is not implemented." << std::endl;

	size_t culprit;
	size_t sz = node->children.size();
	for (size_t i = 0; i < sz-1; ++i)
	{
		if (node->children[i]->totalWeight != node->children[i+1]->totalWeight)
		{
			// which one of the two is the culprit?
			if (i > 0)
			{
				if (node->children[i]->totalWeight != node->children[0]->totalWeight)
					culprit = i;
				else
					culprit = i+1;
			}
			else
			{
				if (node->children[0]->totalWeight != node->children[2]->totalWeight)
					culprit = 0;
				else
					culprit = 1;
			}

			break;
		}
	}

	int totW = node->children[culprit]->totalWeight;
	int reqTotW = node->children[(culprit+1) % 2]->totalWeight;

	int reqW = reqTotW - (node->children[culprit]->totalWeight - node->children[culprit]->weight);

	/*
	std::cout << "unequilibrated node: " << node->name << std::endl;
	std::cout << "  with children: ";
	for (size_t i = 0; i < sz; ++i)
		std::cout << node->children[i]->name << " (" << node->children[i]->totalWeight << ")   ";
	std::cout << std::endl;
	std::cout << "culprit: " << node->children[culprit]->name << " with own weight "
		<< node->children[culprit]->weight << std::endl;
	std::cout << std::endl;
	*/

	writeSolution(rootName, reqW);
}
