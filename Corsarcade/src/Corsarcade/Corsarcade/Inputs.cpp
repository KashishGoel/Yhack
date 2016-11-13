using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define PONG 0
#define PIANO 2

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <Windows.h>
#include <string>   
#include <thread>

void sendString(char MOTD[32], SOCKET Connection);
int drawPiano(int keyID, bool state, int player);

void inputsThread(SOCKET Connection, int gameType, int player) {
	if (gameType == PONG) {
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
	} else if (gameType == PIANO) {
		bool chars[26]{};
		while (true) {
			for (int i = 0; i < 26; i++) {
				if (GetAsyncKeyState('A' + i) && !chars[i]) {
					chars[i] = true;
					string msg(1,(char)('A' + i));
					msg += to_string(player);
					msg += "Pressed\n";
					char tab2[16];
					strcpy_s(tab2, msg.c_str());
					drawPiano(i, true, player);
					sendString(tab2, Connection);
				}
				else if (!GetAsyncKeyState('A' + i) && chars[i]) {
					chars[i] = false;
					string msg(1, (char)('A' + i));
					msg += to_string(player);
					msg += "Released\n";
					char tab2[16];
					strcpy_s(tab2, msg.c_str());
					drawPiano(i, false, player);
					sendString(tab2, Connection);
				}
			}
		}
		/*HANDLE rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console

		DWORD Events = 0;     // Event count
		DWORD EventsRead = 0; // Events read from console

		bool Running = true;

		//programs main loop
		while (Running) {

			// gets the systems current "event" count
			GetNumberOfConsoleInputEvents(rhnd, &Events);

			if (Events != 0) { // if something happened we will handle the events we want

							   // create event buffer the size of how many Events
				INPUT_RECORD eventBuffer[10];

				// fills the event buffer with the events and saves count in EventsRead
				ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);

				// loop through the event buffer using the saved count
				for (DWORD i = 0; i < 10; ++i) {
					if (eventBuffer[i].EventType > 3) continue;
					// check if event[i] is a key event && if so is a press not a release
					if (eventBuffer[i].EventType == KEY_EVENT) {
						if (eventBuffer[i].Event.KeyEvent.bKeyDown) {
							char c = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
							if (c >= 'A' && c <= 'Z') {
								i = c - 'A';
								if (!chars[i]) {
									chars[i] = true;
									cout << "on" << endl;
									string msg(1, (char)('A' + i));
									msg += to_string(player);
									msg += "Pressed\n";
									char tab2[16];
									strcpy_s(tab2, msg.c_str());
									drawPiano(i, true, player);
									sendString(tab2, Connection);
								}
							}
						}
						else {
							char c = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
							if (c >= 'A' && c <= 'Z') {
								i = c - 'A';
								if (chars[i]) {
									chars[i] = false;
									cout << "off" << endl;
									string msg(1, (char)('A' + i));
									msg += to_string(player);
									msg += "Released\n";
									char tab2[16];
									strcpy_s(tab2, msg.c_str());
									drawPiano(i, false, player);
									sendString(tab2, Connection);
								}
							}
						}
					}

				} // end EventsRead loop

			}

		}*/





	}

}