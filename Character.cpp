#include "Character.h"

std::string classTypeToString(ClassType ct) {

	switch (ct) {
	case DPS:
		return "DPS";
	case Tank:
		return "Tank";
	case Healer:
		return "Healer";
	default:
		return "?";
	}
}