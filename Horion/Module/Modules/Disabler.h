#pragma once
#include "Module.h"

class Disabler : public IModule {
public:
	bool lifeboatDis = true;
	int multiplier = 30;
	int ticks = 4;
	int tick = 0;

	Disabler();
	~Disabler();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	//void onEnable();
	virtual void onTick(GameMode* gm) override;
	//virtual void onMove(MoveInputHandler* input) override;
	virtual void onSendPacket(Packet* packet) override;
	// virtual void onSendPacket(Packet* packet) override;
	inline std::vector<MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
	std::vector<MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;
};