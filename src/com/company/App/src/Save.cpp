#include "../stdafx.h"
#include "../AppCommands/Save.h"

namespace Apps {
	App::Save::Save() {
		m_commandName = "Save";
	}
	App::Save::Save(string input) {
		m_commandName = "Save";
		m_input = input;
	}
	App::Save::~Save() {}
	void App::Save::Exec(App& app) const {
		string namafile = "Memori kalkulator.txt";
		ofstream outFile;
		outFile.open(namafile, ios::out);
		if (outFile.is_open()) {
			auto savedCommands = app.GetSavedCommands();
			for (auto const& it : savedCommands) {
				outFile << it->GetInput() << endl;
			}

			time_t rawtime;
			struct tm timeinfo;
			char buffer[128];

			time(&rawtime);
			localtime_s(&timeinfo, &rawtime);

			strftime(buffer, 80, "%Y:%m:%d-%H:%M:%S", &timeinfo);
			outFile << buffer << endl;

			outFile.close();
		}
		else {
			cerr << "Can't save" << endl;
		}
	}
	ICommand* App::Save::Create(string input) {
		return new Save(input);
	}
	bool App::Save::Validate(string input) {
		/* Get the symbols from the input */
		if (input.substr(0, 4) == "Save") {
			return true;
		}
		return false;
	}
}