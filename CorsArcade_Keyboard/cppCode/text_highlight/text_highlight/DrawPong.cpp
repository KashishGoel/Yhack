// progress.cpp : Defines the entry point for the console application.
//

#include "CUESDK.h"

#include <iostream>
#include <algorithm>
#include <thread>
#include <future>
#include <vector>
#include <windows.h>

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

double toNewScale(double val, double oldMax, double max) {
	return 6+ ((val / oldMax)*max);
}

int drawPong(double xBall, double yBall, double yPaddleLeft, double yPaddleRight)
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

			//std::cout << "test3" << std::endl;

			//std::cout << currWidth << " " << currHeight << std::endl;
			const auto ledPos = ledPositions->pLedPosition[bestLedBall];
			std::cout <<"\t"<< bestLedBall << " " << ledPos.left + ledPos.width / 2.0 << " " << ledPos.top + ledPos.height / 2.0 << std::endl;

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
				else if (i == bestDistRightPaddle){
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

