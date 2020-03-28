#ifndef CONTROL_H
#define CONTROL_H
#include<Windows.h>
#include<iostream>
#include<thread>
// Window's key detection methods
// https://docs.microsoft.com/en-us/windows/win32/learnwin32/keyboard-input

void move(int dx, int dy) {
	using namespace std;
	POINT currentCoord;
	GetCursorPos(&currentCoord);
	SetCursorPos(currentCoord.x + dx, currentCoord.y + dy); // new x,y = current x + dx, current y + dy
}

void EventControl() {
	using namespace std; ////

	while (true) {
		if (GetKeyState(VK_CAPITAL) == 1) { // state of caps lock == 1 if it is toggled
			if (GetKeyState(0x41) & 0x8000 || GetKeyState(0x4A) & 0x8000)// 'a' or 'j' pressed
				cout << "here";
		}
	}
}


#endif