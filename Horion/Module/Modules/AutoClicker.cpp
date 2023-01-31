#include "AutoClicker.h"

AutoClicker::AutoClicker() : IModule(0, Category::COMBAT, "A simple autoclicker, automatically clicks for you.") {
	registerBoolSetting("RightClick", &rightclick, rightclick);
	registerBoolSetting("Only Weapons", &weapons, weapons);
	registerBoolSetting("Break Blocks", &breakBlocks, breakBlocks);
	registerIntSetting("Delay", &delay, delay, 0, 20);
	registerBoolSetting("Hold", &hold, hold);
}

AutoClicker::~AutoClicker() {}

const char* AutoClicker::getModuleName() {
	return "AutoClicker";
}

void AutoClicker::onTick(GameMode* gm) {
	if (!GameData::canUseMoveKeys())
		return;
	LocalPlayer* player = Game.getLocalPlayer();
	Level* level = player->level;

	if (Odelay >= delay) {
		Odelay = 0;

		if (GameData::isLeftClickDown() || !hold) {
			auto selectedItem = player->getSelectedItem();
			if (weapons && selectedItem->getAttackingDamageWithEnchants() < 1)
				return;

			player->swingArm();
			if (level->hasEntity() != 0)
				gm->attack(level->getEntity());
			else if (breakBlocks) {
				bool isDestroyed = false;
				gm->startDestroyBlock(level->block, level->blockSide, isDestroyed);
				gm->stopDestroyBlock(level->block);
				if (isDestroyed && player->region->getBlock(level->block)->blockLegacy->blockId != 0)
					gm->destroyBlock(&level->block, 0);
			}
		}

		if (rightclick && (GameData::isRightClickDown() || !hold)) {
			bool idk = true;
			gm->buildBlock(new Vec3i(level->block), level->blockSide, idk);
		}
	} else
		Odelay++;
}