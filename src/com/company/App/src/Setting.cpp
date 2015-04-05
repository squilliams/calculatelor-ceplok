#include "../stdafx.h"
#include "../Setting.h"

namespace Apps {
	namespace Setting {
		const map < Setting::ModeExpression, string >& Setting::m_expToString() {
			const map <Setting::ModeExpression, string> * curMap = new const map <Setting::ModeExpression, string>({
				{ Setting::ModeExpression::PREFIX, "Prefix"		},
				{ Setting::ModeExpression::INFIX, "Infix"		},
				{ Setting::ModeExpression::POSTFIX, "POSTFIX"	}
			});
			return *curMap;
		}
		const map < Token::NumeralType, string >& Setting::m_numToString() {
			const map<Token::NumeralType, string> * curMap = new const map<Token::NumeralType,string>({
				{ Token::NumeralType::ARABIAN, "Arab"	},
				{ Token::NumeralType::ROMANIAN, "Roman" },
				{ Token::NumeralType::LOGICAL, "Logika" }
			});
			return *curMap;
		}
		const map < Token::OperatorType, string >& Setting::m_opToString() {
			const map<Token::OperatorType, string> * curMap = new const map<Token::OperatorType, string>({
				{ Token::OperatorType::ARITHMATIC, "Aritmatika" },
				{ Token::OperatorType::LOGIC, "Logika"			}
			});
			return *curMap;
		}
		Setting::Setting(){
			m_modeExpression = INFIX;
			m_modeNumber = Token::ARABIAN;
			m_modeOperator = Token::ARITHMATIC;
		}
		Setting::Setting(ModeExpression modEx, Token::NumeralType modNum, Token::OperatorType modOp) {
			m_modeExpression = modEx;
			m_modeNumber = modNum;
			m_modeOperator = modOp;
		}
		Setting::~Setting(){}
		Setting::ModeExpression Setting::CheckExpression(string command){
			if (command == "Prefix Expression")
				return Setting::ModeExpression::PREFIX;
			if (command == "Postfix Expression")
				return Setting::ModeExpression::POSTFIX;
			if (command == "Infix Expression")
				return Setting::ModeExpression::INFIX;
			else
				throw 0;
		}
		Token::NumeralType Setting::CheckNumber(const Expression* expression){
			if (expression == nullptr) {
				return m_modeNumber;
			}
			Token::NumeralType ret = Token::NumeralType::NUM_UNDEFINED;
			const vector<Token>& symbols = expression->GetSymbol();
			for (const auto& i : symbols) {
				if (i.GetSymbolType() == Token::OPERAND) {
					if (ret == Token::NumeralType::NUM_UNDEFINED) {
						ret = i.GetNumeralType();
					}
					else if (ret != i.GetNumeralType()) {
						return Token::NumeralType::NUM_UNDEFINED;
					}
				}
			}
			return ret;
		}
		Token::OperatorType Setting::CheckOperator(const Expression* expression){
			if (expression == nullptr) {
				return m_modeOperator;
			}
			Token::OperatorType ret = Token::OperatorType::OP_UNDEFINED;
			const vector<Token>& symbols = expression->GetSymbol();
			for (const auto& i : symbols) {
				if (i.IsOperator()) {
					if (ret == Token::OperatorType::OP_UNDEFINED) {
						ret = i.GetOperatorType();
					}
					else if (ret != i.GetOperatorType()) {
						return Token::OperatorType::OP_UNDEFINED;
					}
				}
			}
			return ret;
		}
		bool Setting::Validate(Expression* command) {
			assert(command != nullptr);
			const Expression* tmp = dynamic_cast<Expression*>(command);
			if (tmp != nullptr) {
				Token::OperatorType tmodOperator;
				if (tmp->GetSymbol().size() > 2)
					tmodOperator = CheckOperator(tmp);
				else // If there's unary operator or it's a single number, it's fine 
					tmodOperator = m_modeOperator;
				Token::NumeralType tmodNumber = CheckNumber(tmp);
				ModeExpression tmodExpression = CheckExpression(command->GetCommandName());

				return ((tmodOperator == m_modeOperator) && (tmodExpression == m_modeExpression) && (tmodNumber == m_modeNumber));
			}
			else {
				return true;
			}
		}
		string Setting::DisplayString() const {
			ostringstream ret;
			try {
				ret << "Setting" << endl;
				ret << "Mode ekspresi = " << m_expToString().at(m_modeExpression) << endl;
				ret << "Mode bilangan = " << m_numToString().at(m_modeNumber) << endl;
				ret << "Mode operator = " << m_opToString().at(m_modeOperator) << endl;
			}
			catch (invalid_argument Ex) {
				ret << "Show failed" << endl;
			}
			return ret.str();
		}
	}
}