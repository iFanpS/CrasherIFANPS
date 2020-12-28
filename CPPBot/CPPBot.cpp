// CPPBot.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <chrono>
#include "corefunc.h"
#include "userfunc.h"
#include "json.hpp"
#include <string>
#include <windows.h>
#include <direct.h>
#define GetCurrentDir _getcwd

using namespace std;
using json = nlohmann::json;

vector<GrowtopiaBot> bots;

inline bool exists_test(const string& name) {
	ifstream f(name.c_str());
	return f.good();
}

int main() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_BLUE);
	SetConsoleTitleA("FanCrasher By iFanpS");
	init();
	cout << "[ + ] Crasher Recode By iFanpS (C) DrOreo200 And GTNoobs" << endl;
	cout << "[ + ] Help by Clayne" << endl;
	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return errno;
	}

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
	string botDataPath = cCurrentPath + string("\\bot.json");

	if (!exists_test(botDataPath)) {
		cout << "[ ! ] Cannot find bot.json! Please place as same directory." << endl;
		return 0;
	}
	cout << "[ + ] bot.json has been loaded!" << endl;

	ifstream i(botDataPath);
	json j;
	i >> j;

	GrowtopiaBot bot = {
		j["username"], j["password"]
	};
	cout << "=====================================================" << endl;

	bot.gameVersion = j["gameVersion"].get<string>();
	bot.SERVER_HOST = j["iptarget"].get<string>();
	bot.worldName = j["targetWorld"].get<string>();
	bot.ownerUsername = j["ownerUsername"].get<string>();
	bot.SERVER_PORT = j["portserver"].get<int>();

	bot.userInit();
	bots.push_back(bot);

	while (true) {
		bot.eventLoop();
		bot.userLoop();
	}
}
