// progress.cpp : Defines the entry point for the console application.
//

using namespace std;
#include "CUESDK.h"

#include <iostream>
#include <thread>
#include <string>

const char* errorToString(CorsairError error)
{
switch (error) {
case CE_Success :
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

void highlightKey(CorsairLedId ledId)
{
for (auto x = .0; x < 2; x += .1) {
auto val = (1 - abs(x - 1)) * 255;
auto ledColor = CorsairLedColor{ ledId, val, val, val };
CorsairSetLedsColors(1, &ledColor);
this_thread::sleep_for(chrono::milliseconds(30));
}
}

int simon()
{
CorsairPerformProtocolHandshake();

if (const auto error = CorsairGetLastError()) {
cout << "Handshake failed: " << errorToString(error) << endl;
getchar();
return -1;
}
CorsairRequestControl(CAM_ExclusiveLightingControl);

auto seq = string();
seq = "";
bool alive = true;

while (alive) {
for (const auto &symbol : seq) {
auto ledId = CorsairGetLedIdForKeyName(symbol);
if (ledId != CLI_Invalid)
highlightKey(ledId);
}

cin >> seq;
}


/*cout << "Please, input a word... ";
auto userInputStr = string();
cin >> userInputStr;

userInputStr = "cosmos";

for (const auto &symbol : userInputStr) {
auto ledId = CorsairGetLedIdForKeyName(symbol);
if (ledId != CLI_Invalid)
highlightKey(ledId);
}*/
return 0;
}