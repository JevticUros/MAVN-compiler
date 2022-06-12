#include "IR.h"

#include <iostream>

using namespace std;
/*Variable getters*/
string Variable::GetName()
{
	return m_name;
}

int Variable::getValue()
{
	return mem_value;
}

int Variable::getPosition()
{
	return m_position;
}

Regs Variable::getAssignment()
{
	return m_assignment;
}
/*Variable setters*/

void Variable::setAssigment(Regs reg)
{
	m_assignment = reg;
}

/*Instruction getters*/
Variables Instruction::getDst()
{
	return m_dst;
}
Variables Instruction::getSrc()
{
	return m_src;
}
Variables Instruction::getOut()
{
	return m_out;
}
Variables Instruction::getIn()
{
	return m_in;
}
Variables Instruction::getUse()
{
	return m_use;
}
Variables Instruction::getDef()
{
	return m_def;
}
list<Instruction*> Instruction::getSucc()
{
	return m_succ;
}
list<Instruction*> Instruction::getPred()
{
	return m_pred;
}

/*Instruction setters*/
void Instruction::setSucc(Instruction* succ)
{
	m_succ.push_back(succ);
}

void Instruction::setPred(Instruction* pred)
{
	m_pred.push_back(pred);
}

int Instruction::getPosition()
{
	return m_position;
}

InstructionType Instruction::getType()
{
	return m_type;
}

void Instruction::fillUseDefVariables()
{
	switch (m_type)
	{
	case I_ADD:
	case I_SUB:
	case I_ADDI:
	case I_OR:
	case I_NOR:
		for (Variables::iterator it = m_src.begin(); it != m_src.end(); it++)
		{
			m_use.push_back((*it));
		}
		for (Variables::iterator it = m_dst.begin(); it != m_dst.end(); it++)
		{
			m_def.push_back((*it));
		}
		break;
	case I_LA: // la rid,mid
	case I_LI: // li rid,num
	case I_LW: // lw rid,num(rid)
	case I_SW: // sw rid,num(rid)
		for (Variables::iterator it = m_dst.begin(); it != m_dst.end(); it++)
		{
			m_def.push_back((*it));
		}
		break;
	case I_BLTZ: // bltz rid,id
		for (Variables::iterator it = m_src.begin(); it != m_src.end(); it++)
		{
			m_use.push_back((*it));
		}
		break;
	}
}


/*void LivenessAnalysis(Instructions& instructions)
{
	bool again = true;
	while (again)
	{
		again = false;

		for (Instructions::reverse_iterator it = instructions.rbegin();
			it != instructions.rend();
			it++)
		{
			Variables newOut, newIn;
			Variables& out = (*it)->getOut();
			Variables& in = (*it)->getIn();

			// Creating newOut
			Instructions& successors = (*it)->getSucc();
			for (Instructions::iterator succIt = successors.begin();
				succIt != successors.end();
				succIt++)
			{
				Variables& succIn = (*succIt)->getIn();
				newOut.insert(newOut.end(), succIn.begin(), succIn.end());
			}

			newOut.sort();
			newOut.unique();

			// Creating newIn
			Variables& use = (*it)->getUse();
			Variables& def = (*it)->getDef();
			Variables outMinusDef;

			// newIn = use and newIn.insert(outMinusDef) and unique are a way to do union
			newIn = use;
			newIn.insert(newIn.end(), outMinusDef.begin(), outMinusDef.end());
			newIn.sort();
			newIn.unique();

			// Repeat condition
			if (newIn != in || newOut != out)
				again = true;

			in = newIn;
			out = newOut;
		}
	}
}

*/

/*void PrintInstructions(Instructions& instructions, ofstream& Mfile)
{
	for (std::list<Instruction*>::iterator it = instructions.begin(); it != instructions.end(); it++)
	{
		Variables dst = (*it)->getDst();
		Variables src = (*it)->getSrc();
		InstructionType type = (*it)->getType();
		string pom;
		if(type == I_ADD)
		{
			Mfile << "$add ";
		}
		else if (type == I_SUB)
		{
			cout << "$sub ";
		}
		else if (type == I_ADDI)
		{
			cout << "$addi ";
		}
		else if (type == I_B)
		{
			cout << "$b ";
		}
		for (std::list<Variable*>::iterator itv = dst.begin(); itv != dst.end(); itv++)
		{
			switch ((*itv)->getAssignment())
			{
			case t0:
			
			}
		}
		for (std::list<Variable*>::iterator its = src.begin(); its != src.end(); its++)
		{
			cout << (*its)->GetName() << ", ";
		}
		cout << "\n";
	}
	

}*/
