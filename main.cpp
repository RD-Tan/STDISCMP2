#pragma once
#include <iostream>
#include <vector>
#include "Config.h"
#include "Producer.h"
#include "ConsumerPool.h"
#include "ConfigReader.h"

int main() {
	Config config = readConfig("./config.txt");

	Producer producer(config);
	ConsumerPool consumerPool(producer, config);
	consumerPool.joinAllThreads();

	std::vector<Character> remaining = producer.dumpRemaining();
	if (remaining.size() > 0) {
		std::cout << "Characters that weren't able to form a party:\n";
		for (int i = 0; i < remaining.size(); i++) {
			Character c = remaining[i];
			std::cout << c.name << "(" << classTypeToString(c.classType) << "), ";
		}
	}
	else {
		std::cout << "\nAll characters were allocated to a dungeon.\n";
	}
	return 0;
}