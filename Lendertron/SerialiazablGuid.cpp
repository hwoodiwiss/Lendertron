#include "SerialiazablGuid.h"
#include <sstream>

SerializableGuid::SerializableGuid()
{
	m_InternalGuid = GUID_NULL;
}

SerializableGuid::SerializableGuid(GUID Guid)
{
	m_InternalGuid = Guid;
}

bool SerializableGuid::operator==(const SerializableGuid& rSerGuid)
{
	return m_InternalGuid == rSerGuid.m_InternalGuid;
}

bool SerializableGuid::operator==(const GUID& rGuid)
{
	return m_InternalGuid == rGuid;
}

SerializableGuid& SerializableGuid::operator=(const GUID& rGuid)
{
	this->m_InternalGuid = rGuid;
	return *this;
}

std::string GuidToString(const GUID& Guid, bool IncludeBraces)
{
	std::stringstream ssOutBuilder;
	ssOutBuilder << std::uppercase;

	if(IncludeBraces)
		ssOutBuilder << "{";
		
	ssOutBuilder << std::hex << Guid.Data1 << "-";

	ssOutBuilder.width(4);
	ssOutBuilder << std::hex << Guid.Data2 << "-";

	ssOutBuilder.width(4);
	ssOutBuilder << std::hex << Guid.Data3 << "-";

	ssOutBuilder.width(2);
	ssOutBuilder << std::hex << static_cast<short>(Guid.Data4[0])
		<< static_cast<short>(Guid.Data4[1]) << "-"
		<< static_cast<short>(Guid.Data4[2]) << static_cast<short>(Guid.Data4[3])
		<< static_cast<short>(Guid.Data4[4]) << static_cast<short>(Guid.Data4[5])
		<< static_cast<short>(Guid.Data4[6]) << static_cast<short>(Guid.Data4[7]);
	if(IncludeBraces)
		ssOutBuilder << "}";

	return ssOutBuilder.str();
}


bool operator==(const GUID& lGuid, const SerializableGuid& rSerGuid)
{
	return lGuid == rSerGuid.m_InternalGuid;
}

std::string SerializableGuid::ToString(bool IncludeBraces)
{ 
	return GuidToString(m_InternalGuid, IncludeBraces);
}

std::ostream& SerializableGuid::Serialize(std::ostream& out)
{
	out.write(reinterpret_cast<char*>(&m_InternalGuid.Data1), sizeof(unsigned long));
	out.write(reinterpret_cast<char*>(&m_InternalGuid.Data2), sizeof(unsigned short));
	out.write(reinterpret_cast<char*>(&m_InternalGuid.Data3), sizeof(unsigned short));
	out.write(reinterpret_cast<char*>(&m_InternalGuid.Data4), sizeof(unsigned char) * 8);
	return out;
}

std::istream& SerializableGuid::Deserialize(std::istream& in)
{
	in.read(reinterpret_cast<char*>(&m_InternalGuid.Data1), sizeof(unsigned long));
	in.read(reinterpret_cast<char*>(&m_InternalGuid.Data2), sizeof(unsigned short));
	in.read(reinterpret_cast<char*>(&m_InternalGuid.Data3), sizeof(unsigned short));
	in.read(reinterpret_cast<char*>(&m_InternalGuid.Data4), sizeof(unsigned char) * 8);
	return in;
}


