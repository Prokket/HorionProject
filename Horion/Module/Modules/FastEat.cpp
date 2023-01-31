#include "FastEat.h"

FastEat::FastEat() : IModule(0, Category::PLAYER, "Eat food almost instantly.") {
}

FastEat::~FastEat() {
}

const char* FastEat::getModuleName() {
	return ("FastEat");
}

void FastEat::onTick(GameMode* gm) {
	PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
	Inventory* inv = supplies->inventory;
	
	for (ItemStack* stack : inv->itemStacks) {
		if (stack->item != NULL && (*stack->item)->itemId != 261 && (*stack->item)->duration == 32)
			(*stack->item)->setMaxUseDuration(5);
	}
}

void FastEat::onDisable() {
	if (Game.getLocalPlayer() == nullptr)
		return;
	PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
	Inventory* inv = supplies->inventory;
	
	for (ItemStack* stack : inv->itemStacks) {
		if (stack->item != NULL && (*stack->item)->itemId != 261 && (*stack->item)->duration == 5)
			(*stack->item)->setMaxUseDuration(32);
	}
}