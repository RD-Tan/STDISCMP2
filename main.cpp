#include <iostream>
#include "Config.h"
#include "Producer.h"
#include "ConsumerPool.h"
int main() {
	Config config;
	config.numConsumers = 5;
	config.minWaitTime = 1;
	config.maxWaitTime = 6;
	config.totalParties = 100;

	Producer producer(config.totalParties);
	ConsumerPool consumerPool(producer, config);

	std::cout << "Hello World!" << std::endl;
	return 0;
}