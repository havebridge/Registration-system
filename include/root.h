#pragma once

#include "core.h"


namespace ObjectModel
{
	class Root
	{
	protected:
		std::string name;
		uint8_t nameLength;
		uint32_t size;
	protected:
		Root()
			:
			name(""),
			nameLength(0),
			size(sizeof nameLength + sizeof size) {}
	public:
		void setName(std::string name)
		{
			this->name = name;
			nameLength += (uint8_t)name.size();
			size += nameLength;
		}

		uint32_t getSize() const { return this->size; }
		std::string getName() const { return this->name; }

		virtual void pack(std::vector<uint8_t>&, uint16_t&) = 0;
	};
}