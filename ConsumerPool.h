#pragma once
#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <random>
#include <atomic>
#include <syncstream>
#include <condition_variable>
#include "Config.h"
#include "Producer.h"

class ConsumerPool
{
private:
	Producer& producer;
	std::vector<std::thread> threads;
	std::atomic<bool> isShutdown;

	void run(int i, Config config);

public:
	ConsumerPool(Producer& producer, Config config);
	~ConsumerPool() = default;
	
	void joinAllThreads();
};

