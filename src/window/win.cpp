#include "win.h"

namespace WinApi32
{

	Window::Window()
	{
		this->InitNativeWindowObj();
		this->CreateNativeControls();
	}

	int Window::Run()
	{
		MSG msg;

		ShowWindow(this->hwnd, SW_SHOWDEFAULT);
		UpdateWindow(this->hwnd);

		std::ifstream ifs("Data/hashtable.hsbrdg", std::ios::ate);

		if (ifs.tellg() != 0)
		{
			Hashtable.Deserialize();
		}

		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return static_cast<int>(msg.wParam);
	}

	void Window::InitNativeWindowObj()
	{
		WNDCLASSEX wc = { sizeof WNDCLASSEX };

		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hInstance = GetModuleHandle(nullptr);
		wc.lpfnWndProc = Window::AppProc;
		wc.lpszClassName = this->className.c_str();
		wc.lpszMenuName = nullptr;
		wc.style = CS_VREDRAW | CS_HREDRAW;

		if (!RegisterClassEx(&wc))
		{
			throw std::runtime_error("Error, cannot register main window class!");
		}

		this->hwnd = CreateWindowEx(
			0,
			this->className.c_str(),
			this->appName.c_str(),
			WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MINIMIZE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			nullptr,
			nullptr,
			nullptr,
			this
		);
	}

	LRESULT CALLBACK Window::AppProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		Window* win;
		if (msg == WM_NCCREATE)
		{
			win = static_cast<Window*>(reinterpret_cast<CREATESTRUCT*>(lparam)->lpCreateParams);
			SetLastError(0);
			if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(win)))
			{
				if (GetLastError() != 0)
				{
					return false;
				}
			}
		}
		else
		{
			win = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		}

		if (win)
		{
			win->hwnd = hwnd;
			return win->WinProc(hwnd, msg, wparam, lparam);

		}

		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	LRESULT CALLBACK Window::WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
		case WM_COMMAND:
		{
			switch (LOWORD(wparam))
			{
			case 1:
			{
				if (Hashtable.count >= tableSize)
				{
					MessageBox(nullptr, L"Max of Users!", L"Error", MB_ICONWARNING);
					break;
				}

				std::wstring loginEnter;
				std::wstring passwordEnter;

				std::string login;
				std::string password;

				loginEnter.resize(MAX_PATH);
				passwordEnter.resize(MAX_PATH);
				GetWindowText(this->Login, &loginEnter[0], MAX_PATH);
				GetWindowText(this->Password, &passwordEnter[0], MAX_PATH);

				loginEnter.erase(remove(begin(loginEnter), end(loginEnter), 0), end(loginEnter));
				passwordEnter.erase(remove(begin(passwordEnter), end(passwordEnter), 0), end(passwordEnter));

				std::copy(loginEnter.begin(), loginEnter.end(), std::back_inserter(login));
				std::copy(passwordEnter.begin(), passwordEnter.end(), std::back_inserter(password));

				if (login.size() != 0 && password.size() != 0)
				{
					Hashtable.Put(login, password);
				}
				else
				{
					MessageBox(hwnd, L"Login and Password cannot be empty", L"Message", 0);
				}
				
				loginEnter.clear();
				passwordEnter.clear();
				login.clear();
				password.clear();
			}
			break;

			case 2:
			{
				std::wstring loginEnter;
				std::wstring passwordEnter;

				std::string login;
				std::string password;

				loginEnter.resize(MAX_PATH);
				passwordEnter.resize(MAX_PATH);
				GetWindowText(this->Login, &loginEnter[0], MAX_PATH);
				GetWindowText(this->Password, &passwordEnter[0], MAX_PATH);

				loginEnter.erase(remove(begin(loginEnter), end(loginEnter), 0), end(loginEnter));
				passwordEnter.erase(remove(begin(passwordEnter), end(passwordEnter), 0), end(passwordEnter));

				std::copy(loginEnter.begin(), loginEnter.end(), std::back_inserter(login));
				std::copy(passwordEnter.begin(), passwordEnter.end(), std::back_inserter(password));

				if (Hashtable.Get(login, password))
				{
					MessageBox(hwnd, L"Found", L"Message", 0);
				}
				else
				{
					MessageBox(hwnd, L"Not Found", L"Message", 0);
				}

				loginEnter.clear();
				passwordEnter.clear();
				login.clear();
				password.clear();
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
			PostQuitMessage(EXIT_SUCCESS);
		}
		return 0;
		}

		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	void Window::CreateNativeControls()
	{
		if (this->buttonSignIn = CreateWindowEx(
			0,
			L"BUTTON",
			L"Sign up",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			300, 350, 150, 50,
			this->hwnd,
			reinterpret_cast<HMENU>(1),
			nullptr,
			nullptr
		); !this->buttonSignIn)
		{
			throw std::runtime_error("Error, cannot create sign in button");
		}

		if (this->buttonSignUp = CreateWindowEx(
			0,
			L"BUTTON",
			L"Sign in",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			1000, 350, 150, 50,
			this->hwnd,
			reinterpret_cast<HMENU>(2),
			nullptr,
			nullptr
		); !this->buttonSignUp)
		{
			throw std::runtime_error("Error, cannot create sign up button");
		}

		if (this->buttonClear = CreateWindowEx(
			0,
			L"BUTTON",
			L"Clear",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			1200, 600, 150, 50,
			this->hwnd,
			reinterpret_cast<HMENU>(3),
			nullptr,
			nullptr
		); !this->buttonClear)
		{
			throw std::runtime_error("Error, cannot create clear button");
		}


		if (this->Login = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"EDIT",
			L"",
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			531, 150, 425, 50,
			this->hwnd,
			nullptr,
			nullptr,
			nullptr
		); !this->Login)
		{
			throw std::runtime_error("Error, cannot create Login input box");
		}

		if (this->Password = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"EDIT",
			L"",
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			531, 250, 425, 50,
			this->hwnd,
			nullptr,
			nullptr,
			nullptr
		); !this->Password)
		{
			throw std::runtime_error("Error, cannot create Password input box");
		}
	}
}
