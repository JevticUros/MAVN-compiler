#include "IR.h"

typedef vector<std::vector<int>> InterferenceMatrix;
typedef stack<Variable*> VariableStack;


/* Class that represents interference graph.
Builds interference graph and does reasource allocation*/
class InterferenceGraph
{
public:
	InterferenceGraph(Variables& vars);
	~InterferenceGraph();

	/* Creates interference graph (matrix) from instructions. */
	void BuildInterferenceGraph(Instructions& instructions);

	/* Creates stack from list of register variables. */
	void BuildVariableStack();

	/* Allocates real registers to variables according to the interference. */
	bool ResourceAllocation();

	/* Prints interference matrix to the console. */
	void PrintInterferenceMatrix();

	InterferenceMatrix im;
	VariableStack varStack;  // same as list of instructions, just in form of stack

private:

	/* Resizes matrix to the passed size. */
	void ResizeInterferenceMatrix(int size);

	/* Applies reg to the variable that has varPos for its position. */
	void ApplyRegToVariable(int varPos, Regs reg);

	Variables& regVariables;  // register variables
};
