/*
 * day05.h
 *
 *  Created on: 2019-12-05
 *      Author: mbreit
 */


void runProgram5
(
	std::vector<int>& opCode,
	std::vector<int>& vOutputs,
	const std::vector<int>* pvUserInputs = NULL
)
{
	std::size_t userInput = 0;
	int* instr = &opCode[0];

	auto extractParamMode = [] (std::vector<int>& vModes, int& opCode) -> void
	{
		int restoreOC = opCode % 100;
		opCode /= 100;
		const std::size_t nModes = vModes.size();
		for (std::size_t i = 0; i < nModes; ++i)
		{
			vModes[i] = opCode % 10;
			opCode /= 10;
		}
		opCode = restoreOC;
	};

	std::vector<int> vModes(2);
	bool doBreak = false;
	while (!doBreak)
	{
		//std::cout << *instr << " ";
		extractParamMode(vModes, *instr);
		//std::cout << vModes[0] << "," << vModes[1] << " " << *instr << std::endl;

		switch (*instr)
		{
			case 1:
			{
				int sum = vModes[0] ? *++instr : opCode[*++instr];
				sum += vModes[1] ? *++instr : opCode[*++instr];
				opCode[*++instr] = sum;
				break;
			}
			case 2:
			{
				int prod = vModes[0] ? *++instr : opCode[*++instr];
				prod *= vModes[1] ? *++instr : opCode[*++instr];
				opCode[*++instr] = prod;
				break;
			}
			case 3:
			{
				if (pvUserInputs && userInput < pvUserInputs->size())
				{
					opCode[*++instr] = (*pvUserInputs)[userInput];
					++userInput;
				}
				else
				{
					std::cout << "Program requested user input no. " << userInput
						<< ", but only " << pvUserInputs->size() << " are provided.";
					throw std::runtime_error("Invalid input.");
				}
				break;
			}
			case 4:
			{
				vOutputs.push_back((vModes[0] ? *++instr : opCode[*++instr]));
				break;
			}
			case 5: // jmp if true
			{
				if (vModes[0] ? *++instr : opCode[*++instr])
				{
					int* nextInstr = &opCode[vModes[1] ? *++instr : opCode[*++instr]]-1;
					instr = nextInstr;
				}
				else
					++instr;
				break;
			}
			case 6: // jmp if false
			{

				if (!(vModes[0] ? *++instr : opCode[*++instr]))
				{
					int* nextInstr = &opCode[vModes[1] ? *++instr : opCode[*++instr]]-1;
					instr = nextInstr;
				}
				else
					++instr;
				break;
			}
			case 7: // less than
			{
				int val0 = vModes[0] ? *++instr : opCode[*++instr];
				int val1 = vModes[1] ? *++instr : opCode[*++instr];
				opCode[*++instr] = (val0 < val1) ? 1 : 0;
				break;
			}
			case 8: //  equal
			{
				int val0 = vModes[0] ? *++instr : opCode[*++instr];
				int val1 = vModes[1] ? *++instr : opCode[*++instr];
				opCode[*++instr] = (val0 == val1) ? 1 : 0;
				break;
			}

			case 99:
				doBreak = true;
				break;

			default:
				std::cout << "Wrong op code: " << *instr << "." << std::endl;
				throw new std::runtime_error("Wrong op.");
		}
		++instr;
	}
}


template <>
void executeDay<5>(const std::string& fn)
{
	std::vector<int> opCode;

	// read program
	{
		std::ifstream infile(fn.c_str());
		int id;
		while (infile >> id)
			opCode.push_back(id);
	}
	std::vector<int> vCopy = opCode;


	// part a
	int sola = 0;
	std::vector<int> inputs(1, 1);
	std::vector<int> outputs;
	runProgram5(opCode, outputs, &inputs);
	if (!outputs.size())
		std::cout << "Program did not return output in part a." << std::endl;
	else
		sola = outputs.back();

	// part b
	int solb = 0;
	inputs[0] = 5;
	outputs.clear();
	opCode.swap(vCopy);
	runProgram5(opCode, outputs, &inputs);
	if (!outputs.size())
		std::cout << "Program did not return output in part b." << std::endl;
	else
		solb = outputs.back();

	writeSolution(sola, solb);
}


