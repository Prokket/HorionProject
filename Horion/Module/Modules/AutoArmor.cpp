#include "AutoArmor.h"

AutoArmor::AutoArmor() : IModule(0, Category::PLAYER, "Automatically equips the best armor.") {
}

AutoArmor::~AutoArmor() {
}

const char* AutoArmor::getModuleName() {
	return ("AutoArmor");
}