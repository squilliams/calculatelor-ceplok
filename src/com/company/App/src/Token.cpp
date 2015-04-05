#include "../stdafx.h"
#include "../Token.h"
#include "../Exceptions/Exception.h"

namespace Apps {
	const map<Token::SymbolType, int>& Token::m_precedenceMap() {
		static const map<Token::SymbolType, int>* curMap = new const map<Token::SymbolType, int>(
		{
			/* Arithmatical Operator Precedences */
			{ Token::OPERAND, 0			},
			{ Token::OPERATORPLUS, 1	},
			{ Token::OPERATORSUB, 1		},
			{ Token::OPERATORMUL, 2		},
			{ Token::OPERATORDIV, 2		},
			{ Token::OPERATORMOD, 2		},
			/* Logical Operator Precedences */
			{ Token::OPERATORAND, 1		},
			{ Token::OPERATOROR, 1		},
			{ Token::OPERATORXOR, 1		},
			{ Token::OPERATORLESS, 1	},
			{ Token::OPERATORMORE, 1	},
			{ Token::OPERATORNOT, 4		},
			/* Parentheses (optional) */
			{ Token::OPENPAR, 3			},
			{ Token::CLOSEPAR, 3		}
		});
		return *curMap;
	}
	const map<string, Token::SymbolType>& Token::m_symbolMap() {
		static const map<string, Token::SymbolType>* const curMap = new const map<string, Token::SymbolType>(
		{
			{ "+", Token::OPERATORPLUS	},
			{ "-", Token::OPERATORSUB	},
			{ "*", Token::OPERATORMUL	},
			{ "/", Token::OPERATORDIV	},
			{ "%", Token::OPERATORMOD	},
			{ "&", Token::OPERATORAND	},
			{ "|", Token::OPERATOROR	},
			{ "^", Token::OPERATORXOR },
			{ "<", Token::OPERATORLESS },
			{ ">", Token::OPERATORMORE },
			{ "!", Token::OPERATORNOT	},
			{ "(", Token::OPENPAR		},
			{ ")", Token::CLOSEPAR		}
		});
		return *curMap;
	};
	Token::Token() {}
	Token::Token(string symbol) {
		m_input = symbol;
		if (m_symbolMap().find(symbol) != m_symbolMap().end()) {
			m_symbolType = m_symbolMap().at(symbol);
			m_value = m_precedenceMap().at(m_symbolType);
			if (IsOperatorArithmatic())
				m_operatorType = ARITHMATIC;
			else if (IsOperatorLogical())
				m_operatorType = LOGIC;
			else
				m_operatorType = OP_UNDEFINED;
		}
		else {
			m_symbolType = OPERAND;
			if (symbol == "TRUE") {
				m_value = -1;
				m_numeralType = LOGICAL;
			}
			else if (symbol == "FALSE") {
				m_value = 0;
				m_numeralType = LOGICAL;
			}
			else {
				try {
					m_value = stod(symbol);
					m_numeralType = ARABIAN;
				}
				catch (invalid_argument Ex) {
					//Convert to arab
					map<char, int> roman_lib = {
						{ 'I', 1 },
						{ 'V', 5 },
						{ 'X', 10 },
						{ 'L', 50 },
						{ 'C', 100 },
						{ 'D', 500 },
						{ 'M', 1000 },
					};
					bool isRoman = true;
					for (auto const& i : symbol) {
						isRoman = isRoman && roman_lib[i];
					}
					if (isRoman) {
						m_numeralType = ROMANIAN;
						int temp_value = 0;
						int i = 0;
						while (i < (int)symbol.length()) {
							if (i == symbol.length() - 1) {
								temp_value += roman_lib[symbol[i]];
							}
							else {
								if (roman_lib[symbol[i + 1]] <= roman_lib[symbol[i]]) {
									temp_value += roman_lib[symbol[i]];
								}
								else {
									temp_value -= roman_lib[symbol[i]];
								}
							}
							++i;
						}
						m_value = temp_value;
					}
					else
						m_numeralType = NUM_UNDEFINED;
				}
				catch (...) {
					cerr << "Fatal error" << endl;
				}
			}
		}
	}
	Token::~Token() {}
	double Token::GetValue() const {
		return m_value;
	}
	string Token::GetInput() const {
		return m_input;
	}
	bool Token::IsOperator() const {
		return (IsOperatorArithmatic() || IsOperatorLogical());
	}
	bool Token::IsOperatorArithmatic() const {
		return (m_symbolType == OPERATORPLUS ||
				m_symbolType == OPERATORSUB ||
				m_symbolType == OPERATORMUL ||
				m_symbolType == OPERATORMOD ||
				m_symbolType == OPERATORDIV);
	}
	bool Token::IsOperatorLogical() const {
		return (m_symbolType == OPERATORAND ||
			m_symbolType == OPERATOROR ||
			m_symbolType == OPERATORLESS ||
			m_symbolType == OPERATORMORE ||
				m_symbolType == OPERATORXOR);
	}
	Token::SymbolType Token::GetSymbolType() const {
		return m_symbolType;
	}
	Token::NumeralType Token::GetNumeralType() const {
		return m_numeralType;
	}
	Token::OperatorType Token::GetOperatorType() const {
		return m_operatorType;
	}
	Token& Token::operator+(const Token& other) {
		if (other.GetSymbolType() == Token::OPERAND) {
			this->m_value += other.m_value;
			return *this;
		}
		else {
			throw IncompatibleArgumentException();
		}
	}
	Token& Token::operator-(const Token& other) {
		if (other.GetSymbolType() == Token::OPERAND) {
			this->m_value -= other.m_value;
			return *this;
		}
		else {
			throw IncompatibleArgumentException();
		}
	}
	Token& Token::operator*(const Token& other) {
		if (other.GetSymbolType() == Token::OPERAND) {
			this->m_value *= other.m_value;
			return *this;
		}
		else {
			throw IncompatibleArgumentException();
		}
	}
	Token& Token::operator/(const Token& other) {
		if (other.GetSymbolType() == Token::OPERAND) {
			this->m_value /= other.m_value;
			return *this;
		}
		else {
			throw IncompatibleArgumentException();
		}
	}
	Token& Token::operator%(const Token& other) {
		if (other.GetSymbolType() == Token::OPERAND) {
			this->m_value = (int) this->m_value % (int) other.m_value;
			return *this;
		}
		else {
			throw IncompatibleArgumentException();
		}
	}
	Token& Token::operator&(const Token& other) {
		if (other.GetSymbolType() == Token::OPERAND) {
			this->m_value = ((int)m_value & (int)other.m_value);
			return *this;
		}
		else {
			throw IncompatibleArgumentException();
		}
	}
	Token& Token::operator<(const Token& other) {
		if (other.GetSymbolType() == Token::OPERAND) {
			this->m_value = (m_value < other.m_value);
			return *this;
		}
		else {
			throw IncompatibleArgumentException();
		}
	}
	Token& Token::operator>(const Token& other) {
		if (other.GetSymbolType() == Token::OPERAND) {
			this->m_value = (m_value > other.m_value);
			return *this;
		}
		else {
			throw IncompatibleArgumentException();
		}
	}
	Token& Token::operator|(const Token& other) {
		if (other.GetSymbolType() == Token::OPERAND) {
			this->m_value = ((int)m_value | (int)other.m_value);
			return *this;
		}
		else {
			throw IncompatibleArgumentException();
		}
	}
	Token& Token::operator^(const Token& other) {
		if (other.GetSymbolType() == Token::OPERAND) {
			this->m_value = ((int)m_value ^ (int)other.m_value);
			return *this;
		}
		else {
			throw IncompatibleArgumentException();
		}
	}
	vector<Token> Token::ConvertStringToSymbols(string input) {
		vector<Token> ret;
		istringstream ss(input);
		string tmp;
		bool nFlag = false;
		while (ss >> tmp) {
			Token tmTok(tmp);
			if (nFlag) {
				assert(tmTok.GetSymbolType() == OPERAND);
				nFlag = false;
				tmTok.m_value = ~(int)tmTok.m_value;
			}
			if (tmTok.GetSymbolType() == OPERATORNOT)
				nFlag = true;
			ret.push_back(tmTok);
		}
		return ret;
	}
	string Token::ToNumeralType(double value, NumeralType numType){
		std::ostringstream ss;
		map<int, string> roman_dict = {
			{ 1000, "M" },
			{ 900, "CM" },
			{ 500, "D" },
			{ 400, "CD" },
			{ 100, "C" },
			{ 90, "XC" },
			{ 50, "L" },
			{ 40, "XL" },
			{ 10, "X" },
			{ 9, "IX" },
			{ 5, "V" },
			{ 4, "IV" },
			{ 1, "I" }
		};
		switch (numType) {
			case ARABIAN: {
				ss << value;
				break;
			}
			case ROMANIAN: {
				auto i = roman_dict.end();
				i--;
				while (value > 0) {
					while (value >= i->first) {
						ss << i->second;
						value -= i->first;
					}
					if (value > 0 && i == roman_dict.begin())
						throw CantConvertException();
					i--;
				}
				break;
			}
			case LOGICAL: {
				if (value == 0)
					ss << "FALSE";
				else
					ss << "TRUE";
			}
		}
		return ss.str();
	}
}