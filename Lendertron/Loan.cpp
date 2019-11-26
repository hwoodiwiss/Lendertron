#include "Loan.h"
#include <sstream>

Loan::Loan(GUID Id, string TypeName, int Duration, float Interest, double Value) : m_Id(Id), m_TypeName(TypeName), m_Duration(Duration), m_Interest(Interest), m_Value(Value)
{
	m_CustomerId == GUID_NULL;
}

void Loan::SetCustomer(GUID CustomerId)
{
	m_CustomerId = CustomerId;
}

string Loan::GetValueString()
{
	std::stringstream ss;
	ss << char(156) << GetValue();
	return ss.str();
}

string Loan::GetDurationString()
{
	int Years = m_Duration / 12;
	int Months = m_Duration % 12;
	std::stringstream ss;
	
	if (Years > 0)
	{
		ss << Years << " Years";
		if (Months > 0)
		{
			ss << " ";
		}
	}

	if (Months > 0)
	{
		ss << Months << " Months";
	}

	return ss.str();
}

string Loan::GetSingleYearInterestString()
{
	std::stringstream ss;
	ss << char(156) << std::setprecision(2) << std::fixed << GetSingleYearInterest();
	return ss.str();
}

string Loan::GetTotalInterestString()
{
	std::stringstream ss;
	ss << char(156) << std::setprecision(2) << std::fixed << GetTotalInterest();
	return ss.str();
}

string Loan::GetTotalRepayableString()
{
	std::stringstream ss;
	ss << char(156) << std::setprecision(2) << std::fixed << GetTotalRepayable();
	return ss.str();
}

double Loan::GetInterestAsDecimalPercent()
{
	return m_Interest / 100;
}

double Loan::GetSingleYearInterest()
{
	return m_Value * GetInterestAsDecimalPercent();
}

double Loan::GetTotalInterest()
{
	return (GetSingleYearInterest() * (((double)m_Duration) / 12.0f));
}

double Loan::GetTotalRepayable()
{
	return m_Value + GetTotalInterest();
}

shared_ptr<Loan> Loan::NewLoan(LoanType* pLoanType, int Duration, double Value)
{
	if (pLoanType->GetMinDuration() <= Duration && pLoanType->GetMaxDuration() >= Duration)
	{
		GUID LoanId;
		if (CoCreateGuid(&LoanId) != S_OK)
		{
			return nullptr;
		}
		return shared_ptr<Loan>(new Loan(LoanId, pLoanType->GetName(), Duration, pLoanType->GetInterestRate(), Value));
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
