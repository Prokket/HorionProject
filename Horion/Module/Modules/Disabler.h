#pragma once
#include "Module.h"

class Disabler : public IModule {
public:
	bool netherDis = true;
	int multiplier = 30;
	int ticks = 4;
	int tick = 0;

	Disabler();
	~Disabler();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	void onEnable();
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onSendPacket(C_Packet* packet) override;
	// virtual void onSendPacket(C_Packet* packet) override;
	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;
};