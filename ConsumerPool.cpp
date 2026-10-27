#include "ConsumerPool.h"

ConsumerPool::ConsumerPool(Producer& producer, Config config) : producer(producer) {
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(config.minWaitTime, config.maxWaitTime);

	for (int i = 0; i < config.totalParties; ++i) {
		threads.emplace_back(&ConsumerPool::run, this, i);
	}
}

ConsumerPool::~ConsumerPool() {
	for (auto& thread : threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}
}

void ConsumerPool::run(int i) {
	while (true) {
		Character dps = producer.popDPS();
		Character tank = producer.popTank();
		Character healer = producer.popHealer();
		if (dps.id == -1 && tank.id == -1 && healer.id == -1) {
			break; // No more characters to process
		}
		if (dps.id != -1) {
			std::cout << "cConsumed DPS: " << dps.name << std::endl;
		}
		if (tank.id != -1) {
			std::cout << "Consumed Tank: " << tank.name << std::endl;
		}
		if (healer.id != -1) {
			std::cout << "Consumed Healer: " << healer.name << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::seconds(dist(gen)));
	}
}