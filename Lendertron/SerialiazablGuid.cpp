#include "SerialiazablGuid.h"

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

bool operator==(const GUID& lGuid, const SerializableGuid& rSerGuid)
{
	return lGuid == rSerGuid.m_InternalGuid;
}

std::ostream& SerializableGuid::Serialize(std::ostream& out)
{
	out << m_InternalGuid.Data1 << m_InternalGuid.Data2 << m_InternalGuid.Data3 << m_InternalGuid.Data4;
	return out;
}

std::istream& SerializableGuid::Deserialize(std::istream& in)
{
	in >> m_InternalGuid.Data1 >> m_InternalGuid.Data2 >> m_InternalGuid.Data3 >> m_InternalGuid.Data4;
	return in;
}


