#include "core.h"


namespace Core
{
	namespace Util
	{
		std::vector<uint8_t> load(const char* path)
		{
			std::ifstream in(path, std::ios::binary);
			std::vector<uint8_t> result((std::istreambuf_iterator<char>(in)), (std::istreambuf_iterator<char>()));
			return result;
		}

		void saveInFile(const char* path, const std::vector<uint8_t>& buffer)
		{
			std::ofstream file;

			file.open(path);

			if (file.is_open())
			{
				for (int i = 0; i != buffer.size(); i++)
				{
					file << buffer[i];
				}

				file.close();

				return;
			}

			std::cerr << "Unable to open the file" << std::endl;
		}


		void saveAll(ObjectModel::Root* entity)
		{
			std::vector<uint8_t> buffer(entity->getSize());
			uint16_t iterator = 0;
			std::string res = "Data/" + entity->getName().substr(0, entity->getName().size()).append(".hsbrdg");
			entity->pack(buffer, iterator);
			saveInFile(res.c_str(), buffer);
		}
	}
}