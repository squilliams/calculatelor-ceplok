#pragma once

#include "stdafx.h"

class EOFReadException: public std::exception {
public:
	virtual const char* what() const throw() {
		return "Reached EOF of input file";
	}
};