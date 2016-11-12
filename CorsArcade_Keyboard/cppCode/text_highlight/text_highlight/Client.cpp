/*
Author: Pindrought
Date: 11/13/2015
This is the solution for the client that you should have at the end of tutorial 1.
*/

using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>   
#include <thread>
//#include "DrawPong.cpp"

int drawPong(double xBall, double yBall, double yPaddleLeft, double yPaddleRight);
void sendString(char MOTD[256], SOCKET Connection);
string recvString(SOCKET Connection);
void inputsThread(SOCKET Connection);

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
	addr.sin_addr.s_addr = inet_addr("172.26.3.15"); //Address = localhost (this pc)
	addr.sin_port = htons(4200); //Port = 1111
	addr.sin_family = AF_INET; //IPv4 Socket

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL); //Set Connection sockTet
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) //If we are unable to connect...
	{
		MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
		return 0; //Failed to Connect
	}
	cout << "Connected!" << std::endl;


	//threading

	thread inputs(inputsThread, Connection);

	///

	//sendString("hello\n", Connection);
	while (true) {
		string pongVars = recvString(Connection);
		//cout << pongVars << endl;
		double vals[4] {};
		int i = 0;
		while (pongVars.find(' ') != std::string::npos) {
			int pos = pongVars.find(' ');
			//cout << pos << endl;
			vals[i] = atof(pongVars.substr(0, pos).c_str());
			pongVars = pongVars.substr(pos+1);
			i++;
		}
		vals[i] = atof( pongVars.c_str());

		drawPong(vals[0], vals[1], vals[2], vals[3]);
		//cout << "trying to read, yo" << endl;
		//drawPong(100,50,30,60);
		//this_thread::sleep_for(chrono::milliseconds(60));
	}
	while (true)
	{
		Sleep(10);
	}
}

void sendString(char MOTD[256], SOCKET Connection) {
	send(Connection, MOTD, sizeof(MOTD), NULL); //Receive Message of the Day buffer into MOTD array
}

string recvString(SOCKET Connection) {
	char MOTD[256];
	recv(Connection, MOTD, sizeof(MOTD), NULL); //Receive Message of the Day buffer into MOTD array
	string msg(MOTD);
	return msg.substr(0, msg.find('\n'));
}