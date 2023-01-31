#include "Hitbox.h"

Hitbox::Hitbox() : IModule(0, Category::COMBAT, "Increase an entitys hitbox size.") {
	registerFloatSetting("Height", &height, height, 1.8f, 10);
	registerFloatSetting("Width", &width, width, 0.6f, 10);
}

Hitbox::~Hitbox() {
}

const char* Hitbox::getModuleName() {
	return ("Hitbox");
}

void findTarget(Entity* currentEntity, bool isRegularEntitie) {
	static auto hitboxMod = moduleMgr->getModule<Hitbox>();
	if (currentEntity && currentEntity != Game.getLocalPlayer() && currentEntity->timeSinceDeath == 0 && currentEntity->damageTime < 7 && Target::isValidTarget(currentEntity) && (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos()) < hitboxMod->range) currentEntity->width = hitboxMod->width, currentEntity->height = hitboxMod->height;
}

void Hitbox::onTick(GameMode* gm) {
	Game.forEachEntity(findTarget);
}
