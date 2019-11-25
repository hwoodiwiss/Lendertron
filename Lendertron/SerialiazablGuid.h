#pragma once
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN

#include "ISerializable.h"

//GUID related helper functions
std::string GuidToString(const GUID& Guid, bool IncludeBraces = true);

//Provides a serializable extension to the GUID structure, and operators to make them inter-usable
class SerializableGuid : public ISerializable
{
public:
	SerializableGuid();
	SerializableGuid(GUID Guid);
	bool operator==(const SerializableGuid& rSerGuid);

	//Equivilence operator between this type and the WinAPI GUID (Right to left and left to right
	bool operator==(const GUID& rGuid);
	friend bool operator==(const GUID& lGuid, const SerializableGuid& rSerGuid);

	SerializableGuid& operator=(const GUID& rGuid);

	GUID AsGuid() { return m_InternalGuid; }
	std::string ToString(bool IncludeBraces = true);

	std::ostream& Serialize(std::ostream& out);
	std::istream& Deserialize(std::istream& in);

private:
	GUID m_InternalGuid;
};