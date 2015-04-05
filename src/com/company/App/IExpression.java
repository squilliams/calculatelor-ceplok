#pragma once

#include "Token.h"
#include "Exceptions/Exception.h"

namespace Apps {
	class IExpression {
	public:
		/* Interface to calculate the expression */
		virtual double Calculate() const = 0;
		/* Interface to get the token lists */
		virtual const vector<Token>& GetSymbol() const = 0;
	};
}
