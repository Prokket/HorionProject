#include "InventoryTransaction.h"
#include "../Utils/Utils.h"
void InventoryTransactionManager::addInventoryAction(const InventoryAction& action, bool idk) {
	static auto InventoryTransactionManager__addAction = Utils::FindSignature("E8 ? ? ? ? 48 8B 07 48 8B D3 48 8B CF 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 84 C0 75 35");
	if (InventoryTransactionManager__addAction)
		reinterpret_cast<void(__fastcall*)(InventoryTransactionManager*, const InventoryAction&, bool)>(InventoryTransactionManager__addAction)(this, action, idk);
}

void InventoryAction::fixInventoryStuff(ItemDescriptor* a1, ItemStack* a2) {
	static auto fixInvStuff = Utils::FindSignature("E8 ? ? ? ? 48 8B 07 48 8B D3 48 8B CF 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 84 C0 75 35");
	if (fixInvStuff)
		reinterpret_cast<void(__fastcall*)(ItemDescriptor*, ItemStack*)>(fixInvStuff)(a1, a2);
}
