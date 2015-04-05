package com.company.App;

import com.company.Commands.*;
/*
|--------------------------------------------------------------------------
| Application run is a an application entity. This class manages all objects
| that one application need. This class is thread-safe. So you can use it
| for multi-threading. You can also save current state if you save it.
*/
public class App {
	/*********************************************************************************
	* Default constructor for class App
	**********************************************************************************
	*/
	public App() {
		Categorizer.GetInstance().Register("Save", Save.Validate);
		Categorizer.GetInstance().Register("Redo", Redo.Validate);
		Categorizer.GetInstance().Register("ShowMem", ShowMem.Validate);
		Categorizer.GetInstance().Register("ShowAllMem", ShowAllMem.Validate);
		Categorizer.GetInstance().Register("Undo", Undo.Validate);
		Categorizer.GetInstance().Register("Set", Setting.Setting.Set.Validate);
		Categorizer.GetInstance().Register("Infix", Infix.Validate);
		Categorizer.GetInstance().Register("Prefix", Prefix.Validate);
		Categorizer.GetInstance().Register("Postfix", Postfix.Validate);


		/* Register creator method for factory */
		Factory.GetInstance().Register("Save", Save.Create);
		Factory.GetInstance().Register("Redo", Redo.Create);
		Factory.GetInstance().Register("ShowMem", ShowMem.Create);
		Factory.GetInstance().Register("ShowAllMem", ShowAllMem.Create);
		Factory.GetInstance().Register("Undo", Undo.Create);
		Factory.GetInstance().Register("Set", Setting.Setting.Set.Create);
		Factory.GetInstance().Register("Infix", Infix.Create);
		Factory.GetInstance().Register("Prefix", Prefix.Create);
		Factory.GetInstance().Register("Postfix", Postfix.Create);
	}
	/*********************************************************************************
	* Run your App class
	**********************************************************************************
	*/
	public void Run() {
		boolean running = true;
		while (running) {
			/* Get new command from user */
			try {
				ICommand newCommand = m_commandReader.GetNextCommand();
				/* Try to run as base command */
				BaseCommand bc = (BaseCommand)newCommand;
				Run(bc);
				/* Try to run as expression */
				Expression* ex = dynamic_cast<Expression*>(newCommand);
				Run(ex);
				/* Save the command */
				m_savedCommands.push_back(newCommand);
				/* Save the expression */
				if (ex != nullptr)
					m_savedExpressions.push_back(ex);
				/* If no more input, stop the application */
			}
			catch (EOFReadException) {
				running = false;
			}
		}
		cerr << "Thank you" << endl;
	}
	/*********************************************************************************
	* Run your command
	**********************************************************************************
	*/
	public void Run(BaseCommand*);
	/*********************************************************************************
	* Run your expression
	**********************************************************************************
	*/
	public void Run(Expression*);
	/*********************************************************************************
	* Delete last n command from memory
	**********************************************************************************
	*/
	public void AppUndo(int);
	/*********************************************************************************
	* Redo last n command from memory
	**********************************************************************************
	*/
	public void AppRedo(int);
	/*********************************************************************************
	* Show last n command from memory
	**********************************************************************************
	*/
	public void AppShowMem(int);
	/*********************************************************************************
	* Show all command from memory
	**********************************************************************************
	*/
	public void AppShowAllMem();
	/*********************************************************************************
	* Get saved commands
	**********************************************************************************
	*/
	public const vector<ICommand*>& GetSavedCommands() const;
	/*********************************************************************************
	* Set setting
	**********************************************************************************
	*/
	public void SetSetting(Setting::Setting setting);

	private Setting::Setting m_setting;
	private Reader m_commandReader;
	private Writer m_commandWriter;
	private vector<ICommand*> m_savedCommands;
	private vector<ICommand*> m_savedExpressions;
};
