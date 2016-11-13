// progress.cpp : Defines the entry point for the console application.
//

#include "CUESDK.h"

#include <iostream>
#include <algorithm>
#include <thread>
#include <future>
#include <vector>
#include <windows.h>
#include <string>

const char* toString(CorsairError error)
{
	switch (error) {
	case CE_Success:
		return "CE_Success";
	case CE_ServerNotFound:
		return "CE_ServerNotFound";
	case CE_NoControl:
		return "CE_NoControl";
	case CE_ProtocolHandshakeMissing:
		return "CE_ProtocolHandshakeMissing";
	case CE_IncompatibleProtocol:
		return "CE_IncompatibleProtocol";
	case CE_InvalidArguments:
		return "CE_InvalidArguments";
	default:
		return "unknown error";
	}
}

double getKeyboardWidth(CorsairLedPositions *ledPositions)
{
	const auto minmaxLeds = std::minmax_element(ledPositions->pLedPosition, ledPositions->pLedPosition + ledPositions->numberOfLed,
		[](const CorsairLedPosition &clp1, const CorsairLedPosition &clp2) {
		return clp1.left < clp2.left;
	});
	return minmaxLeds.second->left + minmaxLeds.second->width - minmaxLeds.first->left;
}

double getKeyboardHeight(CorsairLedPositions *ledPositions)
{
	const auto minmaxLeds = std::minmax_element(ledPositions->pLedPosition, ledPositions->pLedPosition + ledPositions->numberOfLed,
		[](const CorsairLedPosition &clp1, const CorsairLedPosition &clp2) {
		return clp1.top < clp2.top;
	});
	return minmaxLeds.second->top + minmaxLeds.second->height - minmaxLeds.first->top;
}

int toNewScale(double val, double oldMax, double max) {
	return (int)((val / oldMax)*max);
}
static int ScreenMap[10][5] = {
	{ 15, 26, 38, 51, 63 },
	{ 16, 27, 39, 52, 65 },
	{ 17, 28, 40, 53, 65 },
	{ 18, 29, 41, 54, 65 },
	{ 19, 30, 42, 55, 65 },
	{ 20, 31, 43, 56, 65 },
	{ 21, 32, 44, 57, 65 },
	{ 22, 33, 45, 58, 65 },
	{ 23, 34, 46, 59, 65 },
	{ 24, 35, 47, 60 ,68 }
};
static int PaddleLeft[4] = { 13, 25, 37, 49,};
static int PaddleRight[4] = {  24, 36, 48, 60};
int drawPong(double xBall, double yBall, double yPaddleLeft, double yPaddleRight) {
	int xB = toNewScale(xBall, 15, 9);
	int yB = toNewScale(yBall, 5, 4);
	int yPL = toNewScale(yPaddleLeft, 6, 3);
	int yPR = toNewScale(yPaddleRight, 6, 3);
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
			ledColor.b = 10;
			ledColor.r = 10;
			ledColor.g = 10;
			if (ledPos.ledId == ScreenMap[xB][yB]) {
				ledColor.r = 255;
			}
			if (ledPos.ledId == PaddleLeft[yPL]) {
				ledColor.g = 255;
			}
			if (ledPos.ledId == PaddleRight[yPR]) {
				ledColor.g = 255;
			}
			vec.push_back(ledColor);
		}
		CorsairSetLedsColors(vec.size(), vec.data());
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
}
int drawPongmap(double xBall, double yBall, double yPaddleLeft, double yPaddleRight)
{
	std::cout << "vals: " << xBall << " " << yBall << " " << yPaddleLeft << " " << yPaddleRight << std::endl;
	xBall = toNewScale(xBall, 15, 274);
	yBall = toNewScale(yBall, 6, 274);
	yPaddleLeft = toNewScale(yPaddleLeft, 6, 133);
	yPaddleRight = toNewScale(yPaddleRight, 6, 133);
	double xPaddleLeft = 0;
	double xPaddleRight = 270;

	CorsairPerformProtocolHandshake();
	if (const auto error = CorsairGetLastError()) {
		std::cout << "Handshake failed: " << toString(error) << std::endl;
		getchar();
		return -1;
	}

	const auto ledPositions = CorsairGetLedPositions();
	if (ledPositions && ledPositions->numberOfLed > 0) {

		//std::cout << "test2"<< std::endl;

		//std::cout << "Working... Press Escape to close program...";
		//for (auto n = 0; !GetAsyncKeyState(VK_ESCAPE); n++) {

		std::vector<CorsairLedColor> vec;

		int bestLedBall = 0;
		double bestDistBall = 1000;
		int bestLedLeftPaddle = 0;
		double bestDistLeftPaddle = 1000;
		int bestLedRightPaddle = 0;
		double bestDistRightPaddle = 1000;

		for (auto i = 0; i < ledPositions->numberOfLed; i++) {
			const auto ledPos = ledPositions->pLedPosition[i];
			double x = ledPos.left - xBall + ledPos.width / 2.0;
			double y = ledPos.top - yBall + ledPos.height / 2.0;
			double dist = x*x + y*y;
			if (dist < bestDistBall) {
				bestDistBall = dist;
				bestLedBall = i;
			}
			if (dist < bestDistLeftPaddle) {
				bestDistLeftPaddle = dist;
				bestLedLeftPaddle = i;
			}
			if (dist < bestDistRightPaddle) {
				bestDistRightPaddle = dist;
				bestLedRightPaddle = i;
			}
		}
		while (true) {
			auto userInputStr = std::string();
			std::cin >> userInputStr;
			int value = atoi(userInputStr.c_str());
			std::cout << "top: " << ledPositions->pLedPosition[value].top << std::endl;
			std::cout << "top: " << ledPositions->pLedPosition[value].top << std::endl;
			std::cout << "left: " << ledPositions->pLedPosition[value].left << std::endl;
			std::cout << "height: " << ledPositions->pLedPosition[value].height << std::endl;
			std::cout << "width: " << ledPositions->pLedPosition[value].width << std::endl;
		}
		//std::cout << "test3" << std::endl;

		//std::cout << currWidth << " " << currHeight << std::endl;
		const auto ledPos = ledPositions->pLedPosition[bestLedBall];
		std::cout << "\t" << bestLedBall << " " << ledPos.left + ledPos.width / 2.0 << " " << ledPos.top + ledPos.height / 2.0 << std::endl;

		for (auto i = 0; i < ledPositions->numberOfLed; i++) {
			const auto ledPos = ledPositions->pLedPosition[i];
			auto ledColor = CorsairLedColor();
			ledColor.ledId = ledPos.ledId;
			//	if (ledPos.left < currWidth)
			if (i == bestLedBall)
			{
				ledColor.r = 255;
				ledColor.g = 0;
				ledColor.b = 255;
			}
			else if (i == bestDistLeftPaddle) {
				ledColor.r = 255;
				ledColor.g = 0;
				ledColor.b = 0;
			}
			else if (i == bestDistRightPaddle) {
				ledColor.r = 0;
				ledColor.g = 255;
				ledColor.b = 0;
			}
			else {
				ledColor.r = 255;
				ledColor.g = 255;
				ledColor.b = 0;
			}

			vec.push_back(ledColor);
		}

		//std::cout << "test4" << std::endl;

		CorsairSetLedsColors(vec.size(), vec.data());

		//std::cout << "test5" << std::endl;

		//}
	}
	return 0;
}

