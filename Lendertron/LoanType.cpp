#include "LoanType.h"

bool LoanType::IsEligible(Customer* pCustObj)
{
	//Iterates through the critereon for this loan type to determine if the customer is eligible 
	for (auto Critereon : m_Criteria)
	{
		//If any of the Critereon return false, the customer is not eligible
		if (!Critereon->Evaluate(pCustObj))
			return false;
	}

	return true;
}
