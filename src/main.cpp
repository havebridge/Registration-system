#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define _CRT_SECURE_NO_WARNINGS

#include "testHashtable.h"

#include "object.h"

#if RELEASE

#ifndef UNICODE
#define UNICODE
#endif 

#include <Windows.h>

const int tableSize = 2;
HashTable::Hashtable<std::string, std::string, tableSize> Hashtable;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			HWND Button1 = CreateWindow(
				L"BUTTON",
				L"SIGN IN",
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				300, 350, 150, 50,
				hwnd,
				reinterpret_cast<HMENU>(1),
				nullptr,
				nullptr
			);

			HWND Button2 = CreateWindow(
				L"BUTTON",
				L"SIGN UP",
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				1000, 350, 150, 50,
				hwnd,
				reinterpret_cast<HMENU>(2),
				nullptr,
				nullptr
			);

			HWND Button3 = CreateWindow(
				L"BUTTON",
				L"DELETE ALL",
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				1200, 600, 150, 50,
				hwnd,
				reinterpret_cast<HMENU>(3),
				nullptr,
				nullptr
			);

			std::ifstream ifs("Data/hashtable.hsbrdg", std::ios::ate);

			if (ifs.tellg() != 0)
			{
				Hashtable.Deserialize();
			}
		}
		return 0;
		
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case 1:
				{
					if (Hashtable.count >= tableSize)
					{
						MessageBox(nullptr, L"Max of Users!", L"Error", MB_ICONWARNING);
						break;
					}

					Hashtable.Put("dolbaeb", "me");
				}
				break;

				case 2:
				{
					Test::GetTest<std::string, std::string, tableSize>(Hashtable);
				}
				break;

				case 3:
				{
					Hashtable.count = 0;
					Hashtable.~Hashtable();
					std::ofstream ofs;
					ofs.open("Data/hashtable.hsbrdg", std::ofstream::out | std::ofstream::trunc);
					ofs.close();
				}
				break;
			}
		}
		return 0;

		case WM_DESTROY:
		{
			Hashtable.Serialize();
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
		wc.hInstance,
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
	return 0;
}
#endif