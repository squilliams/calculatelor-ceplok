package com.company.Commands;

import com.company.Commands.IDisplayable;

public class Writer {
	/*********************************************************************************
	* Print the command
	**********************************************************************************
	*/
	public void PrintCommand(IDisplayable disp) {
		System.out.println(disp.DisplayString());
	}
};
