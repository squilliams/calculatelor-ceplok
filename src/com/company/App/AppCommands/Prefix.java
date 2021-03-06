#pragma once

#include "BaseCommand.h"

namespace Apps {
	/*
	|--------------------------------------------------------------------------
	| Prefix is a class for prefix expression
	*/
	class App::Prefix : public Expression{
	public:
		/*********************************************************************************
		* Default constructor
		**********************************************************************************
		*/
		Prefix(string);
		/*********************************************************************************
		* Default destructor
		**********************************************************************************
		*/
		~Prefix();
		/*********************************************************************************
		* Calculate the expression and return the result
		**********************************************************************************
		*/
		double Calculate() const;
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
		/*********************************************************************************
		* Default constructor
		**********************************************************************************
		*/
		Prefix();
	};
}