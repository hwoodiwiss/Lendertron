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
	out << m_Id;
	out.write(m_TypeName.data(), sizeof(char) * m_TypeName.length() + 1);
	out.write(reinterpret_cast<char*>(&m_Duration), sizeof(int));
	out.write(reinterpret_cast<char*>(&m_Interest), sizeof(float));
	out.write(reinterpret_cast<char*>(&m_Value), sizeof(double));
	out << m_CustomerId;
	return out;
}

std::istream& Loan::Deserialize(std::istream& in)
{
	in >> m_Id;
	m_TypeName = InStreamToString(in);
	in.read(reinterpret_cast<char*>(&m_Duration), sizeof(int));
	in.read(reinterpret_cast<char*>(&m_Interest), sizeof(float));
	in.read(reinterpret_cast<char*>(&m_Value), sizeof(double));
	in >> m_CustomerId;
	return in;
}
