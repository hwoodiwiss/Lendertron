#include "Loan.h"

Loan::Loan(GUID Id, string TypeName, int Duration, float Interest, double Value) : m_Id(Id), m_TypeName(TypeName), m_Duration(Duration), m_Interest(Interest), m_Value(Value)
{
	m_CustomerId == GUID_NULL;
}

void Loan::SetCustomer(GUID CustomerId)
{
	m_CustomerId = CustomerId;
}

Loan* Loan::NewLoan(LoanType* pLoanType, int Duration, double Value)
{
	if (pLoanType->GetMinDuration() <= Duration && pLoanType->GetMaxDuration() >= Duration)
	{
		GUID LoanId;
		CoCreateGuid(&LoanId);
		return new Loan(LoanId, pLoanType->GetName(), Duration, pLoanType->GetInterestRate(), Value);
	}

	return nullptr;
}

std::ostream& Loan::Serialize(std::ostream& out)
{
	out << m_Id << m_TypeName << m_Duration << m_Interest << m_Value << m_CustomerId;
	return out;
}

std::istream& Loan::Deserialize(std::istream& in)
{
	in >> m_Id >> m_TypeName >> m_Duration >> m_Interest >> m_Value >> m_CustomerId;
	return in;
}
