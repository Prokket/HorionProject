#include "FastPlace.h"

FastPlace::FastPlace() : IModule(0x0, Category::WORLD, "Place Blocks faster") {
	this->registerBoolSetting("Only Crystals", &this->onlyCrystals, this->onlyCrystals);
}

FastPlace::~FastPlace() {
}

const char* FastPlace::getModuleName() {
	return ("FastPlace");
}


void FastPlace::onTick(GameMode* gm) {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;

	if (GameData::isRightClickDown()) {
		auto pStruct = Game.getClientInstance()->getLevel();
		Vec3i block = pStruct->block.toVec3t();
		int face = pStruct->blockSide;
		int rayType = pStruct->rayHitType;

		auto selectedItem = Game.getLocalPlayer()->getSelectedItem();
		auto selectedItemId = Game.getLocalPlayer()->getSelectedItemId();
		bool isCrystal = false;

		if (!onlyCrystals && rayType == 0) {
			if (selectedItemId == 615 && !selectedItem->count == 0 || selectedItemId == 616 && !selectedItem->count == 0 || selectedItemId == 629 && !selectedItem->count == 0) {
				isCrystal = true;
			} else {
				isCrystal = false;
			}

			if (!isCrystal) {
				if (selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock())
					return;
			}
		}
	}
}