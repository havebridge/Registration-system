#pragma once

#include "testHashtable.h"

#include "object.h"

#ifndef UNICODE
#define UNICODE
#define UNICODE_WAS_UNDEFINED
#endif

#include <Windows.h>

#ifdef UNICODE_WAS_UNDEFINED
#undef UNICODE
#endif



#include <algorithm>

namespace WinApi32
{
	class Window
	{
	private:
		const std::wstring appName = L"Hasbridge";
		const std::wstring className = L"WindowClass";
		HWND hwnd, buttonSignIn, buttonSignUp, buttonClear;
		HWND Login, Password;

		static const int tableSize = 100;
		HashTable::Hashtable<std::string, std::string, tableSize> Hashtable;

	public:
		explicit Window();
		~Window() = default;

		int Run();
	private:
		void InitNativeWindowObj();

		static LRESULT CALLBACK AppProc(HWND whnd, UINT msg, WPARAM wparam, LPARAM lparam);
		LRESULT CALLBACK WinProc(HWND whnd, UINT msg, WPARAM wparam, LPARAM lparam);

		void CreateNativeControls();
	};
}
