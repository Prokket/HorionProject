#include "Item.h"

#include "../Memory/GameData.h"
#include "../Utils/Utils.h"
#include "Tag.h"

BaseActorRenderContext::BaseActorRenderContext(ScreenContext *ScreenCtx, ClientInstance *client, MinecraftGame *game) {
	memset(this, 0, sizeof(BaseActorRenderContext));
	using BaseActorRenderContext_t = __int64(__fastcall *)(BaseActorRenderContext *, ScreenContext *, ClientInstance *, MinecraftGame *);
	static BaseActorRenderContext_t BaseActorRenderContext_constructor = reinterpret_cast<BaseActorRenderContext_t>(FindSignature("48 89 5C 24 ?? 48 89 74 24 ?? 48 89 4C 24 08 57 48 83 EC ?? ?? ?? ?? 48 8B F9 48 8D 05 ?? ?? ?? ?? 48 89 ?? 33 F6 48 89 71 08"));
	BaseActorRenderContext_constructor(this, ScreenCtx, client, game);
}
void ItemRenderer::renderGuiItemNew(BaseActorRenderContext *BaseActorRenderCtx, ItemStack *item, int mode, float x, float y, float opacity, float scale, bool isEnchanted) {
	using renderGuiItemNew_t = void(__fastcall *)(ItemRenderer *, BaseActorRenderContext *, ItemStack *, int, float, float, bool, float, float, float);
	static renderGuiItemNew_t renderGuiItemNew = reinterpret_cast<renderGuiItemNew_t>(FindSignature("48 8B C4 53 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 44 89 8C 24"));
	item->setShowPickUp(false);
	renderGuiItemNew(this, BaseActorRenderCtx, item, mode, x, y, isEnchanted, 1, opacity, scale);
}

void ItemRenderer::renderGuiItemInChunk(BaseActorRenderContext *BaseActorRenderCtx, ItemStack *item, float x, float y, float opacity, float scale, bool isEnchanted, int mode) {
	using renderGuiItemInChunk_t = void(__fastcall *)(ItemRenderer *, BaseActorRenderContext *, __int64, ItemStack *, float, float, float, float, float, int);
	static renderGuiItemInChunk_t renderGuiItem = reinterpret_cast<renderGuiItemInChunk_t>(FindSignature("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 B8 0F 29 78 A8 44 0F 29 40 ? 44 0F 29 48 ? 44 0F 29 90 ? ? ? ? 44 0F 29 98 ? ? ? ? 44 0F 29 A0 ? ? ? ? 44 0F 29 A8 ? ? ? ? 48 8B 05 ? ? ? ?"));
	//item->setShowPickUp(false);

	renderGuiItem(this, BaseActorRenderCtx, 2, item, x, y, 1, 1, scale, 0);
}

ItemStack::ItemStack(const ItemStack &src) {
	memset(this, 0x0, sizeof(ItemStack));
	using ItemStackCopyConstructor_t = void(__fastcall *)(ItemStack &, ItemStack const &);
	static ItemStackCopyConstructor_t ItemStackCopyConstructor = reinterpret_cast<ItemStackCopyConstructor_t>(FindSignature("E8 ? ? ? ? 90 49 8B 8E ? ? ? ? 48 8B 01 48 8B 40 ?"));
	ItemStackCopyConstructor(*this, src);
	this->setVtable();
}

ItemStack::ItemStack(const Tag &tag) {
	memset(this, 0x0, sizeof(ItemStack));
	this->setVtable();
	fromTag(tag);
	/*using ItemStackBase__loadItemF = void(__fastcall*)(ItemStack*,Tag const&);
	static ItemStackBase__loadItemF ItemStackBase__loadItem = reinterpret_cast<ItemStackBase__loadItemF>(FindSignature("E8 ? ? ? ? 90 49 8B 5E ? 4D 8B 76 ?")); Updated to 1.19.51 even tho its not in use stuped
	ItemStackBase__loadItem(this, tag);*/
}

void ItemStack::fromTag(const Tag &tag) {
	using ItemStackBase__loadItemF = void(__fastcall *)(ItemStack *, Tag const &);
	static ItemStackBase__loadItemF fromTag = reinterpret_cast<ItemStackBase__loadItemF>(FindSignature("E8 ? ? ? ? 90 80 7D ? 00 74 40"));
	fromTag(this, tag);
}

void ItemStack::save(CompoundTag **tag) {
	using ItemStackBase__saveF = void(__fastcall *)(ItemStack *, CompoundTag **);
	ItemStackBase__saveF save = reinterpret_cast<ItemStackBase__saveF>(FindSignature("E8 ? ? ? ? 0F B6 7C 24 ? 48 8B 4E ?"));
	return save(this, tag);
}
void ItemStack::setUserData(std::unique_ptr<Tag> tag) {
	using setUserData_t = void(__fastcall *)(ItemStack *, std::unique_ptr<Tag>);
	setUserData_t setUserData = reinterpret_cast<setUserData_t>(FindSignature("E8 ? ? ? ? 8B 7D 50"));
	setUserData(this, std::move(tag));
}
void ItemStack::reinit(BlockLegacy &legacy, int count) {
	this->setVtable();
	Utils::CallVFunc<2, void>(this, &legacy, count);
}
void ItemStack::reinit(Item &item, int count, int itemData) {
	this->setVtable();
	Utils::CallVFunc<3, void>(this, &item, count, itemData);
}
int ItemStack::getEnchantValue(int enchantId) {
	using getEnchantsLevel_t = int(__fastcall *)(int, ItemStack *);
	static getEnchantsLevel_t getEnchantsLevel = reinterpret_cast<getEnchantsLevel_t>(FindSignature("48 8B 81 ? ? ? ? 8B 40 18"));
	return getEnchantsLevel(enchantId, this);
}
void ItemStack::setVtable(void) {
	static uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 01 4C 89 71 ? 4C 89 71 ? 48 89 51 ?");
	int offset = *reinterpret_cast<int *>(sigOffset + 1);
	this->vTable = reinterpret_cast<uintptr_t **>(sigOffset + offset + /*length of instruction*/ 7);
}
Item ***ItemRegistry::getItemFromId(void *ptr, int itemId) {
	using getItemFromId_t = Item ***(__fastcall *)(void *, int);
	static getItemFromId_t getItemFromId = reinterpret_cast<getItemFromId_t>(FindSignature("E8 ? ? ? ? 66 3B C3 75 18"));
	return getItemFromId(ptr, itemId);
}

Item ***ItemRegistry::lookUpByName(void *a1, void *a2, TextHolder &text) {
	using ItemRegistry__lookupByName_t = Item ***(__fastcall *)(void *, void *, TextHolder &);
	static ItemRegistry__lookupByName_t ItemRegistry__lookupByNameF = reinterpret_cast<ItemRegistry__lookupByName_t>(FindSignature("E8 ? ? ? ? C7 44 24 ? ? ? ? ? 48 8B 95 ? ? ? ?"));
	return ItemRegistry__lookupByNameF(a1, a2, text);
}

ItemDescriptor::ItemDescriptor(int id, int16_t itemData) {
	using ItemDescriptor__ItemDescriptor_t = ItemDescriptor *(__fastcall *)(ItemDescriptor *, int, int16_t);
	static ItemDescriptor__ItemDescriptor_t func = reinterpret_cast<ItemDescriptor__ItemDescriptor_t>(FindSignature("48 8D 35 ? ? ? ? F6 C3 02"));
	func(this, id, itemData);
}