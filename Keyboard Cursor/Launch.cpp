#include<iostream>
#include<C:/Users/Xin/source/repos/Keyboard Cursor/Keyboard Cursor/Control.h>
#include<thread>
#include<chrono>
#include<conio.h>
#include<Windows.h>

void fun(int times) {
	for (int i = 0; i <= times; i++) {
		move(5, 5);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main() {
	using namespace std;
	thread t1(EventControl);
	

	cin.get();
	t1.detach();
}