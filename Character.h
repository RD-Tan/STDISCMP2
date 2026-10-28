#pragma once
#include <string>

enum ClassType
{
	DPS,
	Tank,
	Healer
};

struct Character
{
	int id;
	std::string name;
	ClassType classType;
};

std::string classTypeToString(ClassType ct);