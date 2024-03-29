#include "InfiniteAura.h"

InfiniteAura::InfiniteAura() : IModule(0, Category::COMBAT, "Killaura but with infinite reach.") {
	registerBoolSetting("MultiAura", &isMulti, isMulti);
	registerFloatSetting("Range", &range, range, 15, 100);
	registerIntSetting("Delay", &delay, delay, 15, 20);
}

InfiniteAura::~InfiniteAura() {
}

const char* InfiniteAura::getModuleName() {
	return ("InfiniteAura");
}

static std::vector<Entity*> targetList0;

void findEntities(Entity* currentEntity, bool isRegularEntitie) {
	static auto infiniteAuraMod = moduleMgr->getModule<InfiniteAura>();
	
	if (currentEntity == Game.getLocalPlayer())  // Skip Local player
		return;

	if (currentEntity == 0)
		return;

	if (currentEntity->timeSinceDeath > 0 || currentEntity->damageTime >= 7)
		return;

	if (FriendList::findPlayer(currentEntity->getNameTag()->getText()))  // Skip Friend
		return;

	if (!Target::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < infiniteAuraMod->range) {
		targetList0.push_back(currentEntity);
	}
}

void InfiniteAura::onTick(GameMode* gm) {

	//Loop through all our players and retrieve their information
	targetList0.clear();

	Game.forEachEntity(findEntities);
	Odelay++;

	if (targetList0.size() > 0 && Odelay >= delay) {
		Game.getLocalPlayer()->swingArm();

		float calcYaw = (gm->player->yaw + 90) * (PI / 180);
		float calcPitch = (gm->player->pitch) * -(PI / 180);

		float teleportX = cos(calcYaw) * cos(calcPitch) * 3.5f;
		float teleportZ = sin(calcYaw) * cos(calcPitch) * 3.5f;
		MovePlayerPacket teleportPacket;

		if (strcmp(Game.getRakNetInstance()->serverIp.getText(), "mco.cubecraft.net") == 0) {
			vec3_t pos = *Game.getLocalPlayer()->getPos();

			MovePlayerPacket movePlayerPacket(Game.getLocalPlayer(), pos);
			Game.getClientInstance()->loopbackPacketSender->sendToServer(&movePlayerPacket);

			pos.y += 0.35f;

			movePlayerPacket = MovePlayerPacket(Game.getLocalPlayer(), pos);
			Game.getClientInstance()->loopbackPacketSender->sendToServer(&movePlayerPacket);
		}

		// Attack all entitys in targetList
		if (isMulti) {
			for (int i = 0; i < targetList0.size(); i++) {
				vec3_t pos = *targetList0[i]->getPos();
				teleportPacket = MovePlayerPacket(Game.getLocalPlayer(), vec3_t(pos.x - teleportX, pos.y, pos.z - teleportZ));
				Game.getClientInstance()->loopbackPacketSender->sendToServer(&teleportPacket);
				Game.getCGameMode()->attack(targetList0[i]);
				teleportPacket = MovePlayerPacket(Game.getLocalPlayer(), *Game.getLocalPlayer()->getPos());
				Game.getClientInstance()->loopbackPacketSender->sendToServer(&teleportPacket);
			}
		} else {
			vec3_t pos = *targetList0[0]->getPos();
			teleportPacket = MovePlayerPacket(Game.getLocalPlayer(), vec3_t(pos.x - teleportX, pos.y, pos.z - teleportZ));
			Game.getClientInstance()->loopbackPacketSender->sendToServer(&teleportPacket);
			Game.getCGameMode()->attack(targetList0[0]);
			teleportPacket = MovePlayerPacket(Game.getLocalPlayer(), *Game.getLocalPlayer()->getPos());
			Game.getClientInstance()->loopbackPacketSender->sendToServer(&teleportPacket);
		}
		Odelay = 0;
	}
}
