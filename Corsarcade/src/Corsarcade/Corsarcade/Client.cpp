using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define PONG 0
#define TRON 1
#define PIANO 2
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Winmm.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>   
#include <thread>
#include <windows.h>
#include <mmsystem.h>

//#include "DrawPong.cpp"

int drawPong(double xBall, double yBall, double yPaddleLeft, double yPaddleRight, int winState);
void sendString(char MOTD[32], SOCKET Connection);
string recvString(SOCKET Connection);
void inputsThread(SOCKET Connection, int gameType, int player);
int drawPiano(int keyID, bool state, int player);
int drawTron(double vals[16], int winState);

void playsound2(LPCWSTR result) {
	PlaySound(result, NULL, SND_FILENAME | SND_ASYNC); // SND_FILENAME );//SND_RESOURCE 
}

void playsound(LPCWSTR result) {
	//cout << "ll" << endl;
	thread uu(playsound2, result);
	uu.detach();
}



int main()
{
	//Winsock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
	addr.sin_addr.s_addr = inet_addr("172.26.3.15"); //Address = localhost (this pc)  172.26.2.204  109.228.50.193 172.26.3.15
	addr.sin_port = htons(4200); //Port = 1111
	addr.sin_family = AF_INET; //IPv4 Socket

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL); //Set Connection sockTet
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) //If we are unable to connect...
	{
		MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
		return 0; //Failed to Connect
	}
	cout << "Connected!" << std::endl;
	char gametype[32];
	cout << "p for pong, P for pool, t for tron!" << std::endl;
	cin >> gametype;
	gametype[1] = '\n';
	cout << "sending" << std::endl;
	sendString(gametype, Connection);
	cout << "sent!" << std::endl;

	cout << gametype << std::endl;

	//threading
	int gameType = PONG;
	switch (gametype[0]) {
	case 'p': 
		gameType = PONG;
		break;
	case 'P':
		gameType = PIANO;
		break;
	case 't':
		gameType = TRON;
		break;
	}
	int player = (int)atof(recvString(Connection).c_str());//1 or 2
	
	thread inputs(inputsThread, Connection, gameType, player);


	//pong vars
	int winState = 0;
	//piano  vars
	bool keys[26] = { 0 };

	while (true) {
		if (gameType == TRON) {
			string pongVars = recvString(Connection);
			if (pongVars == "p" || pongVars == "P") {//Upper P is 2 is winner
				//drawPong(vals[0], vals[1], vals[2], vals[3]);
				if ((pongVars == "P" && player == 2) || (pongVars == "p" && player == 1)) {
					winState = 1;
				}
				if ((pongVars == "P" && player == 1) || (pongVars == "p" && player == 2)) {
					winState = -1;
				}
				continue;
			}
			if (pongVars == "PONG") {
				//cout << "yooo" << endl;
				PlaySound(L"D:\\Documents\\p\\Hackathon\\Yhack\\pong.wav", NULL, SND_FILENAME | SND_ASYNC); // SND_FILENAME );//SND_RESOURCE 
				continue;
			}
			if (pongVars == "PING") {
				PlaySound(L"D:\\Documents\\p\\Hackathon\\Yhack\\ping.wav", NULL, SND_FILENAME | SND_ASYNC);
				continue;
			}
			if (pongVars == "START") {
				winState = 0;
			}
			//cout << pongVars << endl;
			double vals[16]{};
			int i = 0;
			while (pongVars.find(' ') != std::string::npos) {
				int pos = pongVars.find(' ');
				//cout << pos << endl;
				vals[i] = atof(pongVars.substr(0, pos).c_str());
				pongVars = pongVars.substr(pos + 1);
				i++;
			}
			vals[i] = atof(pongVars.c_str());
			/*for (int i = 0; i < 16; i++) {
				cout << vals[i] << " ";
			}
			cout << endl;*/
			drawTron(vals,  winState);
			//cout << "trying to read, yo" << endl;
			//drawPong(100,50,30,60);
			//this_thread::sleep_for(chrono::milliseconds(60));
		}
		else if (gameType == PONG) {
			string pongVars = recvString(Connection);
			/*cout << "start: " << pongVars.length() << endl;// << " PONG " << pongVars.compare("PONG") << endl;
			if (pongVars.length() == 5) {
				cout << "start: " << pongVars[0] << endl;
				cout << "start: " << pongVars[1] << endl;
				cout << "start: " << pongVars[2] << endl;
				cout << "start: " << pongVars[3] << endl;
				cout << "start: " << pongVars[4] << endl;
			}
			continue;*/
			if (pongVars.compare("p")==0 || pongVars.compare("P") == 0) {//Upper P is 2 is winner
													 //drawPong(vals[0], vals[1], vals[2], vals[3]);
				if ((pongVars.compare("P") == 0 && player == 2) || (pongVars.compare("p") == 0 && player == 1)) {
					winState = 1;
					cout << "win" << endl;
				}
				if ((pongVars.compare("P") == 0 && player == 1) || (pongVars.compare("p") == 0 && player == 2)) {
					winState = -1;
					cout << "loss" << endl;
				}
				continue;
			}
			//cout <<"after: " << pongVars << endl;
			//cout << pongVars << " " << "PONG" << (pongVars == "PONG") << endl;
			if (pongVars.compare("PONG") == 0) {
				cout << "played pong" << endl;
				//cout << "yooo" << endl;
				PlaySound(L"D:\\Documents\\p\\Hackathon\\Yhack\\pong.wav", NULL, SND_FILENAME | SND_ASYNC); // SND_FILENAME );//SND_RESOURCE 
				continue;
			}
			//cout << pongVars << " " << "PING" << (pongVars == "PING") << endl;
			if (pongVars.compare("PING") == 0) {
				cout << "played ping" << endl;
				PlaySound(L"D:\\Documents\\p\\Hackathon\\Yhack\\ping.wav", NULL, SND_FILENAME | SND_ASYNC);
				continue;
			}
			if (pongVars.compare("START") == 0) {
				winState = 0;
				continue;
			}
			//cout << pongVars << endl;
			double vals[4]{};
			int i = 0;
			while (pongVars.find(' ') != std::string::npos) {
				int pos = pongVars.find(' ');
				//cout << pos << endl;
				vals[i] = atof(pongVars.substr(0, pos).c_str());
				pongVars = pongVars.substr(pos + 1);
				i++;
			}
			vals[i] = atof(pongVars.c_str());
			for (int i = 0; i < 4; i++) {
				cout << vals[i] << " ";
			}
			cout << endl;
			drawPong(vals[0], vals[1], vals[2], vals[3], winState);
			//cout << "trying to read, yo" << endl;
			//drawPong(100,50,30,60);
			//this_thread::sleep_for(chrono::milliseconds(60));
		}
		else if (gameType == PIANO) {
			string pianoVars = recvString(Connection);
			int charID = pianoVars[0] - 'A';
			cout << charID << " " << (pianoVars[2] == 'P') << " " << (pianoVars[1] - '0') << endl;
			drawPiano(charID, (pianoVars[2] == 'P'), pianoVars[1] - '0');
		}

	}
	
}

void sendString(char MOTD[32], SOCKET Connection) {
	char MOTD2[32] = "MSG";
	for (int i = 3; i < 32; i++) {
		MOTD2[i] = MOTD[i - 3];
	}
	//cout << MOTD2 << endl;
	send(Connection, MOTD2, sizeof(MOTD2), NULL); //Receive Message of the Day buffer into MOTD array
}

string recvString(SOCKET Connection) {
	char MOTD[256];
	recv(Connection, MOTD, sizeof(MOTD), NULL); //Receive Message of the Day buffer into MOTD array
	string msg(MOTD);
	msg = msg.substr(0, msg.find('\n')-1);
	//cout <<"input: "<< msg << " " << msg.length()<<endl;
	return msg.substr(0, msg.find('\n')-1);
}