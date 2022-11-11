#pragma once

#include "core.h"
#include "primitive.h"
#include "string.h"

namespace ObjectModel
{
	class Object : public Root
	{
	public:
		std::vector<Primitive> primitives;
	public:
		Object(std::string);
		Object() = default;
	public:
		void addEntitie(Primitive*);

		virtual void pack(std::vector<uint8_t>&, uint16_t&) override;
		static Object unpack(const std::vector<uint8_t>&, uint16_t&);
	};
}