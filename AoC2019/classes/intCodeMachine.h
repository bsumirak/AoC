/*
 * intCodeMachine.h
 *
 *  Created on: Dec 7, 2019
 *      Author: mbreit
 */

#ifndef CLASSES_INTCODEMACHINE_H
#define CLASSES_INTCODEMACHINE_H


#include <cstdlib>
#include <vector>


template <typename TPrecision = int>
class IntCodeMachine
{
public:
	typedef TPrecision tPrec;

	enum State
	{
		ICMS_INSTRUCTION_PTR_OOB = 0,
		ICMS_ILLEGAL_INSTRUCTION,
		ICMS_WAITING_FOR_INPUT,
		ICMS_READY,
		ICMS_UNDF
	};

	IntCodeMachine();
	IntCodeMachine(const std::vector<tPrec>& opCode);

	void setOpCode(const std::vector<tPrec>& opCode);

	void setHaltOnInput(bool b);

	void execute
	(
		const std::vector<tPrec> vInputs,
		std::vector<tPrec>& vOutputs
	);

	State state() const;

private:
	void extractParamMode(std::vector<tPrec>& vModes, const tPrec& opCode);

	std::vector<tPrec> m_opCode;
	tPrec* m_ip;

	State m_state;

	bool m_bHaltOnOutput;
};

#endif  // CLASSES_INTCODEMACHINE_H
