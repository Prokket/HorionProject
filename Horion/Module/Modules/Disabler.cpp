#include "Disabler.h"

#include "Disabler.h"

Disabler::Disabler() : IModule(0, Category::MISC, "AntiCheat Blocker Works in Lifeboat") {
	this->registerBoolSetting("Lifeboat", &this->lifeboatDis, this->lifeboatDis);
}

Disabler::~Disabler() {}

const char* Disabler::getModuleName() {
	return "AntiCheat Blocker";
}

void Disabler::onTick(GameMode* gm) {
	if (lifeboatDis && !gm->player->onGround) {
		MovePlayerPacket pLifeboat(Game.getLocalPlayer(), *Game.getLocalPlayer()->getPos());
		pLifeboat.onGround = true;
		Game.getClientInstance()->loopbackPacketSender->sendToServer(&pLifeboat);
	}
}

void Disabler::onSendPacket(Packet* packet) {
	if (packet->isInstanceOf<MovePlayerPacket>()) {
		auto player = Game.getLocalPlayer();
		if (lifeboatDis && !player->onGround) {
			MovePlayerPacket* movePacket = reinterpret_cast<MovePlayerPacket*>(packet);
			movePacket->onGround = true;
		}
	}
}