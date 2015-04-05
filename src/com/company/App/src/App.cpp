#include "../App.h"
#include "../AppCommands/Commands.h"
#include "../../Commands/Creations.h"

namespace Apps {
	void App::Run() {
	}
	void App::Run(BaseCommand* bc) {
		if (bc != nullptr) {
			bc->Exec(*this);
		}
	}
	void App::Run(Expression* ex) {
		if (ex != nullptr) {
			/* Validate the expression */
			if (m_setting.Validate(ex)) {
				/* Write the result to user if possible */
				IDisplayable* tmpCommand = dynamic_cast<IDisplayable*>(ex);
				if (tmpCommand != nullptr)
					m_commandWriter.PrintCommand(tmpCommand);
				
			}
			else {
				/* Command is not valid */
				cerr << "Ekspresi yang anda masukkan tidak valid" << endl;
			}
		}
	}
	void App::AppUndo(int n) {
		int j = 0;
		for (int i = 0; i < n && m_savedCommands.size() > 0; i++){
			if (dynamic_cast<Expression*>(m_savedCommands.back()) != nullptr) {
				j++;
			}
			delete m_savedCommands.back();
			m_savedCommands.pop_back();
		}
		for (int i = 0; i < j && m_savedExpressions.size() > 0; i++){
			m_savedExpressions.pop_back();
		}
	}
	void App::AppRedo(int nredo) {
		for (int i = m_savedExpressions.size() - nredo; i < (int)m_savedExpressions.size(); i++) {
			/* Run as expression */
			Expression* ex = dynamic_cast<Expression*>(m_savedExpressions[i]);
			Run(ex);
		}
	}
	void App::AppShowMem(int n){
		if (n > (int)m_savedCommands.size()){
			cerr << "N melebihi batas jumlah memori" << endl << "Nilai maksimal N adalah " << (int)m_savedCommands.size() << endl;
		}else{
			for (int i = m_savedCommands.size() - n; i < (int)m_savedCommands.size(); i++){
				IDisplayable* tmpCommand = dynamic_cast<IDisplayable*>(m_savedCommands[i]);
				if (tmpCommand != nullptr)
					m_commandWriter.PrintCommand(tmpCommand);
			}
		}
	}
	void App::AppShowAllMem(){
		for (int i = 0; i < (int)m_savedCommands.size(); i++){
			IDisplayable* tmpCommand = dynamic_cast<IDisplayable*>(m_savedCommands[i]);
			if (tmpCommand != nullptr)
				m_commandWriter.PrintCommand(tmpCommand);
		}
	}
	const vector<ICommand*>& App::GetSavedCommands() const {
		return m_savedCommands;
	}
	void App::SetSetting(Setting::Setting setting) {
		m_setting = setting;
	}
}
