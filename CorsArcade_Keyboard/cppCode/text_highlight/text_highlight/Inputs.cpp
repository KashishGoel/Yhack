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

		if (GetAsyncKeyState(VK_UP) && !up) {
			up = true;
			sendString("U\n", Connection);
		}
		if (!GetAsyncKeyState(VK_UP) && up) {
			up = false;
			sendString("!U\n", Connection);
		}

		if (GetAsyncKeyState(VK_DOWN) && !down) {
			down = true;
			sendString("D\n", Connection);
		}
		if (!GetAsyncKeyState(VK_DOWN) && down) {
			down = false;
			sendString("!D\n", Connection);
		}

		if (GetAsyncKeyState(VK_LEFT) && !left) {
			left = true;
			sendString("L\n", Connection);
		}
		if (!GetAsyncKeyState(VK_LEFT) && left) {
			left = false;
			sendString("!L\n", Connection);
		}

		if (GetAsyncKeyState(VK_RIGHT) && !right) {
			right = true;
			sendString("R\n", Connection);
		}
		if (!GetAsyncKeyState(VK_RIGHT) && right) {
			right = false;
			sendString("!R\n", Connection);
		}
		cout << "thread2" << endl;
		//sendString("hello\n", Connection);
		//this_thread::sleep_for(chrono::milliseconds(1000));
	}

}