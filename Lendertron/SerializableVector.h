#pragma once
#include <vector>
#include <type_traits>

#include "ISerializable.h"

template<typename T> class SerializableVector : public std::vector<T*>, public ISerializable
{
	static_assert(std::is_base_of<ISerializable, T>::value, "T must inherit from ISerialiazable");
public:
	SerializableVector() : std::vector<T*>() {}

	std::ostream& Serialize(std::ostream& out)
	{
		size_t size = this->size();
		out.write(reinterpret_cast<char*>(&size), sizeof(size_t));
		for (size_t i = 0; i != size; i++)
		{
			out << *(this->at(i));
		}

		return out;
	}

	std::istream& Deserialize(std::istream& in)
	{
		//This is by no means the most efficient way of doing this, there will be overhead for each push_back, especially on size boundaries
		size_t numElements;
		in.read(reinterpret_cast<char*>(&numElements), sizeof(size_t));
		for (size_t index = 0; index < numElements; index++)
		{
			T* currItem = new T();
			in >> *currItem;
			this->push_back(currItem);
		}

		return in;
	}
};