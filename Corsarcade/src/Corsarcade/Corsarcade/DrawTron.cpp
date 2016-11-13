// progress.cpp : Defines the entry point for the console application.
//

#include "CUESDK.h"
#pragma comment(lib,"Winmm.lib")
#include <iostream>
#include <algorithm>
#include <thread>
#include <future>
#include <vector>
#include <windows.h>
#include <string>
#include <windows.h>
#include <mmsystem.h>

const char* toString(CorsairError error);


int toNewScale2(double val, double oldMax, double max) {
	int num = (int)((val / oldMax)*max);
	if (num < 0) num = 0;
	if (num >(int)(max - .5))num = (int)(max - .5);
	return num;
}
static int ScreenMap[11][6] = {
	{ 3/*F2*/, 15/*2*/, 26/*Q*/, 38/*A*/, 51/*Z*/, 63/*Alt*/ },
	{ 4,		  16/*3*/, 27, 39, 52, -1 },
	{ 5,		  17/*4*/, 28, 40, 53, -1 },
	{ -1,	  18/*5*/, 29, 41, 54, 65 },
	{ 6/*F5*/, 19/*6*/, 30, 42, 55, 65 },
	{ 7,		  20/*7*/, 31, 43, 56, 65 },
	{ 8,		  21/*8*/, 32, 44, 57, -1 },
	{ 9/*F8*/, 22/*9*/, 33, 45, 58, -1 },
	{ -1,      23/*0*/, 34, 46, 59, 68 },
	{ 10/*F9*/,24/*minus*/, 35/*P*/, 47/*;*/, 60/*?*/ ,69 /*rightGui*/ },
	{ 11/*F10*/,85/*plus*/, 36/*[*/, 48/*'*/, 60/*?*/ ,69 /*rightGui*/ }
};
static int PaddleLeft[5][6] = { { 1,2,13,14,-1,-1 },{ 13,14,25,-1,-1,-1 },{ 25,37,-1,-1,-1,-1 },{ 37, 49,-1,-1,-1,-1 },{ 49, 61,62,-1,-1,-1 }, };
static int PaddleRight[5][6] = { { -1,12,73,-1,-1,87 },{ -1,87,-1,80,-1,81 },{ 80,-1,81,-1,-1,83 },{ -1,83,-1,-1,-1,91 },{ 91,-1 ,-1,-1,70,92 } };

int drawTron(double vals[16], int winState) {
	int head1x = toNewScale2(vals[0], 11, 11);
	int head1y = toNewScale2(vals[1], 6, 6);
	int head2x = toNewScale2(vals[8], 11, 11);
	int head2y = toNewScale2(vals[9], 6, 6);

	CorsairPerformProtocolHandshake();
	if (const auto error = CorsairGetLastError()) {
		std::cout << "Handshake failed: " << toString(error) << std::endl;
		getchar();
		return -1;
	}
	const auto ledPositions = CorsairGetLedPositions();
	if (ledPositions && ledPositions->numberOfLed > 0) {
		std::vector<CorsairLedColor> vec;
		for (auto i = 0; i < ledPositions->numberOfLed; i++) {
			const auto ledPos = ledPositions->pLedPosition[i];
			auto ledColor = CorsairLedColor();
			ledColor.ledId = ledPos.ledId;
			ledColor.r = (winState == -1) ? 255 : 10;
			ledColor.g = (winState == 1) ? 255 : 10;
			ledColor.b = 10;
			/*if (ledPos.ledId == 62) {
			ledColor.r = 255;
			}*/
			if (ledPos.ledId == ScreenMap[head1x][head1y]) {
				ledColor.r = 255;
				ledColor.g = 0;
				ledColor.b = 0;
			}
			if (ledPos.ledId == ScreenMap[head1x-(int)vals[2]][head1y - (int)vals[3]]) {
				ledColor.r = 255;
				ledColor.g = 0;
				ledColor.b = 0;
			}
			if (ledPos.ledId == ScreenMap[head1x - (int)vals[4]][head1y - (int)vals[5]]) {
				ledColor.r = 255;
				ledColor.g = 0;
				ledColor.b = 0;
			}
			if (ledPos.ledId == ScreenMap[head1x - (int)vals[6]][head1y - (int)vals[7]]) {
				ledColor.r = 255;
				ledColor.g = 0;
				ledColor.b = 0;
			}
			vec.push_back(ledColor);
		}
		CorsairSetLedsColors(vec.size(), vec.data());
		//std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
}
