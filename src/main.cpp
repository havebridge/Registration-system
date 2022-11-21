#include "testHashtable.h"

#include "object.h"

#if RELEASE

#ifndef UNICODE
#define UNICODE
#endif 

#include <Windows.h>


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE prevInstance, PSTR CommandLine, INT ShowCode)
{
	WNDCLASS wc = { sizeof WNDCLASS };

	wc.lpszClassName = L"Window class";
	wc.hInstance = Instance;
	wc.lpfnWndProc = WindowProc;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,
		wc.lpszClassName,
		L"Hasbridge",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr,
		nullptr,
		Instance,
		nullptr
	);

	if (hwnd == nullptr)
	{
		return 0;
	}

	ShowWindow(hwnd, ShowCode);
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
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
#endif