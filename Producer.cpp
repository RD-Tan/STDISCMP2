#include "Producer.h"

Producer::Producer(Config config) {
	std::vector<std::string> usernames;

	std::random_device rd;
	std::mt19937 gen(rd());

	std::ifstream file("usernames.csv");

	if (!file.is_open()) {
		std::cerr << "Error: Could not open the file." << std::endl;
		exit(1);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string cell;
		while (std::getline(ss, cell, ',')) {
			usernames.push_back(cell);
		}

	}

	file.close();

	std::uniform_int_distribution<int> dist(0, usernames.size() - 1);

	for (int i = 0; i < config.DPSCount; i++) {
		Character dps = { i, usernames[dist(gen)], ClassType::DPS };
		dpsQueue.push(dps);
	}

	for (int i = 0; i < config.tankCount; i++) {
		Character dps = { i, usernames[dist(gen)], ClassType::Tank };
		tankQueue.push(dps);
	}

	for (int i = 0; i < config.healerCount; i++) {
		Character dps = { i, usernames[dist(gen)], ClassType::Healer };
		healerQueue.push(dps);
	}
}

bool Producer::tryAcquireParty(std::vector<Character>& newParty) {
	std::lock_guard<std::mutex> lock(partyM);
	if (tankQueue.empty() || healerQueue.empty()) return false;
	if (dpsQueue.size() < 3) return false;

	newParty.push_back(dpsQueue.front());
	dpsQueue.pop();
	newParty.push_back(dpsQueue.front());
	dpsQueue.pop();
	newParty.push_back(dpsQueue.front());
	dpsQueue.pop();

	newParty.push_back(tankQueue.front());
	tankQueue.pop();

	newParty.push_back(healerQueue.front());
	healerQueue.pop();

	return true;
}

std::vector<Character> Producer::dumpRemaining() {
	std::vector<Character> dump;
	while(!dpsQueue.empty()) {
		dump.push_back(dpsQueue.front());
		dpsQueue.pop();
	}
	while (!tankQueue.empty()) {
		dump.push_back(tankQueue.front());
		tankQueue.pop();
	}
	while (!healerQueue.empty()) {
		dump.push_back(healerQueue.front());
		healerQueue.pop();
	}
	return dump;
}