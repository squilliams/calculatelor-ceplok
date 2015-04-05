#pragma once

#include "../stdafx.h"

/*********************************************************************************
* Throw if we try to do binary operator to two incompatible argument
**********************************************************************************
*/
class IncompatibleArgumentException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "Incompatible Argument";
	}
};
/*********************************************************************************
* Throw if we try to do convert operand value to an invalid numeral type
**********************************************************************************
*/
class CantConvertException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "Cannot convert value to a specific numeral type";
	}
};