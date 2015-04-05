#include "../stdafx.h"
#include "../AppCommands/ShowMem.h"

namespace Apps {
	App::ShowMem::ShowMem() {
		m_commandName = "ShowMem";
	}
	App::ShowMem::ShowMem(string input) {
		m_commandName = "ShowMem";
		m_input = input;
		istringstream tmp(input);
		string kata1;
		tmp >> kata1;
		if (!(tmp >> n))
			n = 1;
	}
	App::ShowMem::~ShowMem() {}
	void App::ShowMem::Exec(App& app) const {
		app.AppShowMem(n);
	}
	ICommand* App::ShowMem::Create(string input) {
		return new ShowMem(input);
	}
	bool App::ShowMem::Validate(string input) {
		/* Get the symbols from the input */
		if (input.substr(0, 7) == "ShowMem") return true;
		else return false;
	}
}