#include "ConsumerPool.h"

ConsumerPool::ConsumerPool(Producer& producer, Config config) : producer(producer) {
	isShutdown = false;
	for (int i = 0; i < config.numConsumers; ++i) {
		threads.emplace_back(&ConsumerPool::run, this, i, config);
	}
}

void ConsumerPool::joinAllThreads() {
	for (auto& thread : threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}
}

void ConsumerPool::run(int id, Config config) {
	// each thread gets its own random stuff.
	// giving it to the class seems to cause weird things to happen.
	// and adding a mutex seems like a dumb thing to do since that'll just add overhead.
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(config.minWaitTime, config.maxWaitTime);
	while (!isShutdown) {
		std::vector<Character> party;
		bool success = producer.tryAcquireParty(party);

		if (!success) {
			isShutdown = true;
			std::osyncstream(std::cout) << "[Dungeon " << id << " ] Terminating. Not enough resources." << std::endl;
			break;
		}

		std::string partyInfo;
		for (Character c: party) {
			partyInfo += classTypeToString(c.classType) + ": " + c.name + "\n";
		}
		std::osyncstream(std::cout) << "[Dungeon " << id << "] Party gathered.\n" << partyInfo << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(dist(gen)));
		if (isShutdown) {
			std::osyncstream(std::cout) << "[Dungeon " << id << "] Cleared. Terminating now.\n" << std::endl;
		}
		else {
			std::osyncstream(std::cout) << "[Dungeon " << id << "] Cleared. Will attempt to form party soon if possible.\n" << std::endl;

		}

	}
}