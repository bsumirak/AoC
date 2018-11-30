/*
 * day18.h
 *
 *  Created on: 18.12.2017
 *      Author: mbreit
 */


template <>
void executeDay<18>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());
	std::string line;

	std::vector<std::string> vInstr;
	vInstr.reserve(100);

	// read data
	while (std::getline(infile, line))
		vInstr.push_back(line);
	size_t sz = vInstr.size();

	// part a
	int sola = -1;
	{
		std::vector<int64_t> reg(16, 0);

		size_t sz = vInstr.size();
		int pos = 0;
		int lastFreq = 0;
		while (pos >= 0 && pos < (int) sz)
		{
			std::istringstream iss(vInstr[pos]);
			std::string instr;

	//std::cout << vInstr[pos] << std::endl;

			iss >> instr;




			std::string next;
			iss >> next;

			int arg1I;
			bool arg1IsReg = true;
			if (next[0] - 'a' < 16 && next[0] - 'a' >= 0)
			{
				arg1I = next[0] - 'a';
				arg1IsReg = true;
			}
			else
			{
				arg1I = std::stoi(next);
				arg1IsReg = false;
			}



			int arg2I;
			bool arg2IsReg = false;
			if (instr != "snd" && instr != "rcv")
			{
				iss >> next;
				if (next[0] - 'a' < 16 && next[0] - 'a' >= 0)
				{
					arg2I = next[0] - 'a';
					arg2IsReg = true;
				}
				else
				{
					arg2I = std::stoi(next);
					arg2IsReg = false;
				}
			}

//std::cout << instr << " " << (arg1IsReg ? "r" : "") << arg1I << " " << (arg2IsReg ? "r" : "") << arg2I << std::endl;




			if (instr == "snd")
			{
				if (arg1IsReg)
					lastFreq = reg[arg1I];
				else
					lastFreq = arg1I;
			}
			else if (instr == "set")
			{
				if (arg2IsReg)
					reg[arg1I] = reg[arg2I];
				else
					reg[arg1I] = arg2I;
			}
			else if (instr == "add")
			{
				if (arg2IsReg)
					reg[arg1I] = reg[arg1I] + reg[arg2I];
				else
					reg[arg1I] = reg[arg1I] + arg2I;
			}
			else if (instr == "mul")
			{
				if (arg2IsReg)
					reg[arg1I] = reg[arg1I] * reg[arg2I];
				else
					reg[arg1I] = reg[arg1I] * arg2I;
			}
			else if (instr == "mod")
			{
				if (arg2IsReg)
					reg[arg1I] = reg[arg1I] % reg[arg2I];
				else
					reg[arg1I] = reg[arg1I] % arg2I;
			}
			else if (instr == "rcv")
			{
				if (reg[arg1I])
				{
					sola = lastFreq;
					reg[arg1I] = lastFreq;
					break;
				}
			}
			else if (instr == "jgz")
			{
				if (arg1IsReg)
				{
					if (reg[arg1I] > 0)
					{
						if (arg2IsReg)
							pos = pos + reg[arg2I] - 1;
						else
							pos = pos + arg2I - 1;
					}
				}
				else
				{
					if (arg1I > 0)
					{
						if (arg2IsReg)
							pos = pos + reg[arg2I] - 1;
						else
							pos = pos + arg2I - 1;
					}
				}
			}
			else throw;

			++pos;
		}
	}


	//part b
	int p1SendCnt = 0;
	{
		std::vector<int64_t> reg0(16, 0);
		std::vector<int64_t> reg1(16, 1);

		std::queue<int64_t> q0, q1;

		int pos0 = 0;
		int pos1 = 0;

		int lastFreq0 = 0;
		int lastFreq1 = 0;

		bool bWait0 = false;
		bool bWait1 = false;
		bool bTerm0 = false;
		bool bTerm1 = false;

		while (!bTerm0 || !bTerm1)
		{
			if (!bTerm0)
			{
				std::istringstream iss0(vInstr[pos0]);
				std::string instr0, instr1;
				iss0 >> instr0;
				std::string arg10, arg20;

				iss0 >> arg10;
				int arg10I;
				bool arg10IsReg = true;
				if (arg10[0] - 'a' < 16 && arg10[0] - 'a' >= 0)
				{
					arg10I = arg10[0] - 'a';
					arg10IsReg = true;
				}
				else
				{
					arg10I = std::stoi(arg10);
					arg10IsReg = false;
				}

				int arg20I;
				bool arg20IsReg = false;
				if (instr0 != "snd" && instr0 != "rcv")
				{
					iss0 >> arg20;
					if (arg20[0] - 'a' < 16 && arg20[0] - 'a' >= 0)
					{
						arg20I = arg20[0] - 'a';
						arg20IsReg = true;
					}
					else
					{
						arg20I = std::stoi(arg20);
						arg20IsReg = false;
					}
				}


				if (instr0 == "snd")
				{
					if (arg10IsReg)
						q1.push(reg0[arg10I]);
					else
						q1.push(arg10I);

					bWait1 = false;
				}
				else if (instr0 == "set")
				{
					if (arg20IsReg)
						reg0[arg10I] = reg0[arg20I];
					else
						reg0[arg10I] = arg20I;
				}
				else if (instr0 == "add")
				{
					if (arg20IsReg)
						reg0[arg10I] = reg0[arg10I] + reg0[arg20I];
					else
						reg0[arg10I] = reg0[arg10I] + arg20I;
				}
				else if (instr0 == "mul")
				{
					if (arg20IsReg)
						reg0[arg10I] = reg0[arg10I] * reg0[arg20I];
					else
						reg0[arg10I] = reg0[arg10I] * arg20I;
				}
				else if (instr0 == "mod")
				{
					if (arg20IsReg)
						reg0[arg10I] = reg0[arg10I] % reg0[arg20I];
					else
						reg0[arg10I] = reg0[arg10I] % arg20I;
				}
				else if (instr0 == "rcv")
				{
					if (q0.size())
					{
						reg0[arg10I] = q0.front();
						q0.pop();
					}
					else
						bWait0 = true;
				}
				else if (instr0 == "jgz")
				{
					if (arg10IsReg)
					{
						if (reg0[arg10I] > 0)
						{
							if (arg20IsReg)
								pos0 = pos0 + reg0[arg20I] - 1;
							else
								pos0 = pos0 + arg20I - 1;
						}
					}
					else
					{
						if (arg10I > 0)
						{
							if (arg20IsReg)
								pos0 = pos0 + reg0[arg20I] - 1;
							else
								pos0 = pos0 + arg20I - 1;
						}
					}
				}
				else throw;

				if (!bWait0)
					++pos0;

				if (pos0 < 0 || pos0 >= (int) sz)
					bTerm0 = true;
			}


			if (!bTerm1)
			{
				std::istringstream iss1(vInstr[pos1]);
				std::string instr1;
				iss1 >> instr1;
				std::string arg11, arg21;

				iss1 >> arg11;
				int arg11I;
				bool arg11IsReg = true;
				if (arg11[0] - 'a' < 16 && arg11[0] - 'a' >= 0)
				{
					arg11I = arg11[0] - 'a';
					arg11IsReg = true;
				}
				else
				{
					arg11I = std::stoi(arg11);
					arg11IsReg = false;
				}

				int arg21I;
				bool arg21IsReg = false;
				if (instr1 != "snd" && instr1 != "rcv")
				{
					iss1 >> arg21;
					if (arg21[0] - 'a' < 16 && arg21[0] - 'a' >= 0)
					{
						arg21I = arg21[0] - 'a';
						arg21IsReg = true;
					}
					else
					{
						arg21I = std::stoi(arg21);
						arg21IsReg = false;
					}
				}

				if (instr1 == "snd")
				{
					if (arg11IsReg)
						q0.push(reg1[arg11I]);
					else
						q0.push(arg11I);

					bWait0 = false;
					++p1SendCnt;
				}
				else if (instr1 == "set")
				{
					if (arg21IsReg)
						reg1[arg11I] = reg1[arg21I];
					else
						reg1[arg11I] = arg21I;
				}
				else if (instr1 == "add")
				{
					if (arg21IsReg)
						reg1[arg11I] = reg1[arg11I] + reg1[arg21I];
					else
						reg1[arg11I] = reg1[arg11I] + arg21I;
				}
				else if (instr1 == "mul")
				{
					if (arg21IsReg)
						reg1[arg11I] = reg1[arg11I] * reg1[arg21I];
					else
						reg1[arg11I] = reg1[arg11I] * arg21I;
				}
				else if (instr1 == "mod")
				{
					if (arg21IsReg)
						reg1[arg11I] = reg1[arg11I] % reg1[arg21I];
					else
						reg1[arg11I] = reg1[arg11I] % arg21I;
				}
				else if (instr1 == "rcv")
				{
					if (q1.size())
					{
						reg1[arg11I] = q1.front();
						q1.pop();
					}
					else
						bWait1 = true;
				}
				else if (instr1 == "jgz")
				{
					if (arg11IsReg)
					{
						if (reg1[arg11I] > 0)
						{
							if (arg21IsReg)
								pos1 = pos1 + reg1[arg21I] - 1;
							else
								pos1 = pos1 + arg21I - 1;
						}
					}
					else
					{
						if (arg11I > 0)
						{
							if (arg21IsReg)
								pos1 = pos1 + reg1[arg21I] - 1;
							else
								pos1 = pos1 + arg21I - 1;
						}
					}
				}
				else throw;

				if (!bWait1)
					++pos1;

				if (pos1 < 0 || pos1 >= (int) sz)
					bTerm1 = true;
			}


			if ((bTerm0 && bWait1) || (bTerm1 && bWait0))
			{
				std::cout << "Wait while other terminated." << std::endl;
				throw;
			}

			if (bWait0 && bWait1)
				break;
		}
	}


	writeSolution(sola, p1SendCnt);
}


