#include "../stdafx.h"
#include "../AppCommands/Redo.h"

namespace Apps {
	App::Redo::Redo() {
		m_commandName = "Redo";
	}
	App::Redo::Redo(string input) {
		m_commandName = "Redo";
		m_input = input;
		istringstream tmp(input);
		string kata1;
		tmp >> kata1;
		if (!(tmp >> n))
			n = 1;
	}
	App::Redo::~Redo() {}
	void App::Redo::Exec(App& app) const {
		app.AppRedo(n);
	}
	ICommand* App::Redo::Create(string input) {
		return new Redo(input);
	}
	bool App::Redo::Validate(string input) {
		/* Get the symbols from the input */
		if (input.substr(0, 4) == "Redo") return true;
		else return false;
	}
}