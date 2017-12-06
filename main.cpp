/*
 * main.cpp
 *
 *  Created on: 01.12.2017
 *      Author: mbreit
 */


#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <set>
#include <map>


int main(int argc, char** argv)
{
	int day = 1;
	if (argc >= 2)
		day = atoi(argv[1]);

	switch (day)
	{
		case 1:
		{
			const char* seq = "9513446799636685297929646689682997114316733445451534532351778534251427172168183621874641711534917291674333857423799375512628489423332297538215855176592633692631974822259161766238385922277893623911332569448978771948316155868781496698895492971356383996932885518732997624253678694279666572149831616312497994856288871586777793459926952491318336997159553714584541897294117487641872629796825583725975692264125865827534677223541484795877371955124463989228886498682421539667224963783616245646832154384756663251487668681425754536722827563651327524674183443696227523828832466473538347472991998913211857749878157579176457395375632995576569388455888156465451723693767887681392547189273391948632726499868313747261828186732986628365773728583387184112323696592536446536231376615949825166773536471531487969852535699774113163667286537193767515119362865141925612849443983484245268194842563154567638354645735331855896155142741664246715666899824364722914296492444672653852387389477634257768229772399416521198625393426443499223611843766134883441223328256883497423324753229392393974622181429913535973327323952241674979677481518733692544535323219895684629719868384266425386835539719237716339198485163916562434854579365958111931354576991558771236977242668756782139961638347251644828724786827751748399123668854393894787851872256667336215726674348886747128237416273154988619267824361227888751562445622387695218161341884756795223464751862965655559143779425283154533252573949165492138175581615176611845489857169132936848668646319955661492488428427435269169173654812114842568381636982389224236455633316898178163297452453296667661849622174541778669494388167451186352488555379581934999276412919598411422973399319799937518713422398874326665375216437246445791623283898584648278989674418242112957668397484671119761553847275799873495363759266296477844157237423239163559391553961176475377151369399646747881452252547741718734949967752564774161341784833521492494243662658471121369649641815562327698395293573991648351369767162642763475561544795982183714447737149239846151871434656618825566387329765118727515699213962477996399781652131918996434125559698427945714572488376342126989157872118279163127742349";

			// part a
			const char* iter = seq;
			int suma = 0;
			size_t n = 1;
			while (*++iter)
			{
				if (*iter == *(iter-1))
					suma += *iter - '0';
				++n; // count for length of string (easier for b)
			}

			// do not forget wrapping
			if (*seq == *(iter-1))
				suma += *seq - '0';

			// part b
			int sumb = 0;
			int p = n / 2;
			for (size_t i = 0; i < n; ++i)
			{
				if (seq[i] == seq[(i+p) % n])
					sumb += seq[i] - '0';
			}

			std::cout << "1a: " << suma
				<< "      1b: " << sumb << std::endl;

			break;
		}

		case 2:
		{
			std::ifstream infile("input/input02.dat");
			std::string line;
			int suma = 0;
			int sumb = 0;
			while (std::getline(infile, line))
			{
				std::istringstream iss(line);
				int n = 0;
				int tmp;
				int min = std::numeric_limits<int>::max();
				int max = std::numeric_limits<int>::min();
				while (iss >> tmp)
				{
					++n;

					// part a
					if (tmp > max)
						max = tmp;
					if (tmp < min)
						min = tmp;

					// part b
					std::istringstream iss2(line);
					int m = 0;
					int tmp2;
					while (iss2 >> tmp2)
					{
						++m;
						if (m == n) continue;

						if (tmp%tmp2 == 0)
						{
							sumb += tmp / tmp2;
							//std::cout << "adding " << tmp << " / " << tmp2 << std::endl;
						}
					}
				}
				suma += max - min;
			}

			std::cout << "2a: " << suma
				<< "      1b: " << sumb << std::endl;

			break;
		}

		case 3:
		{
			// part a - solved using only calculator
			int sola = 326;

			// part b
			int x = 0;
			int y = 0;
			int n = 1;
			std::vector<std::vector<int> > mem(101); // looking at the solution, 11 would suffice
			for (size_t i = 0; i < 101; ++i)
				mem[i].resize(101,0);
			mem[50][50] = 1;
			int solb = -1;

			while (true)
			{
				if (y <= x && y <= -x) // new ring and lower side
					x += 1;
				else if (y < x && y >= -x) // right side
					y += 1;
				else if (y >= x && y > -x) // upper side
					x -= 1;
				else
					y -= 1;

				mem[x+50][y+50] += mem[x+49][y+51] + mem[x+50][y+51] + mem[x+51][y+51]
							 	 + mem[x+49][y+50] + mem[x+50][y+50] + mem[x+51][y+50]
							 	 + mem[x+49][y+49] + mem[x+50][y+49] + mem[x+51][y+49];

				if (mem[x+50][y+50] > 361527)
				{
					solb = mem[x+50][y+50];
					break;
				}
				if (x == 49 && y == -49)
					break; // for mem safety;
			}

			std::cout << "3a: " << sola
				<< "      3b: " << solb << std::endl;

			break;
		}

		case 4:
		{
			std::ifstream infile("input/input04.dat");
			std::string line;
			int suma = 0;
			int sumb = 0;
			while (std::getline(infile, line))
			{
				std::istringstream iss(line);

				// part a
				std::set<std::string> passphrase;
				std::string tmp;
				bool valid = true;
				while (iss >> tmp)
				{
					std::pair<std::set<std::string>::iterator, bool> res = passphrase.insert(tmp);
					if (!res.second)
					{
						std::cout << "passphrase invalid" << std::endl;
						valid = false;
						break;
					}
				}

				if (valid) ++suma;

				// part b
				std::vector<std::string> pp;
				valid = true;
				std::istringstream issb(line);
				while (issb >> tmp)
				{
					// compare with each already processed word in phrase
					size_t sz = pp.size();
					for (size_t i = 0; i < sz; ++i)
					{
						const std::string& cur = pp[i];
						size_t nChar = cur.size();

						if (tmp.size() != nChar)
							continue;

						// save all char frequencies in map for current and new string
						std::map<char, size_t> mTmp, mCur;
						for (size_t c = 0; c < nChar; ++c)
						{
							std::map<char, size_t>::iterator itTmp, itCur;

							if ((itTmp = mTmp.find(tmp[c])) != mTmp.end())
								++(itTmp->second);
							else
								mTmp[tmp[c]] = 1;

							if ((itCur = mCur.find(cur[c])) != mCur.end())
								++(itCur->second);
							else
								mCur[cur[c]] = 1;
						}

						// compare frequencies
						bool unequal = false;
						std::map<char, size_t>::const_iterator itTmp = mTmp.begin();
						std::map<char, size_t>::const_iterator itTmpEnd = mTmp.end();
						for (; itTmp != itTmpEnd; ++itTmp)
						{
							char c = itTmp->first;
							size_t cnt = itTmp->second;
							std::map<char, size_t>::iterator itCur;
							if ((itCur = mCur.find(c)) != mCur.end())
							{
								if (itCur->second != cnt)
								{
									unequal = true;
									break;
								}
							}
							else
							{
								unequal = true;
								break;
							}
						}


						if (!unequal)
						{
							valid = false;
							break;
						}
					}

					// if no double entry, add word to phrase; otherwise phrase invalid
					if (valid)
						pp.push_back(tmp);
					else
						break;
				}

				if (valid)
					++sumb;
			}

			std::cout << "4a: " << suma
				<< "      4b: " << sumb << std::endl;

			break;
		}

		case 5:
		{
			// read list
			std::ifstream infile("input/input05.dat");
			int tmp;
			std::vector<int> jumpList;
			jumpList.reserve(1000);
			while (infile >> tmp)
				jumpList.push_back(tmp);

			// make a copy for b
			size_t sz = jumpList.size();
			std::vector<int> jumpListb(jumpList);

			// part a
			size_t nja = 0;
			int* jla = &jumpList[0];
			int* jlb = jla + jumpList.size();
			int* jlp = jla;
			while (jlp < jlb && jlp >= jla)
			{
				++nja;
				jlp += (*jlp)++; // jump-increment
			}

			// part b
			jumpList.swap(jumpListb);
			int njb = 0;
			jla = &jumpList[0];
			jlb = jla + jumpList.size();
			jlp = jla;
			while (jlp < jlb && jlp >= jla)
			{
				++njb;
				int jmp = *jlp;
				*jlp += (*jlp >= 3 ? -1 : 1); // in-/decrement
				jlp += jmp; // jump
			}

			std::cout << "5a: " << nja
				<< "      5b: " << njb << std::endl;

			break;
		}

		case 6:
		{
			// part a and b together (and really brute force)
			int tmp[] = {14, 0, 15, 12, 11, 11, 3, 5, 1, 6, 8, 4, 9, 1, 8, 4};
			std::vector<int> mem(tmp, tmp+16);
			std::vector<std::vector<int> > allStates;
			allStates.reserve(1000);
			allStates.push_back(mem);

			int na = 1;
			int nb;
			while (true)
			{
				// find slot with max.
				int max = mem[0];
				size_t maxInd = 0;
				for (size_t i = 1; i < 16; ++i)
				{
					if (mem[i] > max)
					{
						max = mem[i];
						maxInd = i;
					}
				}

				// distribute
				int forAll = max / 16;
				int rest = max % 16;

				for (size_t i = 0; i < 16; ++i)
					mem[i] += forAll;

				for (size_t i = maxInd+1; i < maxInd+1+rest; ++i)
					++mem[i%16];

				mem[maxInd] = forAll;

				// check reoccurrence
				bool reocc = false;
				for (size_t i = 0; i < allStates.size(); ++i)
				{
					bool same = true;
					for (size_t j = 0; j < 16; ++j)
					{
						if (allStates[i][j] != mem[j])
						{
							same = false;
							break;
						}
					}

					if (same)
					{
						reocc = true;
						nb = na - i;
						break;
					}
				}

				if (reocc) break;

				// save and inc
				allStates.push_back(mem);
				++na;
			}


			// part b




			std::cout << "6a: " << na
				<< "      6b: " << nb << std::endl;

			break;
		}

		default: break;
	}

	return 0;
}

