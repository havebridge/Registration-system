#include "object.h"

namespace ObjectModel
{
	Object::Object(std::string name)
	{
		this->setName(name);
		size += (sizeof uint16_t) * 4;
	}

	void Object::addEntitie(Primitive* entity)
	{
		primitives.push_back(*dynamic_cast<Primitive*>(entity));

		size += entity->getSize();
	}



	void Object::pack(std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		Core::encode<uint8_t>(buffer, iterator, nameLength);
		Core::encode<std::string>(buffer, iterator, name);

		for (auto p : primitives)
		{
			p.pack(buffer, iterator);
		}

		Core::encode<uint32_t>(buffer, iterator, size);
	}


	Object Object::unpack(const std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		Object o;
		o.nameLength = Core::decode<uint8_t>(buffer, iterator);
		o.name = Core::decode<std::string>(buffer, iterator);

		for (auto it = o.primitives.begin(); it != o.primitives.end(); ++it)
		{
			o.primitives.push_back(Primitive::unpack(buffer, iterator));
		}

		o.size = Core::decode<uint32_t>(buffer, iterator);

		return o;
	}
}