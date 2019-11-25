#pragma once
#include "Customer.h"

//Abstract interface to various types of criteria checking
//Technically Critereon is the singular for Criteria, bu it looks wrong to me
class ILoanCriteria
{
public:
	//The action criteria cheking function, pure virtual function has to be overriden in all derived classes
	virtual bool Evaluate(shared_ptr<Customer>) = 0;
};