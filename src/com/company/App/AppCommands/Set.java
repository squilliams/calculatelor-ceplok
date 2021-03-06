#pragma once

#include "BaseCommand.h"
#include "../Setting.h"

namespace Apps {
	/*
	|--------------------------------------------------------------------------
	| Set is class to configure setting class.
	*/
	namespace Setting {
		class Setting::Set : public App::BaseCommand {
		public:
			/*********************************************************************************
			* Default constructor
			**********************************************************************************
			*/
			Set();
			/*********************************************************************************
			* Constructor with parameter
			**********************************************************************************
			*/
			Set(string);
			/*********************************************************************************
			* Default destructor
			**********************************************************************************
			*/
			~Set();
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
			Setting m_setSetting;
		};
	}
}

