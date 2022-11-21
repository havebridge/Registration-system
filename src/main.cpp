#include "testHashtable.h"

#include "object.h"

#if RELEASE

#ifndef UNICODE
#define UNICODE
#endif 

#include <Windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLing, int nCmdShow)
{
	MSG msg;
	HWND hwnd;
	WNDCLASSEX wc{ (sizeof WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
	{
		switch (uMsg)
		{
			case WM_DESTROY:
			{
				PostQuitMessage(EXIT_SUCCESS);
			}
			return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
	wc.lpszClassName = L"Window";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
	{
		return EXIT_FAILURE;
	}

	if (hwnd = CreateWindow(wc.lpszClassName, L"Hasbridge", WS_OVERLAPPEDWINDOW, 100, 100, 600, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
	{
		return EXIT_FAILURE;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
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