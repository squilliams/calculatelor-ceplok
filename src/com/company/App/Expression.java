#pragma once

#include "IExpression.h"
#include "../Commands/ICommand.h"
#include "../Commands/IDisplayable.h"

namespace Apps {
	class Expression : public Commands::ICommand, public IExpression, public Commands::IDisplayable {
	public:
		/*********************************************************************************
		* Base class for all expression
		**********************************************************************************
		*/
		Expression();
		/*********************************************************************************
		* Get list of tokens for this expression
		**********************************************************************************
		*/
		const vector<Token>& GetSymbol() const;
		/*********************************************************************************
		* Return string to be displayed
		**********************************************************************************
		*/
		virtual string DisplayString() const;
		/*********************************************************************************
		* Return name as a command
		**********************************************************************************
		*/
		string GetCommandName() const;
		/*********************************************************************************
		* Get the original input
		**********************************************************************************
		*/
		string GetInput() const;
		/*********************************************************************************
		* Destructor
		**********************************************************************************
		*/
		virtual ~Expression();
	protected:
		vector<Token> m_symbols;
		string m_commandName;
		string m_input;
	};
}

