#include "../stdafx.h"
#include "../AppCommands/Undo.h"

namespace Apps {
	App::Undo::Undo() {
		m_commandName = "Undo";
	}
	App::Undo::Undo(string input) {
		m_commandName = "Undo";
		m_input = input;
		istringstream ss(m_input);
		string temp;
		ss >> temp;
		if (!(ss >> n))
			n = 1;
	}
	App::Undo::~Undo() {}
	void App::Undo::Exec(App& app) const {
		app.AppUndo(n);
	}
	ICommand* App::Undo::Create(string input) {
		return new Undo(input);
	}
	bool App::Undo::Validate(string input) {
		/* Read the first 4 character */
		if (input.substr(0, 4) == "Undo") return true;
		else return false;
	}
}