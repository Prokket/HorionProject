#include "Jesus.h"

Jesus::Jesus() : IModule(0, Category::MOVEMENT, "Walk over water, like Jesus.") {
}

Jesus::~Jesus() {
}

const char* Jesus::getModuleName() {
	return "Jesus";
}

void Jesus::onTick(GameMode* gm) {
	if (gm->player->isSneaking() || !gm->player->isInWater() && !gm->player->hasEnteredWater() && !gm->player->isInLava()) return;

	gm->player->velocity.y = 0.1f;
	gm->player->onGround = true;
	wasInWater = true;

	if (!gm->player->isInWater() && !gm->player->isInLava() && wasInWater) {
		wasInWater = false;
		gm->player->velocity.x *= 1.2f;
		gm->player->velocity.z *= 1.2f;
	}
}

