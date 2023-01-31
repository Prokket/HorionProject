#include "Reducer.h"

Reducer::Reducer() : IModule(0, Category::COMBAT, "Tries do reduce your knockback relatively legit") {
	this->mode.addEntry(EnumEntry("Jump", 0))
			   .addEntry(EnumEntry("Sneak", 1))
			   .addEntry(EnumEntry("JumpReset", 2));
	this->registerEnumSetting("Mode", &this->mode, 0);
}

Reducer::~Reducer() {
}

const char* Reducer::getModuleName() {
	if (this->isEnabled()) {
		std::string mod = std::string("Reducer (") + std::string(this->mode.GetSelectedEntry().GetName()) + std::string(")");

		return mod.c_str();
	}

	return "Reducer";
}

void Reducer::onEnable() {
	if (Game.getLocalPlayer() == nullptr) {
		this->setEnabled(false);
		return;
	}

	this->hitCount = 0;
	this->ticks = 0;
}

void Reducer::onTick(GameMode* gm) {
    LocalPlayer* player = Game.getLocalPlayer();
    if (!player) return;

    switch (mode.selected) {
        case 0:
            if (player->damageTime > 0 && player->onGround) 
                player->jumpFromGround();
            break;
        case 1:
            if (player->damageTime > 0 && !player->isSneaking()) {
                player->setSneaking(true);
                player->setSneaking(false);
            }
            break;
        case 2:
            ticks++;
            if (player->damageTime == 1) hitCount++;
            if (player->damageTime > 0) ticks = 0;
            if (ticks >= 20) hitCount = 0;
            if (player->damageTime > 0 && hitCount == 2 && player->onGround) {
                player->jumpFromGround();
                hitCount = 0;
            }
            break;
    }
}
