#include "../stdafx.h"
#include "../AppCommands/Infix.h"

namespace Apps {
	App::Infix::Infix() {
		m_commandName = "Infix Expression";
	}
	App::Infix::Infix(string input) {
		m_commandName = "Infix Expression";
		m_input = input;
		m_symbols = Token::ConvertStringToSymbols(input);
	}
	App::Infix::~Infix() {}
	double App::Infix::Calculate() const {
		vector<Token> onPostfix;
		Containers::stack<Token> st_operator;
		for (auto const& it : m_symbols) {
			if (it.GetSymbolType() == Token::OPERAND) {
				onPostfix.push_back(it);
			}
			else if (it.GetSymbolType() == Token::OPENPAR) {
				st_operator.push(it);
			}
			else if (it.GetSymbolType() == Token::CLOSEPAR) {
				while (!st_operator.empty() && st_operator.top().GetSymbolType() != Token::OPENPAR) {
					onPostfix.push_back(st_operator.top());
					st_operator.pop();
				}
				if (st_operator.empty())
					throw "Invalid Expression"; // STUB
				else
					st_operator.pop();
			}
			else if (it.IsOperator()) {
				while (!st_operator.empty() && st_operator.top().IsOperator() && it.GetValue() <= st_operator.top().GetValue()) {
					onPostfix.push_back(st_operator.top());
					st_operator.pop();
				}
				st_operator.push(it);
			}
		}
		while (!st_operator.empty()) {
			onPostfix.push_back(st_operator.top());
			st_operator.pop();
		}
		Containers::stack<Token> operand;
		for (auto const& it : onPostfix) {
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
	ICommand* App::Infix::Create(string input) {
		return new Infix(input);
	}
	bool App::Infix::Validate(string input) {
		/* Get the symbols from the input */
		vector<Token> symbols = Token::ConvertStringToSymbols(input);
		if (symbols.front().IsOperator() || symbols.back().IsOperator()) {
			return false;
		}
		return true;
	}
}