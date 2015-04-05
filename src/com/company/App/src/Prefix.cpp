#include "../stdafx.h"
#include "../AppCommands/Prefix.h"

namespace Apps {
	App::Prefix::Prefix() {
		m_commandName = "Prefix Expression";
	}
	App::Prefix::Prefix(string input) {
		m_commandName = "Prefix Expression";
		m_input = input;
		m_symbols = Token::ConvertStringToSymbols(input);
	}
	App::Prefix::~Prefix() {}
	double App::Prefix::Calculate() const {
		Containers::stack<Token> operand;
		vector<Token> tmp = m_symbols;
		reverse(tmp.begin(), tmp.end());
		for (auto const& it : tmp) {
			if (it.IsOperator()) {
				Token first = operand.top();
				operand.pop();
				Token second = operand.top();
				operand.pop();
				try {
					switch (it.GetSymbolType()) {
						case Token::OPERATORPLUS:
							operand.push(first + second);
							break;
						case Token::OPERATORSUB:
							operand.push(first - second);
							break;
						case Token::OPERATORMUL:
							operand.push(first * second);
							break;
						case Token::OPERATORDIV:
							operand.push(first / second);
							break;
						case Token::OPERATORMOD:
							operand.push(first % second);
							break;
						case Token::OPERATORAND:
							operand.push(first & second);
							break;
						case Token::OPERATOROR:
							operand.push(first | second);
							break;
						case Token::OPERATORXOR:
							operand.push(first ^ second);
						case Token::OPERATORLESS:
							operand.push(first < second);
						case Token::OPERATORMORE:
							operand.push(first > second);
					}
				}
				catch (IncompatibleArgumentException ex) {
					cerr << "Fatal Error" << endl;
					return 0;
				}
			}
			else {
				operand.push(it);
			}
		}
		return operand.top().GetValue();
	}
	
	ICommand* App::Prefix::Create(string input) {
		return new Prefix(input);
	}
	bool App::Prefix::Validate(string input) {
		/* Get the symbols from the input */
		vector<Token> symbols = Token::ConvertStringToSymbols(input);
		/* Stub */
		if (symbols[0].IsOperator()) return true;
		else return false;
	}
}