#include "AirSwim.h"

AirSwim::AirSwim() : IModule(0, Category::MOVEMENT, "Swim in Air.") {
}

AirSwim::~AirSwim() {
}

const char* AirSwim::getModuleName() {
	return ("AirSwim");
}

void AirSwim::onTick(GameMode* gm) {
	Game.getLocalPlayer()->didEnterWaterBool = true;
	Game.getLocalPlayer()->doWaterSplashEffect();
	Game.getLocalPlayer()->startSwimming();
}

void AirSwim::onDisable() {
	if (Game.getLocalPlayer() == nullptr)
		return;
	Game.getLocalPlayer()->didEnterWaterBool = false;
	Game.getLocalPlayer()->stopSwimming();
}

void AirSwim::onEnable() {
	if (Game.getLocalPlayer() == nullptr)
		return;
	if (Game.getLocalPlayer() && Game.getLocalPlayer()->didEnterWaterBool) {
		Game.getLocalPlayer()->startSwimming();
	}
};