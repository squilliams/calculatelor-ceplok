#include "../stdafx.h"
#include "../Expression.h"

namespace Apps {
	Expression::Expression() {}
	Expression::~Expression() {}
	const vector<Token>& Expression::GetSymbol() const {
		return m_symbols;
	}
	string Expression::DisplayString() const {
		Token::NumeralType numType;
		for (auto const& i: m_symbols) {
			if (i.GetNumeralType() != Token::NumeralType::NUM_UNDEFINED)
				numType = i.GetNumeralType();
		}
		string m_converted;
		try {
			m_converted = Token::ToNumeralType(Calculate(), numType);
		}
		catch (CantConvertException ex) {
			cerr << "Tidak dapat mengembalikan hasil perhitungan dalam mode bilangan ini" << endl;
		}
		return m_input + " = " + m_converted;
	}
	string Expression::GetInput() const {
		return m_input;
	}
	string Expression::GetCommandName() const {
		return m_commandName;
	}
}
