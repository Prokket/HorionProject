#include "AirJump.h"

AirJump::AirJump() : IModule('G', Category::MOVEMENT, "Jump even you're not on the ground.") {
	registerBoolSetting("Legacy", &legacyMode, legacyMode);
}

AirJump::~AirJump() {
}

const char* AirJump::getModuleName() {
	return ("AirJump");
}

void AirJump::onTick(GameMode* gm) {
	GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();
	
	if (input == nullptr)
		return;
	
	gm->player->onGround = (legacyMode) ? true : GameData::isKeyDown(*input->spaceBarKey) && hasJumped == 0;
	
	if (GameData::isKeyDown(*input->spaceBarKey) && hasJumped == 0)
		hasJumped = 1;
	else if (!GameData::isKeyDown(*input->spaceBarKey))
		hasJumped = 0;
}
