#include "Entity.h"

#include "../Memory/GameData.h"
#include "../Utils/Utils.h"
InventoryTransactionManager *Entity::getTransactionManager() {
	//return &this->transac;
	static unsigned int offset = 0x1210;
	//if (offset == 0) {
	// EnchantCommand::execute
	//offset = *reinterpret_cast<int *>(FindSignature("E8 ? ? ? ? 48 8B 07 48 8B 48 ? 48 85 C9") + 3);
	//}
	return reinterpret_cast<InventoryTransactionManager *>(reinterpret_cast<__int64>(this) + offset);
}
PlayerInventoryProxy *Player::getSupplies() {
	static unsigned int offset = 0xB70;
	/*if (offset == 0) {
		offset = *reinterpret_cast<int *>(FindSignature("E8 ? ? ? ? 48 8D 48 ? 48 8B 01") + 7);  // GameMode::startDestroyBlock -> GameMode::_canDestroy -> getSupplies
	}*/
	return *reinterpret_cast<PlayerInventoryProxy **>(reinterpret_cast<__int64>(this) + offset);
}
void LocalPlayer::unlockAchievements() {  // MinecraftEventing::fireEventAwardAchievement
	using fireEventAward = void(__fastcall *)(void *, int);
	static fireEventAward fireEventAwardFunc = reinterpret_cast<fireEventAward>(FindSignature("E8 ? ? ? ? 48 8B BE ? ? ? ? 48 8B CE"));
	for (int i = 0; i < 118; i++)
		fireEventAwardFunc(this, i);
}
void LocalPlayer::applyTurnDelta(Vec2 *viewAngleDelta) {
	using applyTurnDelta = void(__thiscall *)(void *, Vec2 *);
	static applyTurnDelta TurnDelta = reinterpret_cast<applyTurnDelta>(FindSignature("E8 ? ? ? ? 45 0F 2E C3"));
	TurnDelta(this, viewAngleDelta);
}
void LocalPlayer::setGameModeType(int gma) {
	// Player::setPlayerGameType
	//using setGameMode = void(__thiscall *)(void *, int);
	//static setGameMode Game_Mode = reinterpret_cast<setGameMode>(FindSignature("48 8B C4 56 57 41 56 48 81 EC ? ? ? ? 48 C7 44 24 ? ? ? ? ? 48 89 58 ? 48 89 68 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 8B EA 48 8B D9 44 8B B1 ? ? ? ? 83 FA ? 75 2D"));
	this->setPlayerGameType(gma);
}

bool Level::hasEntity() {
	return rayHitType == 1;
}

float Entity::getBlocksPerSecond() {
	return getTicksPerSecond() * *Game.getClientInstance()->minecraft->timer;
}

void Entity::lerpTo(Vec3 const &pos, Vec2 const &a2, int a3) { //lerpTo was removed from the Player vtable so this is how we are going to use it from now on
	using lerpTo = void(__fastcall *)(Entity *, Vec3 const &, Vec2 const &, int);
	static lerpTo lerp = reinterpret_cast<lerpTo>(FindSignature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 41 56 48 83 EC 30 48 8B D9"));
	lerp(this, pos, a2, a3);
}

Entity *Level::getEntity() {
	if (rayHitType != 1) return nullptr;
	Entity *retval = nullptr;
	Game.forEachEntity([this, &retval](Entity *ent, bool b) {
		if (*(__int64 *)((__int64)ent + 0x10) == GamingEntityFinder) {
			retval = ent;
			return;
		}
	});
	return retval;
}