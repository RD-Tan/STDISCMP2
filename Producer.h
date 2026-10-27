#pragma once
#include <mutex>
#include <queue>
#include "Character.h"

class Producer
{
private:
	std::mutex dpsM;
	std::mutex tankM;
	std::mutex healerM;

	std::queue<Character> dpsQueue;
	std::queue<Character> tankQueue;
	std::queue<Character> healerQueue;

public:
	Producer(unsigned long totalParties);
	~Producer() = default;

	Character popDPS();
	Character popTank();
	Character popHealer();

};

