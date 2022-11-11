#pragma once

#include "core.h"
#include "root.h"

namespace ObjectModel
{
	class Primitive : public Root
	{
	public:
		uint8_t type;
		uint8_t count;
		std::vector<uint8_t>* data;
	private:
		Primitive();
	public:
		template<typename T>
		static std::unique_ptr<Primitive> createPrimitive(std::string name, Type type, T value)
		{
			std::unique_ptr<Primitive> str(new Primitive());
			str->setName(name);
			str->type = static_cast<uint8_t>(type);
			str->count = static_cast<uint8_t>(value.size());
			str->data = new std::vector<uint8_t>(str->count);
			str->size += static_cast<uint32_t>(str->count);

			uint16_t iterator = 0;
			Core::template encode<T>(*str->data, iterator, value);

			return str;

		}

		virtual void pack(std::vector<uint8_t>&, uint16_t&) override;
		static Primitive unpack(const std::vector<uint8_t>&, uint16_t&);
	};
}