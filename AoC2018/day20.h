/*
 * day20.h
 *
 *  Created on: 2019-01-05
 *      Author: mbreit
 */


struct PathNode
{
/*
	~PathNode()
	{
		const size_t sz = vC.size();
		for (size_t i = 0; i < sz; ++i)
			delete vC[i];
	}
*/

	std::string dirs;
	std::vector<PathNode*> vC;
};

struct Room
{
/*
	~Room()
	{
		const size_t sz = vAdj.size();
		for (size_t i = 0; i < sz; ++i)
			delete vAdj[i];
	}
*/

	std::vector<Room*> vAdj;
};


struct ReadPathStackFrame
{
	ReadPathStackFrame(PathNode* _pn)
	: pn(_pn) {}

	PathNode* pn;
	std::vector<PathNode*> vOpenEnds;
};


void printPathTree(PathNode* node, int lv = 0)
{
	std::cout << std::string(2*lv, ' ') << node->dirs << std::endl;
	const size_t sz = node->vC.size();
	for (size_t k = 0; k < sz; ++k)
		printPathTree(node->vC[k], lv+1);
}




template <>
void executeDay<20>(const std::string& fn)
{
	typedef std::pair<int, int> ivec2;

	// read input
	std::ifstream infile(fn.c_str());
	std::string pathRegex;
	infile >> pathRegex;

	PathNode* root = new PathNode();
	PathNode* node = root;

	std::stack<ReadPathStackFrame*> stack;

	size_t i = 0;
	bool doBreak = false;
	while (++i)
	{
		switch (pathRegex[i])
		{
			case '$':
			{
				doBreak = true;
				break;
			}
			case 'N':
			case 'E':
			case 'S':
			case 'W':
			{
				node->dirs += pathRegex[i];
				break;
			}
			case '(':
			{
				stack.push(new ReadPathStackFrame(node));
				PathNode* next = new PathNode();
				node->vC.push_back(next);
				node = next;
				break;
			}
			case ')':
			{
				PathNode* next = new PathNode();

				// close open ends
				const size_t sz = stack.top()->vOpenEnds.size();
				for (size_t k = 0; k < sz; ++k)
					stack.top()->vOpenEnds[k]->vC.push_back(next);
				node->vC.push_back(next);

				delete stack.top();
				stack.pop();

				node = next;
				break;
			}
			case '|':
			{
				PathNode* parent = stack.top()->pn;
				PathNode* next = new PathNode();
				parent->vC.push_back(next);
				stack.top()->vOpenEnds.push_back(node);
				node = next;
				break;
			}
			default:
			{
				std::cout << "Unexpected character '" << pathRegex[i] << "'." << std::endl;
				exit(1);
			}
		}

		if (doBreak)
			break;
	}

//printPathTree(root);


	// create graph of rooms from paths
	Room* startRoom = new Room();
	{
		std::map<ivec2, Room*> coord2Graph;
		coord2Graph[ivec2(0,0)] = startRoom;

		std::set<std::pair<PathNode*, ivec2> > lookupMap;

		std::stack<std::pair<PathNode*, ivec2> > workStack;
		workStack.push(std::make_pair(root, ivec2(0,0)));
		while (!workStack.empty())
		{
			node = workStack.top().first;
			ivec2 coords = workStack.top().second;
			workStack.pop();

			Room* curRoom = coord2Graph[coords];

			const std::string& dirs = node->dirs;
			size_t sz = dirs.size();

			for (size_t k = 0; k < sz; ++k)
			{
				ivec2 newCoords = coords;
				switch (dirs[k])
				{
					case 'N':
						++newCoords.second;
						break;
					case 'E':
						++newCoords.first;
						break;
					case 'S':
						--newCoords.second;
						break;
					case 'W':
						--newCoords.first;
						break;
					default:
						std::cout << "Unexpected direction '" << dirs[k] << "'." << std::endl;
						exit(1);
				}

				Room* nextRoom;
				std::map<ivec2, Room*>::iterator it = coord2Graph.lower_bound(newCoords);
				if (it != coord2Graph.end() && !coord2Graph.key_comp()(newCoords, it->first))
					nextRoom = it->second;
				else
				{
					nextRoom = new Room();
					coord2Graph.insert(it, std::map<ivec2, Room*>::value_type(newCoords, nextRoom));
				}

				// make edges between adjacent rooms
				size_t adjSz = nextRoom->vAdj.size();
				size_t l = 0;
				for (; l < adjSz; ++l)
					if (nextRoom->vAdj[l] == curRoom)
						break;
				if (l == adjSz)
					nextRoom->vAdj.push_back(curRoom);

				adjSz = curRoom->vAdj.size();
				l = 0;
				for (; l < adjSz; ++l)
					if (curRoom->vAdj[l] == nextRoom)
						break;
				if (l == adjSz)
					curRoom->vAdj.push_back(nextRoom);


				curRoom = nextRoom;
				coords = newCoords;
			}

			sz = node->vC.size();
			for (size_t k = 0; k < sz; ++k)
			{
				std::pair<PathNode*, ivec2> nextPair(node->vC[k], coords);
				std::pair<std::set<std::pair<PathNode*, ivec2> >::iterator, bool> res = lookupMap.insert(nextPair);
				if (res.second)
					workStack.push(nextPair);
			}
		}

		//delete root;
	}

	// now do a breadth-first search; the last room found is the one we are looking for
	int maxDoors = 0;

	std::map<Room*, int> doorsToRoom;

	std::queue<std::pair<Room*, int> > q;
	q.push(std::make_pair(startRoom, 0));
	while (!q.empty())
	{
		Room* room = q.front().first;
		std::map<Room*, int>::iterator it = doorsToRoom.find(room);
		if (it != doorsToRoom.end())
		{
			q.pop();
			continue;
		}

		int lvl = q.front().second;
		q.pop();

		maxDoors = std::max(maxDoors, lvl);
		doorsToRoom[room] = lvl;

		const size_t sz = room->vAdj.size();
		for (size_t k = 0; k < sz; ++k)
			q.push(std::make_pair(room->vAdj[k], lvl+1));
	}


	// part b
	int n1000 = 0;
	std::map<Room*, int>::iterator it = doorsToRoom.begin();
	std::map<Room*, int>::iterator itEnd = doorsToRoom.end();
	for (; it != itEnd; ++it)
		if (it->second >= 1000)
			++n1000;

	writeSolution(maxDoors, n1000);
}


