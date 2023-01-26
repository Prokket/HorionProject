#include "Criticals.h"

Criticals::Criticals() : IModule(0, Category::COMBAT, "Each hit becomes a critical hit.") {
}

Criticals::~Criticals() {
}

const char* Criticals::getModuleName() {
	return ("Criticals");
}

void Criticals::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<MovePlayerPacket>() && Game.getLocalPlayer() != nullptr) {
		MovePlayerPacket* movePacket = reinterpret_cast<MovePlayerPacket*>(packet);
		movePacket->onGround = false;
	}
}
