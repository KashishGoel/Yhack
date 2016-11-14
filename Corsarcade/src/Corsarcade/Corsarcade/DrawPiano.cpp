// progress.cpp : Defines the entry point for the console application.
//
using namespace std;

#include "CUESDK.h"

#include <iostream>
#include <algorithm>
#include <thread>
#include <future>
#include <vector>
#include <windows.h>
#include <string>
#include <mmsystem.h>

const char* toString(CorsairError error);


static char keys[2][26] = { 0 };

void playsound(LPCWSTR result);

int orderToKeyboard(int keyID) {
	int key = CorsairGetLedIdForKeyName('A' + keyID);
	if (key >= 26 && key <= 35) {
		key -= 26;
	}
	if (key >= 38 && key <= 46) {
		key -= 38;
		key += 1+ 35 - 26;
	}
	if (key >= 51 && key <= 57) {
		key -= 51;
		key += 1+ 35 - 26;
		key += 1 + 46 - 38;
	}
	return key;
}

int drawPiano(int keyID, bool state, int player) {
	std::cout << (player - 1) << " " << keyID << std::endl;
	keys[player-1][keyID] = state;

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
			ledColor.r = 0;
			ledColor.g = 0;
			ledColor.b = 0;
			/*if (ledPos.ledId == 62) {
			ledColor.r = 255;
			}*/
			for (int c = 0; c < 26; c++) {
				if (ledPos.ledId == CorsairGetLedIdForKeyName('A' + c)) {
					ledColor.r = 255;
					ledColor.g = 255;
					ledColor.b = 255;
				}
				if (keys[0][c] && keys[1][c] && ledPos.ledId == CorsairGetLedIdForKeyName('A' + c)) {
					ledColor.r = 255;
					ledColor.g = 0;
					ledColor.b = 255;
				}
				else if (keys[0][c] && ledPos.ledId == CorsairGetLedIdForKeyName('A'+c)) {
					ledColor.r = 255;
					ledColor.g = 0;
					ledColor.b = 0;
				}
				else if (keys[1][c] && ledPos.ledId == CorsairGetLedIdForKeyName('A' + c)) {
					ledColor.r = 0;
					ledColor.g = 0;
					ledColor.b = 255;
				}
			}
			vec.push_back(ledColor);
		}
		CorsairSetLedsColors(vec.size(), vec.data());
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	if (state) {
		string file = "C:\\Users\\George\\Desktop\\";
		file += to_string(orderToKeyboard(keyID));
		file += ".WAV";
		cout << "played" << endl;
		int len;
		int slength = (int)file.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, file.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, file.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		LPCWSTR result = r.c_str();
		playsound(result);

	}
}
