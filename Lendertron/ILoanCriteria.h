#pragma once
#include "Customer.h"

//Abstract interface to various types of criteria cheking
class ILoanCriteria
{
public:
	//The action criteria cheking function, pure virtual function has to be overriden in all derived classes
	virtual bool Evaluate(Customer*) = 0;
};