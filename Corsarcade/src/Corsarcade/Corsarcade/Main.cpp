//// progress.cpp : Defines the entry point for the console application.
////
//
//#include "CUESDK.h"
//
//#include <iostream>
//#include <algorithm>
//#include <thread>
//#include <future>
//#include <vector>
//#include <windows.h>
//#include <string>
//
//const char* toString(CorsairError error)
//{
//	switch (error) {
//	case CE_Success:
//		return "CE_Success";
//	case CE_ServerNotFound:
//		return "CE_ServerNotFound";
//	case CE_NoControl:
//		return "CE_NoControl";
//	case CE_ProtocolHandshakeMissing:
//		return "CE_ProtocolHandshakeMissing";
//	case CE_IncompatibleProtocol:
//		return "CE_IncompatibleProtocol";
//	case CE_InvalidArguments:
//		return "CE_InvalidArguments";
//	default:
//		return "unknown error";
//	}
//}
//
//double getKeyboardWidth(CorsairLedPositions *ledPositions)
//{
//	const auto minmaxLeds = std::minmax_element(ledPositions->pLedPosition, ledPositions->pLedPosition + ledPositions->numberOfLed,
//		[](const CorsairLedPosition &clp1, const CorsairLedPosition &clp2) {
//		return clp1.left < clp2.left;
//	});
//	return minmaxLeds.second->left + minmaxLeds.second->width - minmaxLeds.first->left;
//}
//struct boxPos {
//	int x;
//	int y;
//};
//
//int main()
//{	
//
//	CorsairPerformProtocolHandshake();
//	if (const auto error = CorsairGetLastError()) {
//		std::cout << "Handshake failed: " << toString(error) << std::endl;
//		getchar();
//		return -1;
//	}
//	int numPadKeyCodes[] = { 119, 116, 117, 118, 113, 115, 109, 110, 111 };
//	int boardMap[10][4] = {
//		{ 14, 26, 38, 51 },
//		{ 15, 27, 39, 52 },
//		{ 16, 28, 40, 53 },
//		{ 17, 29, 41, 54 },
//		{ 18, 30, 42, 55 },
//		{ 19, 31, 43, 56 },
//		{ 20, 32, 44, 57 },
//		{ 21, 33, 45, 58 },
//		{ 22, 34, 46, 59 },
//		{ 23, 35, 47, 60 }
//	};
//	const auto ledPositions = CorsairGetLedPositions();
//	std::cout << "Press Escape to quit\n";
//	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//	if (ledPositions && ledPositions->numberOfLed > 0) {
//		struct boxPos box = { 0,0 }; 
//		std::vector<CorsairLedColor> vec;
//		while (!GetAsyncKeyState(VK_ESCAPE)) {
//			if (GetAsyncKeyState(VK_DOWN))
//				if (box.y + 1 < 4) 
//					box.y++;
//			if (GetAsyncKeyState(VK_UP))
//				if (box.y - 1 >= 0)
//					box.y--;
//			if (GetAsyncKeyState(VK_RIGHT))
//				if (box.x + 1 < 10)
//					box.x++;
//			if (GetAsyncKeyState(VK_LEFT))
//				if (box.x - 1 >= 0)
//					box.x--;
//			vec.clear();
//			for (auto i = 0; i < ledPositions->numberOfLed; i++) {
//				const auto ledPos = ledPositions->pLedPosition[i];
//				auto ledColor = CorsairLedColor();
//				ledColor.ledId = ledPos.ledId;
//				ledColor.b = 55;
//				if (ledColor.ledId == boardMap[box.x][box.y]) {
//					ledColor.g = 255;
//					ledColor.r = 255;
//				}
//				vec.push_back(ledColor);
//			}
//			CorsairSetLedsColors(vec.size(), vec.data());
//			/*for (int key = 0; key < 10; key++) {
//				std::vector<CorsairLedColor> vec;
//				vec.clear();
//				for (auto i = 0; i < ledPositions->numberOfLed; i++) {
//					const auto ledPos = ledPositions->pLedPosition[i];
//					auto ledColor = CorsairLedColor();
//					ledColor.ledId = ledPos.ledId;
//					if (ledColor.ledId == numPadKeyCodes[key])
//						ledColor.r = 255;
//					ledColor.b = 255;
//					vec.push_back(ledColor);
//				}
//				CorsairSetLedsColors(vec.size(), vec.data());
//				std::this_thread::sleep_for(std::chrono::milliseconds(50));
//			}*/
//			std::this_thread::sleep_for(std::chrono::milliseconds(100));
//		}
//	}
//}
//
