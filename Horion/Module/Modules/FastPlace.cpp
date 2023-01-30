#include "FastPlace.h"

FastPlace::FastPlace() : IModule(0x0, Category::WORLD, "Place Blocks faster") {
	this->registerBoolSetting("Only Crystals", &this->onlyCrystals, this->onlyCrystals);
}

FastPlace::~FastPlace() {}

const char* FastPlace::getModuleName() {
	return "FastPlace";
}

void FastPlace::onTick(GameMode* gm) {
	if (auto player = Game.getLocalPlayer(); player != nullptr && GameData::isRightClickDown()) {
		auto pStruct = Game.getClientInstance()->getLevel();
		Vec3i block = pStruct->block.toVec3t();
		int face = pStruct->blockSide;
		int rayType = pStruct->rayHitType;
		if (!onlyCrystals && rayType == 0) {
			if (auto selectedItem = player->getSelectedItem(); selectedItem != nullptr) {
				auto selectedItemId = player->getSelectedItemId();
				bool isCrystal = (selectedItemId == 615 || selectedItemId == 616 || selectedItemId == 629) && !selectedItem->count == 0;
				if (!isCrystal && (!selectedItem->getItem() || !selectedItem->getItem()->isBlock() || selectedItem->count == 0))
					return;
			}
		}
	}
}