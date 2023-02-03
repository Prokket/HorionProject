#include "Reach.h"

#include <Windows.h>
#include "../../../Utils/Logger.h"
#include "../../../Utils/Utils.h"

Reach::Reach() : IModule(0, Category::COMBAT, "Increases your reach") {
	this->registerFloatSetting("Reach Value", &this->reachValue, this->reachValue, 3.f, 7.f);
	type.addEntry(EnumEntry("Signature", 0)).addEntry(EnumEntry("Offset", 1));
	registerEnumSetting("Mode", &type, 0);
	registerFloatSetting("Reach Value", &reachValue, reachValue, 3.f, 7.f);
}

Reach::~Reach() {
}

const char* Reach::getModuleName() {
	return ("Reach");
}

void Reach::onTick(GameMode* gm) {
	if (reachPtr != 0 && type.selected == 0) {
		*reachPtr = reachValue;
	}
}

void Reach::onEnable() {
	if (type.selected == 0) {
		static uintptr_t sigOffset = 0x0;
		if (sigOffset == 0x0) {
			sigOffset = FindSignature("F3 0F 10 05 ? ? ? ? 41 0F 28 D9");

			if (sigOffset != 0x0) {
				int offset = *reinterpret_cast<int*>((sigOffset + 4));  // Get Offset from code
				reachPtr = reinterpret_cast<float*>(sigOffset + offset + 8);
				originalReach = *reachPtr;
			}
		}
		if (!VirtualProtect(reachPtr, sizeof(float), PAGE_EXECUTE_READWRITE, &oldProtect)) {
#ifdef _DEBUG
			logF("couldnt unprotect memory send help");
			__debugbreak();
#endif
		}
	} else {
		uintptr_t reachOff = Utils::getBase() + 0x398A878;  // Reach offset

		unsigned char arr[4];

		memcpy(arr, &reachValue, sizeof(float));
		Utils::patchBytes((unsigned char*)reachOff, arr, 4);
	}
}

void Reach::onDisable() {
	if (type.selected == 0) {
		*reachPtr = originalReach;
		if (reachPtr != 0)
			VirtualProtect(reachPtr, sizeof(float), oldProtect, &oldProtect);
	} else {
		uintptr_t reachOff = Utils::getBase() + 0x398A878;  // Reach offset
		Utils::patchBytes((unsigned char*)reachOff, (unsigned char*)"\x00\x00\x40\x40" /*3*/, 4);
	}
}