#include "Packet.h"

#include "../Utils/Utils.h"

TextHolder* Packet::getName() {
	return Utils::CallVFunc<2, TextHolder*>(this, new TextHolder());
}
LevelSoundEventPacket::LevelSoundEventPacket() {
	static uintptr_t** LevelSoundEventPacketVtable = 0x0;
	if (LevelSoundEventPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 01 89 51 30 F2 41 0F 10 00");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		LevelSoundEventPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (LevelSoundEventPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(LevelSoundEventPacket));  // Avoid overwriting vtable
	vTable = LevelSoundEventPacketVtable;
	this->entityType.setText("minecraft:player");
}
PlayerAuthInputPacket::PlayerAuthInputPacket() {
	static uintptr_t** PlayerAuthInputPacketVtable = 0x0;
	if (PlayerAuthInputPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 01 F2 0F 10 42 ? F2 0F 11 41 ? F2 0F 10 42 ?");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		PlayerAuthInputPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (PlayerAuthInputPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerAuthInputPacket));  // Avoid overwriting vtable
	vTable = PlayerAuthInputPacketVtable;
}
PlayerAuthInputPacket::PlayerAuthInputPacket(Vec3 pos, float pitch, float yaw, float yawUnused) {
	static uintptr_t** PlayerAuthInputPacketVtable = 0x0;
	if (PlayerAuthInputPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 89 5C 24 ? 57 48 83 EC 20 48 8D 05 ? ? ? ? 48 8B D9 48 89 01 48 81 C1 98 00 00 00 E8 ? ? ? ? 48 8B BB ? ? ? ?");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		PlayerAuthInputPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (PlayerAuthInputPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerAuthInputPacket));  // Avoid overwriting vtable
	vTable = PlayerAuthInputPacketVtable;
	this->pos = pos;
	this->pitch = pitch;
	this->yaw = yaw;
	this->yawUnused = yawUnused;
	this->InputAD = 0.f;
	this->InputWS = 0.f;
}
MobEquipmentPacket::MobEquipmentPacket() {
	static uintptr_t** MobEquipmentPacketVtable = 0x0;
	if (MobEquipmentPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("40 53 48 83 EC ? 48 8B D9 48 81 C1 ? ? ? ? E8 ? ? ? ? 48 8D 8B ? ? ? ? E8 ? ? ? ? 48 8D 8B ? ? ? ? E8 ? ? ? ? 48 8D 4B ? E8 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 03");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		MobEquipmentPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (MobEquipmentPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(MobEquipmentPacket));  // Avoid overwriting vtable
	vTable = MobEquipmentPacketVtable;
}
MobEquipmentPacket::MobEquipmentPacket(__int64 entityRuntimeId, ItemStack& item, int hotbarSlot, int inventorySlot) {
	memset(this, 0x0, sizeof(MobEquipmentPacket));
	using MobEquimentPacketConstructor_t = void(__fastcall*)(MobEquipmentPacket*, __int64, ItemStack&, int, int, char);
	static MobEquimentPacketConstructor_t MobEquimentPacketConstructor = reinterpret_cast<MobEquimentPacketConstructor_t>(FindSignature("E8 ? ? ? ? 90 48 8B CE E8 ? ? ? ? 45 33 C9 4C 8D 44 24 ? 48 8B D6 48 8B C8 E8 ? ? ? ? 0F B6 47 ?"));

	if (MobEquimentPacketConstructor != 0)
		MobEquimentPacketConstructor(this, entityRuntimeId, item, hotbarSlot, inventorySlot, 0);
}
InventoryTransactionPacket::InventoryTransactionPacket() {
	static uintptr_t** InventoryTransactionPacketVtable = 0x0;
	if (InventoryTransactionPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 01 48 83 C1 ? E8 ? ? ? ? 48 89 6E ? 48 89 6E ?");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		InventoryTransactionPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (InventoryTransactionPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(InventoryTransactionPacket));  // Avoid overwriting vtable
	vTable = InventoryTransactionPacketVtable;
}
TextPacket::TextPacket() {
	static uintptr_t** textPacketVtable = 0x0;
	if (textPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 01 88 51 30 48 83 C1 38");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		textPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (textPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(TextPacket));  // Avoid overwriting vtable
	vTable = textPacketVtable;

	messageType = 1;  // TYPE_CHAT
}
MovePlayerPacket::MovePlayerPacket() {
	static uintptr_t** movePlayerPacketVtable = 0x0;
	if (movePlayerPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 01 48 8D 51 ? 48 8B CF");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		movePlayerPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (movePlayerPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(MovePlayerPacket));  // Avoid overwriting vtable
	vTable = movePlayerPacketVtable;
}
MovePlayerPacket::MovePlayerPacket(LocalPlayer* player, Vec3 pos) {
	static uintptr_t** movePlayerPacketVtable = 0x0;
	if (movePlayerPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("E8 ? ? ? ? 90 0F 57 C9 F3 0F 7F 4D ? 4C 89 65 ? 48 8B 06");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		movePlayerPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (movePlayerPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(MovePlayerPacket));  // Avoid overwriting vtable
	vTable = movePlayerPacketVtable;
	entityRuntimeID = player->entityRuntimeId;
	Position = pos;
	pitch = player->pitch;
	yaw = player->yaw;
	headYaw = player->yaw;
	onGround = true;
	mode = 0;
}
PlayerActionPacket::PlayerActionPacket() {
	static uintptr_t** playerActionPacketVtable = 0x0;
	if (playerActionPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 89 5C 24 ? 48 89 4C 24 ? 57 48 83 EC ? 48 8B D9 C7 41 ? ? ? ? ? C7 41 ? ? ? ? ? 66 C7 41 ? ? ? 33 FF 48 89 79 ? 48 89 79 ? 89 79 28 48 8D 05 ? ? ? ? 48 89 01 48 89 79 ? 48 89 79 ? 48 83 C1 ?");
		int offset = *reinterpret_cast<int*>(sigOffset + 1);
		playerActionPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (playerActionPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerActionPacket));  // Avoid overwriting vtable
	vTable = playerActionPacketVtable;
}

SubChunkRequestPacket::SubChunkRequestPacket() {
	static uintptr_t** subChunkRequestPacketVtable = 0x0;
	if (subChunkRequestPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("0F B7 02 4C 8B CA");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		subChunkRequestPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (subChunkRequestPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(SubChunkRequestPacket));  // Avoid overwriting vtable
	vTable = subChunkRequestPacketVtable;
}

EmotePacket::EmotePacket() {
	static uintptr_t** emotePacketVtable = 0x0;
	if (emotePacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 0D ? ? ? ? 48 89 8D ? ? ? ? 48 89 85 ? ? ? ? 48 89 BD");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		emotePacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (emotePacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(EmotePacket));  // Avoid overwriting vtable
	vTable = emotePacketVtable;
}
//48 8D 15 ? ? ? ? C7 40 ? ? ? ? ? 33 C9 C7 40 ? ? ? ? ? 48 89 48 28 48 89 48 30 89 48 38 89 48 40 48 89 48 48 48 89 48 58 C7 40 ? ? ? ? ? C7 40 ? ? ? ? ? 66 C7 40 ? ? ? 48 89 50 10 48 C7 40 ? ? ? ? ? EB 04 33 C9 8B C1 48 8D 48 10 48 8D 15 ? ? ? ? 48 89 51 20 48 89 43 08 48 8B C3 48 89 0B 48 83 C4 30 5B C3 48 8D 0D ? ? ? ? E8 ? ? ? ? 83 3D ? ? ? ? ? 0F 85 ? ? ? ? 48 8D 05 ? ? ? ? 48 8D 0D ? ? ? ? 48 89 05 ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? E9 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 40 53 48 83 EC 30 65 48 8B 04 25 ? ? ? ? 48 8B D9 48 89 4C 24 ? BA ? ? ? ? 48 8B 08 8B 04 0A 39 05 ? ? ? ? 0F 8F ? ? ? ? E8 ? ? ? ? 48 8B C8 BA ? ? ? ? 48 8B 00 FF 50 08 48 89 44 24 ? 48 85 C0 74 4F
//Model Form Response packet
AnimatePacket::AnimatePacket() {
	static uintptr_t** animatePacketVtable = 0x0;
	if (animatePacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 06 48 89 4E ? 48 89 4E ?");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		animatePacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (animatePacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(AnimatePacket));  // Avoid overwriting vtable
	vTable = animatePacketVtable;
}
/*
AnimatePacket::AnimatePacket(AnimatePacket Action, __int64 entityRuntimeId, float) {
}
*/

NPCRequestPacket::NPCRequestPacket() {
	static uintptr_t** npcRequestPacketVtable = 0x0;
	if (npcRequestPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("E8 ? ? ? ? 48 8B F8 49 8B 5D ?");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		npcRequestPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (npcRequestPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(NPCRequestPacket));  // Avoid overwriting vtable
	vTable = npcRequestPacketVtable;
}

PlayerSkinPacket::PlayerSkinPacket() {
	static uintptr_t** playerSkinPacketVtable = 0x0;
	if (playerSkinPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 01 48 89 79 ? 48 89 79 ? 48 83 C1 40");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		playerSkinPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (playerSkinPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerSkinPacket));  // Avoid overwriting vtable
	vTable = playerSkinPacketVtable;
}

NetworkLatencyPacket::NetworkLatencyPacket() {
	static uintptr_t** networkLatencyPacketVtable = 0x0;
	if (networkLatencyPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 0F 11 43 ?");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		networkLatencyPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (networkLatencyPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(NetworkLatencyPacket));  // Avoid overwriting vtable
	vTable = networkLatencyPacketVtable;
}

CommandRequestPacket::CommandRequestPacket() {
	static uintptr_t** commandRequestPacketVtable = 0x0;
	if (commandRequestPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 8B D9 48 89 01 48 83 C1 50 E8 ? ? ? ? 48 8B 53 ?");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		commandRequestPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (commandRequestPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(CommandRequestPacket));  // Avoid overwriting vtable
	vTable = commandRequestPacketVtable;
}

CommandRequestPacket::CommandRequestPacket(std::string cmd) {
	static uintptr_t** commandRequestPacketVtable = 0x0;
	if (commandRequestPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("40 53 48 83 EC 20 48 8D 05 ? ? ? ? 48 8B D9 48 89 01 48 83 C1 50 E8 ? ? ? ? 48 8B 53 ?");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		commandRequestPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (commandRequestPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(CommandRequestPacket));  // Avoid overwriting vtable
	vTable = commandRequestPacketVtable;
	this->origin = Origin::PLAYER;
	this->isExternal = 0;
}

InteractPacket::InteractPacket(/*enum InteractPacket::Action, class ActorRuntimeID, Vec3 const&*/) {
	static uintptr_t** interactPacketVtable = 0x0;
	if (interactPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 01 88 51 30 4C 89 41 ?");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		interactPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (interactPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(InteractPacket));  // Avoid overwriting vtable
	vTable = interactPacketVtable;
}

ActorEventPacket::ActorEventPacket() {
	static uintptr_t** actorEvenPacketVtable = 0x0;
	if (actorEvenPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("E8 ? ? ? ? 90 49 8B 06 49 8B CE 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 4C 8B C0 48 8B 08 ");
		int offset = *reinterpret_cast<int*>(sigOffset + 1);
		actorEvenPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (actorEvenPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(ActorEventPacket));  // Avoid overwriting vtable
	vTable = actorEvenPacketVtable;
}

ActorEventPacket::ActorEventPacket(uint64_t entityRuntimeId, char eventId, int16_t itemId) {
	static uintptr_t** actorEvenPacketVtable = 0x0;
	if (actorEvenPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("E8 ? ? ? ? 90 49 8B 06 49 8B CE 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 4C 8B C0 48 8B 08 ");
		int offset = *reinterpret_cast<int*>(sigOffset + 1);
		actorEvenPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (actorEvenPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(ActorEventPacket));  // Avoid overwriting vtable
	vTable = actorEvenPacketVtable;
	this->entityRuntimeId = entityRuntimeId;
	this->eventId = eventId;
	this->itemId = itemId;
}