#include "main.h"

#if RELEASE
int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
    )
{
	WinApi32::Window win;
	return win.Run();
}

#endif


#if DEBUG
int main(int argc, char** argv)
{
	const int tableSize = 2;
	HashTable::Hashtable<std::string, std::string, tableSize> Hashtable;
	std::vector<HashTable::User<std::string, std::string>> Users;


	//Users = Test::PutTest<std::string, std::string, tableSize>(Hashtable);
	//Hashtable.Serialize();

	//Test::RemoveTest<std::string, std::string, tableSize>(Hashtable, Users);
	//Test::RemoveTest<std::string, std::string, tableSize>(Hashtable, Users);
	//std::cout << std::endl;

	Hashtable.Deserialize();

	std::cout << Hashtable;

	//std::cout << Test::GetTest<std::string, std::string, tableSize>(Hashtable);
	return 0;
}
#endif
