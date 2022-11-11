#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>

#include "root.h"
#include "data.h"

namespace Core
{
	namespace Util
	{
		std::vector<uint8_t> load(const char* path);
		void saveInFile(const char* path, const std::vector<uint8_t>& buffer);
		void saveAll(ObjectModel::Root* entity);
	}


	//serialization
	template<typename T>
	void encode(std::vector<uint8_t>& buffer, uint16_t& iterator, T value)
	{
		for (int i = (sizeof T * 8) - 8; i >= 0; i -= 8)
		{
			buffer[iterator++] = value >> i;
		}
	}


	template<>
	inline void encode<std::string>(std::vector<uint8_t>& buffer, uint16_t& iterator, const std::string value)
	{
		for (int i = 0; i != value.size(); ++i)
		{
			encode<uint8_t>(buffer, iterator, value[i]);
		}
	}


	template<typename T>
	void encode(std::vector<uint8_t>& buffer, uint16_t& iterator, const std::vector<T>& value)
	{
		for (int i = 0; i != value.size(); ++i)
		{
			encode<T>(buffer, iterator, value[i]);
		}
	}

	//deserialization
	template<typename T>
	T decode(const std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		T result = 0, temp = 0;


		for (int i = 0; i != sizeof T; ++i)
		{
			temp = buffer[iterator++] << (((sizeof T * 8) - 8) - (i * 8));
			result |= temp;
		}

		return result;
	}

	template<>
	inline std::string decode<std::string>(const std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		iterator -= 1;

		uint8_t size = decode<uint8_t>(buffer, iterator);

		std::string result((buffer.begin() + iterator), (buffer.begin() + iterator + size));

		iterator += size;

		return result;
	}


	template<typename T>
	void decode(const std::vector<uint8_t>& buffer, uint16_t& iterator, std::vector<T>& value)
	{
		for (int i = 0; i != value.size(); ++i)
		{
			value[i] = buffer[iterator++];
		}
	}
}