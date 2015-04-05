#pragma once

#include "BaseCommand.h"

namespace Apps {
	/*
	|--------------------------------------------------------------------------
	| Redo is a class for Redo command. Redo call the AppRedo to load memory.
	*/
	class App::Redo : public BaseCommand {
	public:
		/*********************************************************************************
		* Default constructor
		**********************************************************************************
		*/
		Redo();
		/*********************************************************************************
		* Default constructor
		**********************************************************************************
		*/
		Redo(string);
		/*********************************************************************************
		* Default destructor
		**********************************************************************************
		*/
		~Redo();
		/*********************************************************************************
		* Execute command
		**********************************************************************************
		*/
		void Exec(App&) const;
		/*********************************************************************************
		* Create new instance of the class
		**********************************************************************************
		*/
		static ICommand* Create(string);
		/*********************************************************************************
		* Check if string input is appropriate for this class
		**********************************************************************************
		*/
		static bool Validate(string);
	private:
		int n;
	};
}