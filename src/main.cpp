/* Autor: Uroš Jevtić Datum: 07.06.2022. */
#include <iostream>
#include <exception>

#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "LivenesAnalysis.h"
#include "IR.h"
#include "InterferenceGraph.h"

using namespace std;


int main()
{
	try
	{
		std::string fileName = ".\\..\\examples\\simple.mavn";
		bool retVal = false;

		LexicalAnalysis lex;

		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();

		retVal = lex.Do();

		if (retVal)
		{
			cout << "Lexical analysis finished successfully!" << endl;
			lex.printTokens();
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}

		/*Start of syntax analysis*/
		cout << "--------------------------------------------------" << endl;
		cout << "Syntax analysis start" << endl;

		
		Instructions instructions;		//List of instructions

		SyntaxAnalysis syntax(lex, instructions);
		
		if (syntax.Do())
		{
			cout << "Syntax analysis finished successfully!" << endl;
		}
		else
		{
			cout << "Syntax analysis failed!" << endl;
		}
		
		InterferenceGraph ig(syntax.getRegVariables());
		ig.BuildInterferenceGraph(instructions);
		ig.BuildVariableStack();

		// Print interference matrix
		cout << "Interference matrix:" << endl;
		ig.PrintInterferenceMatrix();

		//ig.ResourceAllocation();
		if (ig.ResourceAllocation())
			cout << endl << "Resource allocation successful!" << endl;
		else
			throw runtime_error("\nException! Resource allocation failed!!\n");



		syntax.createMIPS();
	}



	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
