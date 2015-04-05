#include "../stdafx.h"
#include "../AppCommands/Set.h"

namespace Apps {
	namespace Setting {
		Setting::Set::Set() {
			m_commandName = "Set";
		}
		Setting::Set::Set(string input) {
			m_commandName = "Set";
			m_input = input;
			int arg1, arg2, arg3;
			do {
				cerr << "Kode mode ekspresi: 0 - Prefix | 1 - Infix | 2 - Postfix" << endl;
				cerr << "Masukkan mode ekspresi yang anda inginkan: ";
				cin >> arg1;
			} while (arg1 < 0 || arg1 > 2);
			ModeExpression modEx = static_cast<ModeExpression>(arg1);

			do {
				cerr << "Kode mode bilangan: 0 - Arab | 1 - Roman | 2 - Logika" << endl;
				cerr << "Masukkan mode bilangan yang anda inginkan: ";
				cin >> arg2;
			} while (arg2 < 0 || arg2 > 2);
			Token::NumeralType numType = static_cast<Token::NumeralType>(arg2);

			do {
				cerr << "Kode mode operator: 0 - Aritmatika | 1 - Logika" << endl;
				cerr << "Masukkan mode operator yang anda inginkan: ";
				cin >> arg3;
			} while (arg3 < 0 || arg3 > 1);
			Token::OperatorType opType = static_cast<Token::OperatorType>(arg3);
			m_setSetting = Setting(modEx, numType, opType);
			/* Read last eof */
			string dummy;
			getline(cin, dummy);

		}
		Setting::Set::~Set() {}
		void Setting::Set::Exec(App& app) const {
			app.SetSetting(m_setSetting);
		}
		ICommand* Setting::Set::Create(string input) {
			return new Set(input);
		}
		bool Setting::Set::Validate(string input) {
			/* Read the first 4 character */
			if (input.substr(0, 3) == "Set") return true;
			else return false;
		}
	}
}
