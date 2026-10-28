#pragma once
#include <mutex>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include "Character.h"
#include "Config.h"

class Producer
{
private:
	std::mutex partyM;

	std::queue<Character> dpsQueue;
	std::queue<Character> tankQueue;
	std::queue<Character> healerQueue;

public:
	Producer(Config config);
	~Producer() = default;

	bool tryAcquireParty(std::vector<Character>& newParty);
	std::vector<Character> dumpRemaining();
};

