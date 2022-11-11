#include "primitive.h"

namespace ObjectModel
{
	Primitive::Primitive()
	{
		size += sizeof type + sizeof count;
	}


	void Primitive::pack(std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		Core::encode<uint8_t>(buffer, iterator, nameLength);
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<uint8_t>(buffer, iterator, type);
		Core::encode<uint8_t>(buffer, iterator, count);
		Core::encode<uint8_t>(buffer, iterator, *data);
		Core::encode<uint32_t>(buffer, iterator, size);
	}


	Primitive Primitive::unpack(const std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		Primitive str;

		str.nameLength = Core::decode<uint8_t>(buffer, iterator);
		str.name = Core::decode<std::string>(buffer, iterator);
		str.type = Core::decode<uint8_t>(buffer, iterator);
		str.count = Core::decode<uint8_t>(buffer, iterator);

		str.data = new std::vector<uint8_t>(str.count);

		Core::decode<uint8_t>(buffer, iterator, *str.data);

		str.size = Core::decode<uint32_t>(buffer, iterator);

		return str;
	}
}