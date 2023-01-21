#pragma once

#include "core.h"

namespace ObjectModel
{
	enum class Type : uint8_t
	{
		U8 = 1,
		U16,
		U32,

		BOOL
	};


	template<typename ...>
	uint8_t getTypeSize(Type type)
	{
		switch (type)
		{
		case Type::U8: return sizeof(uint8_t); break;
		case Type::U16: return sizeof(uint16_t); break;
		case Type::U32: return sizeof(uint32_t); break;
		case Type::BOOL: return sizeof(bool); break;
		}
	}
}