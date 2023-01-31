#include "Reach.h"

#include <Windows.h>
#include "../../../Utils/Logger.h"
#include "../../../Utils/Utils.h"

Reach::Reach() : IModule(0, Category::COMBAT, "Increases your reach.") {
}

Reach::~Reach() {
}

const char* Reach::getModuleName() {
	return ("Reach");
}