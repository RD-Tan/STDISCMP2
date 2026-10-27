#pragma once
#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <random>
#include "Config.h"
#include "Producer.h"

class ConsumerPool
{
private:
	Producer& producer;
	std::vector<std::thread> threads;

	// rng things
	std::random_device rd; 
	std::mt19937 gen;       
	std::uniform_int_distribution<int> dist;


	void run(int i);

public:
	ConsumerPool(Producer& producer, Config config);
	~ConsumerPool();




};

