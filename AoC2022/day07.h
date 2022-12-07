/*
 * day07.h
 *
 *  Created on: 2022-12-07
 *      Author: mbreit
 */

struct Node7
{
	std::string name;
	std::uint64_t sz;

	Node7* parent;

	bool isDir;
	std::vector<Node7*> inv;
};


std::uint64_t computeSize(Node7* dir, std::uint64_t& total)
{
	std::uint64_t sz = 0;

	for (Node7* item : dir->inv)
	{
		if (!item->isDir)
			sz += item->sz;
		else
		{
			auto dirSz = computeSize(item, total);
			if (dirSz <= 100000)
				total += dirSz;
			sz += dirSz;
		}
	}

	return sz;
}

std::uint64_t findBest(Node7* dir, std::uint64_t req, std::uint64_t& bestSz)
{
	std::uint64_t sz = 0;

	for (Node7* item : dir->inv)
	{
		if (!item->isDir)
			sz += item->sz;
		else
		{
			auto dirSz = findBest(item, req, bestSz);
			if (dirSz >= req && dirSz < bestSz)
				bestSz = dirSz;
			sz += dirSz;
		}
	}

	return sz;
}

#if 0
void print7(Node7* dir, unsigned offset = 0)
{
	std::cout << std::string(offset, ' ') << "- " << dir->name << std::endl;

	offset += 2;
	for (Node7* item : dir->inv)
	{
		if (item->isDir)
			print7(item, offset);
		else
		{
			std::cout << std::string(offset, ' ') << "- " << item->name
				<< " (" << item->sz << ")" << std::endl;
		}
	}
	offset -= 2;
}
#endif


template <>
void executeDay<7>(const std::string& fn)
{
	Node7* root = new Node7{"/", 0, nullptr, true, std::vector<Node7*>()};

	Node7* currDir = nullptr;

	unsigned state = 0;

	// read input
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		while (std::getline(infile, line))
		{
			if (line.empty())
				break;

			if (line[0] == '$')
			{
				state = 0;
				std::istringstream iss(line);
				std::string s;
				iss >> s;
				iss >> s;
				if (s == "cd")
				{
					iss >> s;
					if (s == "/")
						currDir = root;
					else if (s == "..")
					{
						if (currDir->parent != nullptr)
							currDir = currDir->parent;
						else
							std::cout << "going to non-existent parent dir!" << std::endl;
					}
					else
					{
						const auto it = std::find_if(currDir->inv.begin(), currDir->inv.end(),
							[&](Node7* node){return node->name == s;});
						if (it != currDir->inv.end())
							currDir = *it;
						else
							std::cout << "going into unknown dir!" << std::endl;
					}
				}
				else if (s == "ls")
				{
					// do nothing
					state = 1;
				}
			}
			else if (line[0] == 'd')
			{
				std::istringstream iss(line);
				std::string s;
				iss >> s;
				iss >> s;
				const auto it = std::find_if(currDir->inv.begin(), currDir->inv.end(),
					[&](Node7* node){return node->name == s && node->isDir;});
				if (it == currDir->inv.end())
					currDir->inv.push_back(new Node7{s, 0, currDir, true, std::vector<Node7*>()});
				else
					std::cout << "ignoring ls item that is already known" << std::endl;
			}
			else
			{
				std::istringstream iss(line);
				std::uint64_t sz;
				iss >> sz;
				std::string name;
				iss >> name;
				const auto it = std::find_if(currDir->inv.begin(), currDir->inv.end(),
					[&](Node7* node){return node->name == name && !node->isDir;});
				if (it == currDir->inv.end())
					currDir->inv.push_back(new Node7{name, sz, currDir, false, std::vector<Node7*>()});
				else
					std::cout << "ignoring ls item that is already known" << std::endl;
			}
		}
		infile.close();
	}

	//print7(root);

	// part a
	std::uint64_t resA = 0;
	const auto rootSz = computeSize(root, resA);
	if (rootSz < 100000)
		resA += rootSz;

	// part b
	const std::uint64_t reqSpace = 30000000 - (70000000 - rootSz);
	std::uint64_t resB = rootSz;
	findBest(root, reqSpace, resB);


	writeSolution(resA, resB);
}


