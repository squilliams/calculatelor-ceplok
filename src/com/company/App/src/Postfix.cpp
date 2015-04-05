#include "../stdafx.h"
#include "../AppCommands/Postfix.h"

namespace Apps {
	App::Postfix::Postfix() {
		m_commandName = "Postfix Expression";
	}
	App::Postfix::Postfix(string input) {
		m_commandName = "Postfix Expression";
		m_input = input;
		m_symbols = Token::ConvertStringToSymbols(input);
	}
	App::Postfix::~Postfix() {}
	double App::Postfix::Calculate() const {
		Containers::stack<Token> operand;
		for (auto const& it : m_symbols) {
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
							operand.push(second - first);
							break;
						case Token::OPERATORMUL:
							operand.push(first * second);
							break;
						case Token::OPERATORDIV:
							operand.push(second / first);
							break;
						case Token::OPERATORMOD:
							operand.push(second % first);
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
							operand.push(second < first);
						case Token::OPERATORMORE:
							operand.push(second > first);
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
	ICommand* App::Postfix::Create(string input) {
		return new Postfix(input);
	}
	bool App::Postfix::Validate(string input) {
		/* Get the symbols from the input */
		vector<Token> symbols = Token::ConvertStringToSymbols(input);

		if (symbols[symbols.size() - 1].IsOperator()) return true;
		else return false;
	}
}