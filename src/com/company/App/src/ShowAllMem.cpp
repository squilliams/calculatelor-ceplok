#include "../stdafx.h"
#include "../AppCommands/ShowAllMem.h"

namespace Apps {
	App::ShowAllMem::ShowAllMem() {
		m_commandName = "ShowAll";
	}
	App::ShowAllMem::ShowAllMem(string input) {
		m_commandName = "ShowAll";
		m_input = input;
	}
	App::ShowAllMem::~ShowAllMem() {}
	void App::ShowAllMem::Exec(App& app) const {
		app.AppShowAllMem();
	}
	ICommand* App::ShowAllMem::Create(string input) {
		return new ShowAllMem(input);
	}
	bool App::ShowAllMem::Validate(string input) {
		/* Get the symbols from the input */
		/* Stub */
		if (input.substr(0, 7) == "ShowAll") return true;
		else return false;
	}
}