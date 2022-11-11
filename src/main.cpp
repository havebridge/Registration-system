#include "testHashtable.h"

#include "object.h"


int main(int argc, char** argv)
{
	const int tableSize = 20;
	HashTable::Hashtable<std::string, std::string, tableSize> Hashtable;
	std::vector<HashTable::User<std::string, std::string>> Users;


	//Users = Test::PutTest<std::string, std::string, tableSize>(Hashtable);
	//Hashtable.Serialize();

	//Test::RemoveTest<std::string, std::string, tableSize>(Hashtable, Users);
	//Test::RemoveTest<std::string, std::string, tableSize>(Hashtable, Users);
	//std::cout << std::endl;

	Hashtable.Deserialize();

	std::cout << Hashtable;

	std::cout << Test::GetTest<std::string, std::string, tableSize>(Hashtable);

	/*ObjectModel::Object Test("test");

	std::string str1 = "xyesos";
	std::string str2 = "yeban";
	std::string str3 = "grisha";
	std::string str4 = "nikita";

	std::unique_ptr<ObjectModel::Primitive> st1 = ObjectModel::Primitive::createPrimitive("str1", ObjectModel::Type::U8, ObjectModel::Wrapper::STRING, str1);
	std::unique_ptr<ObjectModel::Primitive> st2 = ObjectModel::Primitive::createPrimitive("str1", ObjectModel::Type::U8, ObjectModel::Wrapper::STRING, str2);
	std::unique_ptr<ObjectModel::Primitive> st3 = ObjectModel::Primitive::createPrimitive("str1", ObjectModel::Type::U8, ObjectModel::Wrapper::STRING, str3);
	std::unique_ptr<ObjectModel::Primitive> st4 = ObjectModel::Primitive::createPrimitive("str1", ObjectModel::Type::U8, ObjectModel::Wrapper::STRING, str4);

	Test.addEntitie(st1.get());
	Test.addEntitie(st2.get());
	Test.addEntitie(st3.get());
	Test.addEntitie(st4.get());

	Core::Util::saveAll(&Test);

	std::vector<uint8_t> objectFromFile = Core::Util::load("Data/test.hsbrdg");
	uint16_t it = 0;
	ObjectModel::Object object = ObjectModel::Object::unpack(objectFromFile, it);*/
	return 0;
}