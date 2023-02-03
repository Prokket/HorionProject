#include "Disabler.h"

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

Disabler::Disabler() : IModule(0x0, Category::SERVER, "Nethergames Fly Disabler") {
	this->registerBoolSetting("Lifeboat", &this->netherDis, this->netherDis);
	// this->registerBoolSetting("Cubecraft", &this->ccDis, this->ccDis);
	// this->registerBoolSetting("Mineplex", &this->mineDis, this->mineDis);
	//this->registerBoolSetting("Mineville", &this->minevilleDis, this->minevilleDis);
}

Disabler::~Disabler() {
}

const char* Disabler::getModuleName() {
	return "Disabler";
}


void Disabler::onEnable() {
}

void Disabler::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	tick++;

	if (netherDis) {
		C_MovePlayerPacket packet(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&packet);
	

	}
}


void Disabler::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}


void Disabler::onSendPacket(C_Packet* packet) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	auto flight = moduleMgr->getModule<Fly>();

	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		auto player = g_Data.getLocalPlayer();
		if (netherDis && !player->onGround) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		}
	}
}