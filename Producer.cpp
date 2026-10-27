#include "Producer.h"

Producer::Producer(unsigned long totalParties) {
	for (int i = 0; i < totalParties; i++) {
		Character dps1 = { i, "DPS_" + std::to_string(i), ClassType::DPS };
		//Character dps2 = { i, "DPS_" + std::to_string(i + totalParties), ClassType::DPS };
		//Character dps3 = { i, "DPS_" + std::to_string(i + totalParties * 2), ClassType::DPS };
		Character tank = { i, "Tank_" + std::to_string(i + totalParties * 3), ClassType::Tank };
		Character healer = { i, "Healer_" + std::to_string(i + totalParties * 4), ClassType::Healer };
		dpsQueue.push(dps1);
		//dpsQueue.push(dps2);
		//dpsQueue.push(dps3);
		tankQueue.push(tank);
		healerQueue.push(healer);
	}
}

Character Producer::popDPS() {
	std::lock_guard<std::mutex> lock(dpsM);
	if (dpsQueue.empty()) {
		return { -1, "", ClassType::DPS };
	}
	Character character = dpsQueue.front();
	dpsQueue.pop();
	return character;
}

Character Producer::popTank() {
	std::lock_guard<std::mutex> lock(tankM);
	if (tankQueue.empty()) {
		return { -1, "", ClassType::Tank };
	}
	Character character = tankQueue.front();
	tankQueue.pop();
	return character;
}

Character Producer::popHealer() {
	std::lock_guard<std::mutex> lock(healerM);
	if (healerQueue.empty()) {
		return { -1, "", ClassType::Healer };
	}
	Character character = healerQueue.front();
	healerQueue.pop();
	return character;
}