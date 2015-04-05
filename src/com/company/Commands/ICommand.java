package com.company.Commands;


public interface ICommand {
	/*********************************************************************************
	* Get command name
	* null
	**********************************************************************************
	*/
	public String GetCommandName();
	public String GetInput();
	public boolean Validate();
	public ICommand Create();
};
