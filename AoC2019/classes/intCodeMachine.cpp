/*
 * intCodeMachine.cpp
 *
 *  Created on: Dec 7, 2019
 *      Author: mbreit
 */

#include "intCodeMachine.h"

#include <iostream>
#include <limits>
#include <algorithm>


template <typename TPrecision>
IntCodeMachine<TPrecision>::IntCodeMachine() :
	m_ip(NULL),
	m_state(ICMS_UNDF),
	m_bHaltOnOutput(false)
{}


template <typename TPrecision>
IntCodeMachine<TPrecision>::IntCodeMachine(const std::vector<tPrec>& opCode) :
	m_opCode(opCode),
	m_ip(&opCode[0]),
	m_state(ICMS_UNDF),
	m_bHaltOnOutput(false)
{}


template <typename TPrecision>
void IntCodeMachine<TPrecision>::setOpCode(const std::vector<tPrec>& opCode)
{
	m_opCode = opCode;
	m_ip = &opCode[0];
}


template <typename TPrecision>
void IntCodeMachine<TPrecision>::setHaltOnInput(bool b)
{
	m_bHaltOnOutput = b;
}


template <typename TPrecision>
void IntCodeMachine<TPrecision>::execute
(
	const std::vector<tPrec> vInputs,
	std::vector<tPrec>& vOutputs
)
{
	std::size_t userInput = 0;

	std::vector<tPrec> vModes(2);
	bool doBreak = false;
	while (!doBreak)
	{
		if (std::size_t(m_ip - &m_opCode[0]) >= m_opCode.size())
		{
			m_state = ICMS_INSTRUCTION_PTR_OOB;
			break;
		}

		//std::cout << *m_ip << " ";
		extractParamMode(vModes, *m_ip);
		//std::cout << vModes[0] << "," << vModes[1] << " " << *m_ip << std::endl;

		switch (*m_ip)
		{
			case 1:
			{
				tPrec sum = vModes[0] ? *++m_ip : m_opCode[*++m_ip];
				sum += vModes[1] ? *++m_ip : m_opCode[*++m_ip];
				m_opCode[*++m_ip] = sum;
				break;
			}
			case 2:
			{
				tPrec prod = vModes[0] ? *++m_ip : m_opCode[*++m_ip];
				prod *= vModes[1] ? *++m_ip : m_opCode[*++m_ip];
				m_opCode[*++m_ip] = prod;
				break;
			}
			case 3:
			{
				if (userInput < vInputs->size())
				{
					m_opCode[*++m_ip] = (*vInputs)[userInput];
					++userInput;
				}
				else
				{
					std::cout << "Program requested user input no. " << userInput
						<< ", but only " << vInputs->size() << " are provided.";
					m_state = ICMS_WAITING_FOR_INPUT;
				}
				break;
			}
			case 4:
			{
				vOutputs.push_back((vModes[0] ? *++m_ip : m_opCode[*++m_ip]));
				if (m_bHaltOnOutput)
					doBreak = true;
				break;
			}
			case 5: // jmp if true
			{
				if (vModes[0] ? *++m_ip : m_opCode[*++m_ip])
					m_ip = &m_opCode[vModes[1] ? *++m_ip : m_opCode[*++m_ip]]-1;
				else
					++m_ip;
				break;
			}
			case 6: // jmp if false
			{

				if (!(vModes[0] ? *++m_ip : m_opCode[*++m_ip]))
					m_ip = &m_opCode[vModes[1] ? *++m_ip : m_opCode[*++m_ip]]-1;
				else
					++m_ip;
				break;
			}
			case 7: // less than
			{
				tPrec val0 = vModes[0] ? *++m_ip : m_opCode[*++m_ip];
				tPrec val1 = vModes[1] ? *++m_ip : m_opCode[*++m_ip];
				m_opCode[*++m_ip] = (val0 < val1) ? 1 : 0;
				break;
			}
			case 8: //  equal
			{
				tPrec val0 = vModes[0] ? *++m_ip : m_opCode[*++m_ip];
				tPrec val1 = vModes[1] ? *++m_ip : m_opCode[*++m_ip];
				m_opCode[*++m_ip] = (val0 == val1) ? 1 : 0;
				break;
			}

			case 99:
				doBreak = true;
				break;

			default:
				std::cout << "Wrong op code: " << *m_ip << "." << std::endl;
				m_state = ICMS_ILLEGAL_INSTRUCTION;
				doBreak = true;
		}
		++m_ip;
	}
}


template <typename TPrecision>
auto IntCodeMachine<TPrecision>::state() const -> State
{
	return m_state;
}


template <typename TPrecision>
void IntCodeMachine<TPrecision>::extractParamMode(std::vector<tPrec>& vModes, const tPrec& opCode)
{
	tPrec opCodeCp = opCode;
	tPrec restoreOC = opCodeCp % 100;
	opCodeCp /= 100;
	const std::size_t nModes = vModes.size();
	for (std::size_t i = 0; i < nModes; ++i)
	{
		vModes[i] = opCodeCp % 10;
		opCodeCp /= 10;
	}
}

