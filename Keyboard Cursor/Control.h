#ifndef CONTROL_H
#define CONTROL_H
#include<Windows.h>
#include<iostream>
#include<thread>
#include<chrono>
// Window's key detection methods
// https://docs.microsoft.com/en-us/windows/win32/learnwin32/keyboard-input

auto sleeptime = std::chrono::milliseconds(50); // time inbetween each cursor position change
int diff = 7; // the difference in the y/x coordinate per movement
int boost = 10;

void move(int dx, int dy) {
	using namespace std;
	POINT currentCoord;
	GetCursorPos(&currentCoord);
	SetCursorPos(currentCoord.x + dx, currentCoord.y + dy); // new x,y = current x + dx, current y + dy
}

void EventControl() {
	using namespace std;
	INPUT leftclick;
	leftclick.type = INPUT_MOUSE;
	leftclick.mi.dwFlags = (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP);
	leftclick.mi.mouseData = 0;
	leftclick.mi.dwExtraInfo = NULL;
	leftclick.mi.time = 0;

	INPUT rightclick = leftclick;
	rightclick.mi.dwFlags = (MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP);

	INPUT f10;
	WORD vkey = VK_F10;
	f10.type = INPUT_KEYBOARD;
	f10.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	f10.ki.time = 0;
	f10.ki.dwExtraInfo = 0;
	f10.ki.wVk = vkey;
	f10.ki.dwFlags = 0; 

	INPUT keyup = f10;
	keyup.ki.dwFlags = (KEYEVENTF_KEYUP);

	bool select = true;
	

	while (true) {
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) {
			select = true;
		}
		int tdiff = (GetKeyState(VK_LSHIFT) & 0x8000) ? diff + boost : diff; // if shift is pressed, add boost to diff
		if (GetKeyState(VK_CAPITAL) == 1) { // state of caps lock == 1 if it is toggled
			if (select) { // deselect everything
				SendInput(1, &f10, sizeof(INPUT));
				select = false;
			}
			
			if ((GetKeyState(0x41) & 0x8000 || GetKeyState(0x4A) & 0x8000) &&
				(GetKeyState(0x57) & 0x8000 || GetKeyState(0x49) & 0x8000)) { // left-up
				move(-tdiff, -tdiff);
				this_thread::sleep_for(sleeptime);
			}
			else if ((GetKeyState(0x44) & 0x8000 || GetKeyState(0x4C) & 0x8000) &&
					 (GetKeyState(0x57) & 0x8000 || GetKeyState(0x49) & 0x8000)) { // right-up
				move(tdiff, -tdiff);
				this_thread::sleep_for(sleeptime);
			}
			else if ((GetKeyState(0x41) & 0x8000 || GetKeyState(0x4A) & 0x8000) &&
					 (GetKeyState(0x53) & 0x8000 || GetKeyState(0x4B) & 0x8000)) { // left-down
				move(-tdiff, tdiff);
				this_thread::sleep_for(sleeptime);
			}
			else if ((GetKeyState(0x44) & 0x8000 || GetKeyState(0x4C) & 0x8000) && 
					 (GetKeyState(0x53) & 0x8000 || GetKeyState(0x4B) & 0x8000)) { // right-down
				move(tdiff, tdiff);
				this_thread::sleep_for(sleeptime);

			}
			else if (GetKeyState(0x41) & 0x8000 || GetKeyState(0x4A) & 0x8000) { // 'a' or 'j' pressed
				move(-tdiff, 0);
				this_thread::sleep_for(sleeptime);
			}
			else if (GetKeyState(0x44) & 0x8000 || GetKeyState(0x4C) & 0x8000) { // 'd' or 'l' pressed
				move(tdiff, 0);
				this_thread::sleep_for(sleeptime);
			}
			else if (GetKeyState(0x57) & 0x8000 || GetKeyState(0x49) & 0x8000) { // 'w' or 'i' pressed
				move(0, -tdiff);
				this_thread::sleep_for(sleeptime);
			}
			else if (GetKeyState(0x53) & 0x8000 || GetKeyState(0x4B) & 0x8000) { // 's' or 'k' pressed
				move(0, tdiff);
				this_thread::sleep_for(sleeptime);
			}

			if (GetKeyState(0x51) & 0x8000 || GetKeyState(0x55) & 0x8000) { // 'q' or 'u' pressed = left-mouse-button
				SendInput(1, &leftclick, sizeof(INPUT));
				this_thread::sleep_for(chrono::milliseconds(300));
			}
			if (GetKeyState(0x45) & 0x8000 || GetKeyState(0x4F) & 0x8000) { // 'e' or 'o' pressed = right-mouse-button
				SendInput(1, &rightclick, sizeof(INPUT));
				this_thread::sleep_for(chrono::milliseconds(300));
			}
			
		}
		else {
			select = true;
		}
		if (GetKeyState(VK_F10) & 0x8000) {
			SendInput(1, &keyup, sizeof(INPUT));
		}


	}
}


#endif