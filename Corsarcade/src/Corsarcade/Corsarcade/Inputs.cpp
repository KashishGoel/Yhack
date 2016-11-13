using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>   
#include <thread>

void sendString(char MOTD[32], SOCKET Connection);



void inputsThread(SOCKET Connection) {
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	//sendString("Hello\n", Connection);
	while (true) {

		if (GetAsyncKeyState(VK_UP) && !up) {
			up = true;
			sendString("UpPressed\n", Connection);
		}
		else if (!GetAsyncKeyState(VK_UP) && up) {
			up = false;
			sendString("UpReleased\n", Connection);
		}

		else if (GetAsyncKeyState(VK_DOWN) && !down) {
			down = true;
			sendString("DownPressed\n", Connection);
		}
		else if (!GetAsyncKeyState(VK_DOWN) && down) {
			down = false;
			sendString("DownReleased\n", Connection);
		}

		/*	else if (GetAsyncKeyState(VK_LEFT) && !left) {
		left = true;
		sendString("Left\n", Connection);
		}
		else if (!GetAsyncKeyState(VK_LEFT) && left) {
		left = false;
		sendString("!L\n", Connection);
		}

		else if (GetAsyncKeyState(VK_RIGHT) && !right) {
		right = true;
		sendString("R\n", Connection);
		}
		else if (!GetAsyncKeyState(VK_RIGHT) && right) {
		right = false;
		sendString("!R\n", Connection);
		}*/
		//	//cout << "thread2" << endl;
		//	//sendString("hello\n", Connection);
		//	this_thread::sleep_for(chrono::milliseconds(15));
	}

}