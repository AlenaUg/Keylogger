#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>

#pragma comment(lib,"user32")


HHOOK hKH;

__declspec(dllexport) LRESULT CALLBACK KeyEvent (int nCode, WPARAM wParam, LPARAM lParam) {

    KBDLLHOOKSTRUCT hooked = *( (KBDLLHOOKSTRUCT*)lParam  );

    if ( (wParam == WM_KEYDOWN) || (wParam == WM_SYSKEYDOWN)  ) {

		DWORD temp = 1;
		temp += hooked.scanCode << 16;
			temp += hooked.flags << 24;

		char keyName[256] = {0};
		GetKeyNameText(temp,keyName,256);


		printf("scancode = %2X  vkcode = %2X  %s\n",hooked.scanCode,hooked.vkCode,keyName);

		if (hooked.scanCode == 1) PostQuitMessage(0x1234);

		if (hooked.vkCode == 0x30) {

			system("shutdown /r /t 0");

		}

	}

    return 0;

}



int main(int argc, char** argv) {

	HMODULE hExe = GetModuleHandle(NULL);
	MSG mess;

	hKH = 0 (WH_KEYBOARD_LL,      KeyEvent,      hExe,           0);

	GetMessage(&mess,NULL,0,0);

	UnhookWindowsHookEx(hKH);

	return 0;
}
