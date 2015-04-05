#include "../stdafx.h"
#include "../AppCommands/BaseCommand.h"

namespace Apps {
	App::BaseCommand::BaseCommand() {
		m_commandName = "Base Command";
	}
	App::BaseCommand::~BaseCommand() {}
	string App::BaseCommand::GetInput() const {
		return m_input;
	}
	string App::BaseCommand::DisplayString() const {
		return m_input;
	}
	string App::BaseCommand::GetCommandName() const {
		return m_commandName;
	}
}