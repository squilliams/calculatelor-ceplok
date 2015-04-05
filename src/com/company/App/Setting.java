#pragma once

#include "../Commands/ICommand.h"
#include "../Commands//IDisplayable.h"
#include "Expression.h"
#include "Token.h"

using namespace Commands;

namespace Apps {
	namespace Setting{
		class Setting : public IDisplayable {
		public:
			class Set;
			/*********************************************************************************
			* Default constructor for class Setting
			**********************************************************************************
			*/
			Setting();
			/*********************************************************************************
			* Default destructor for class Setting
			**********************************************************************************
			*/
			~Setting();
			/*********************************************************************************
			* Validate a command
			**********************************************************************************
			*/
			bool Validate(Expression*);
			/*********************************************************************************
			* Return string that describe this class
			**********************************************************************************
			*/
			string DisplayString() const;
		private:
			enum ModeExpression { PREFIX = 0, INFIX = 1, POSTFIX = 2 };
			/*********************************************************************************
			* Default constructor for class Setting with parameter
			**********************************************************************************
			*/
			Setting(ModeExpression, Token::NumeralType, Token::OperatorType);
			/*********************************************************************************
			* Check a command operator mode
			**********************************************************************************
			*/
			Token::OperatorType CheckOperator(const Expression* command);
			/*********************************************************************************
			* Check a command expresion mode
			**********************************************************************************
			*/
			ModeExpression CheckExpression(string command);
			/*********************************************************************************
			* Check a command number mode
			**********************************************************************************
			*/
			Token::NumeralType CheckNumber(const Expression* command);

			Token::OperatorType m_modeOperator;
			Token::NumeralType m_modeNumber;
			ModeExpression m_modeExpression;
			static const map < ModeExpression, string >& m_expToString();
			static const map < Token::NumeralType, string >& m_numToString();
			static const map < Token::OperatorType, string >& m_opToString();
		};
	}


}