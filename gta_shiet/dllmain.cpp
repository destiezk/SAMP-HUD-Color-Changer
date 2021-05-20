#include <Windows.h>
#include <thread>
#include <string>

#include <d3d9.h>
#pragma comment(lib, "d3d9")

using namespace std;
bool activated = false;
bool lmb = false;

int a = 255;

int m_r = 252;
int m_g = 108;
int m_b = 133;

void Keys()
{
	static int r = 252;
	static int g = 108;
	static int b = 133;

	for (;;)
	{
		if (GetAsyncKeyState(VK_F10) & 1)
		{
			activated = !activated;
		}

		if (activated)
		{
			if (GetAsyncKeyState(VK_LBUTTON) < 0 && lmb == false)
			{
				lmb = true;
			}
			if (GetAsyncKeyState(VK_LBUTTON) == 0 && lmb == true)
			{
				lmb = false;
			}

			*(DWORD*)(0xBAB22C) = D3DCOLOR_RGBA(r, g, b, a);//*(DWORD*)(0xBAB22C) = D3DCOLOR_RGBA(0, 0, 0, 255);
			*(DWORD*)(0xBAB230) = D3DCOLOR_RGBA(r, g, b, a);
			*(DWORD*)(0xBAB238) = D3DCOLOR_RGBA(r, g, b, a);
			*(DWORD*)(0xBAB244) = D3DCOLOR_RGBA(r, g, b, a);
			*(DWORD*)(0xBAB24C) = D3DCOLOR_RGBA(r, g, b, a);
			*(DWORD*)(0xBAB23C) = D3DCOLOR_RGBA(r, g, b, a);


			/*//HP
			*(uint8_t*)0xBAB22C = r;
			*(uint8_t*)0xBAB22D = g;
			*(uint8_t*)0xBAB22E = b;
			*(uint8_t*)0xBAB22F = a;

			//Money
			*(uint8_t*)0xBAB230 = m_r;
			*(uint8_t*)0xBAB231 = m_g;
			*(uint8_t*)0xBAB232 = m_b;
			*(uint8_t*)0xBAB233 = a;

			//Ammo
			*(uint8_t*)0xBAB239 = r;
			*(uint8_t*)0xBAB23A = g;
			*(uint8_t*)0xBAB23B = b;
			*(uint8_t*)0xBAB23C = a;*/
		}
	}
}

void Effect()
{
	for (;;)
	{
		if (!activated)
			continue;

		if (lmb)
		{
			for (a = 255; a > 0; a--)
				std::this_thread::sleep_for(chrono::microseconds(500));

			for (a = 0; a < 255; a++)
				std::this_thread::sleep_for(chrono::microseconds(500));
		}
	}
}

void alternative()
{
	for (;;)
	{
		if (!activated)
			continue;

		static int clr = 0;

		if (lmb)
		{
			//fade out
			for (clr = 255; clr > 0; clr--)
			{
				if (clr <= 252)
					m_r--;

				if (clr <= 108)
					m_g--;

				if (clr <= 133)
					m_b--;


				std::this_thread::sleep_for(chrono::microseconds(300));
			}

			//fade in
			for (clr = 0; clr < 255; clr++)
			{
				if (clr <= 252)
					m_r++;

				if (clr <= 108)
					m_g++;

				if (clr <= 133)
					m_b++;

				std::this_thread::sleep_for(chrono::microseconds(300));
			}

			m_r = 252;
			m_g = 108;
			m_b = 133;
		}
	}
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		new std::thread(Keys);
		new std::thread(Effect);

		new std::thread(alternative);
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}