#pragma once

using namespace std;

namespace Apps {
	class Token {
	public:
		Token();
		~Token();
		enum SymbolType {
			OPERAND,
			OPERATORPLUS,
			OPERATORSUB,
			OPERATORMUL,
			OPERATORDIV,
			OPERATORMOD,
			OPERATORAND,
			OPERATOROR,
			OPERATORNOT,
			OPERATORXOR,
			OPERATORLESS,
			OPERATORMORE,
			OPENPAR,
			CLOSEPAR
		};
		enum NumeralType {
			ARABIAN = 0,
			ROMANIAN = 1,
			LOGICAL = 2,
			NUM_UNDEFINED = 3
		};
		enum OperatorType {
			ARITHMATIC = 0,
			LOGIC = 1,
			OP_UNDEFINED = 2
		};

		double GetValue() const;
		bool IsOperator() const;
		string GetInput() const;

		SymbolType GetSymbolType() const;
		NumeralType GetNumeralType() const;
		OperatorType GetOperatorType() const;

		Token& operator%(const Token& other);
		Token& operator+(const Token& other);
		Token& operator-(const Token& other);
		Token& operator*(const Token& other);
		Token& operator/(const Token& other);
		Token& operator&(const Token& other);
		Token& operator<(const Token& other);
		Token& operator>(const Token& other);
		Token& operator|(const Token& other);
		Token& operator^(const Token& other);

		static vector<Token> ConvertStringToSymbols(string);
		static string ToNumeralType(double, NumeralType);
	private:
		Token(string);
		bool IsOperatorArithmatic() const;
		bool IsOperatorLogical() const;

		SymbolType m_symbolType;
		NumeralType m_numeralType;
		OperatorType m_operatorType;

		string m_input;
		double m_value;

		static const map<SymbolType, int>& m_precedenceMap();
		static const map<string, SymbolType>& m_symbolMap();
	};
}