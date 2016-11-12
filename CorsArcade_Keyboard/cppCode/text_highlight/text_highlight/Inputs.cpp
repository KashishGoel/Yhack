using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>   
#include <thread>

void sendString(char MOTD[256], SOCKET Connection);



void inputsThread(SOCKET Connection) {
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	while (true) {

		if (GetAsyncKeyState(VK_UP) && !upp) {
			upp = true;
			sendString("U\n", Connection);
		}
		if (!GetAsyncKeyState(VK_UP) && upp) {
			upp = false;
			sendString("!U\n", Connection);
		}

		if (GetAsyncKeyState(VK_DOWN) && !downn) {
			downn = true;
			sendString("U\n", Connection);
		}
		if (!GetAsyncKeyState(VK_DOWN) && downn) {
			downn = false;
			sendString("!U\n", Connection);
		}

		if (GetAsyncKeyState(VK_LEFT) && !left) {
			left = true;
			sendString("U\n", Connection);
		}
		if (!GetAsyncKeyState(VK_LEFT) && left) {
			left = false;
			sendString("!U\n", Connection);
		}

		if (GetAsyncKeyState(VK_RIGHT) && !right) {
			right = true;
			sendString("U\n", Connection);
		}
		if (!GetAsyncKeyState(VK_RIGHT) && right) {
			right = false;
			sendString("!U\n", Connection);
		}
		cout << "thread2" << endl;
		//sendString("hello\n", Connection);
		//this_thread::sleep_for(chrono::milliseconds(1000));
	}

}