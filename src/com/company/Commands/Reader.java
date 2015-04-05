package com.company.Commands;

import com.company.Commands.ICommand;

import java.io.BufferedReader;
import java.io.InputStreamReader;


public class Reader {
	public ICommand GetNextCommand() {
		BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
		String input = new String();
		try {
			while ((input = bufferedReader.readLine()) != null && input.length() == 0) {
				System.out.print("Masukkan perintah: ");
			}
		} catch (Exception ex) {
		}
		String name = Categorizer.GetInstance().CreateCategory(input);
		ICommand command = Factory.GetInstance().CreateCommand(name, input);

		return command;
	}
};
