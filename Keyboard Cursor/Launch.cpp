#include<iostream>
#include<C:/Users/Xin/source/repos/Keyboard Cursor/Keyboard Cursor/Control.h>
#include<thread>
#include<chrono>
#include<conio.h>
#include<Windows.h>


int main() {
	using namespace std;
	thread t1(EventControl);

	cin.get();
	t1.detach();
}