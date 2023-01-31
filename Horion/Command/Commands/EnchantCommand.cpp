#include "EnchantCommand.h"
#include "../../../Utils/Utils.h"

EnchantCommand::EnchantCommand() : IMCCommand("enchant", "Enchants items", "<enchantment> [level] <mode: auto / manual : 1/0>") {
	enchantMap = {
		{"protection", 0},
		{"fire_protection", 1},
		{"feather_falling", 2},
		{"blast_protection", 3},
		{"projectile_protection", 4},
		{"thorns", 5},
		{"respiration", 6},
		{"depth_strider", 7},
		{"aqua_affinity", 8},
		{"frost_walker", 25},
		{"sharpness", 9},
		{"smite", 10},
		{"bane_of_arthropods", 11},
		{"knockback", 12},
		{"fire_aspect", 13},
		{"looting", 14},
		{"channeling", 32},
		{"impaling", 29},
		{"loyalty", 31},
		{"riptide", 30},
		{"silktouch", 16},
		{"fortune", 18},
		{"unbreaking", 17},
		{"efficiency", 15},
		{"mending", 26},
		{"power", 19},
		{"punch", 20},
		{"flame", 21},
		{"infinity", 22},
		{"multishot", 33},
		{"quick_charge", 35},
		{"piercing", 34},
		{"luck_of_sea", 23},
		{"lure", 24},
		{"soul_speed", 36}
	};
}

EnchantCommand::~EnchantCommand() {
}

bool EnchantCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() > 1);

	int enchantId = 0;
	int enchantLevel = 32767;
	bool isAuto = true;

	if (args->at(1) != "all") {
		try {
			// convert string to back to lower case
			std::string data = args->at(1);
			std::transform(data.begin(), data.end(), data.begin(), ::tolower);

			auto convertedString = enchantMap.find(data);
			if (convertedString != enchantMap.end())
				enchantId = convertedString->second;
			else
				enchantId = assertInt(args->at(1));
		} catch (int) {
			clientMessageF("exception while trying to get enchant string");
			enchantId = assertInt(args->at(1));
		}
	}

	if (args->size() > 2)
		enchantLevel = assertInt(args->at(2));
	if (args->size() > 3)
		isAuto = static_cast<bool>(assertInt(args->at(3)));

	PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
	Inventory* inv = supplies->inventory;
	InventoryTransactionManager* manager = Game.getLocalPlayer()->getTransactionManager();

	int selectedSlot = supplies->selectedHotbarSlot;
	ItemStack* item = inv->getItemStack(selectedSlot);

	InventoryAction* firstAction = nullptr;
	InventoryAction* secondAction = nullptr;

	ItemDescriptor* desc = nullptr;
	desc = new ItemDescriptor((*item->item)->itemId, 0); 

	if (isAuto) {
		{
			firstAction = new InventoryAction(supplies->selectedHotbarSlot, desc, nullptr, item, nullptr, item->count);
			if (strcmp(Game.getRakNetInstance()->serverIp.getText(), "mco.mineplex.com") == 0)
				secondAction = new InventoryAction(0, nullptr, desc, nullptr, item, item->count, 32766, 100);
			else 
				secondAction = new InventoryAction(0, nullptr, desc, nullptr, item, item->count, 507, 99999);
			manager->addInventoryAction(*firstAction);
			manager->addInventoryAction(*secondAction);
			delete firstAction;
			delete secondAction;
		}
	}

	using getEnchantsFromUserData_t = void(__fastcall*)(ItemStack*, void*);
	using addEnchant_t = bool(__fastcall*)(void*, __int64);
	using saveEnchantsToUserData_t = void(__fastcall*)(ItemStack*, void*);

	static getEnchantsFromUserData_t getEnchantsFromUserData = reinterpret_cast<getEnchantsFromUserData_t>(FindSignature("E8 ? ? ? ? 89 43 1C"));
	static addEnchant_t addEnchant = reinterpret_cast<addEnchant_t>(FindSignature("E8 ? ? ? ? 8D 0C 9D ? ? ? ?"));

	static saveEnchantsToUserData_t saveEnchantsToUserData = 0x0;
	if (!saveEnchantsToUserData) {
		saveEnchantsToUserData = reinterpret_cast<saveEnchantsToUserData_t>(FindSignature("E8 ? ? ? ? 90 4C 8D 0D ? ? ? ? BA 18 00 00 00 44 8D 42 ? 48 8D 4C 24 ? E8 ? ? ? ? 90 8B C3"));
	}

	if (strcmp(args->at(1).c_str(), "all") == 0) {
		for (int i = 0; i < 38; i++) {
			void* EnchantData = malloc(0x60);
			if (EnchantData != nullptr)
				memset(EnchantData, 0x0, 0x60);

			getEnchantsFromUserData(item, EnchantData);

			__int64 enchantPair = ((__int64)enchantLevel << 32) | i;

			if (addEnchant(EnchantData, enchantPair)) {  // Upper 4 bytes = level, lower 4 bytes = enchant type
				saveEnchantsToUserData(item, EnchantData);
				__int64 proxy = reinterpret_cast<__int64>(Game.getLocalPlayer()->getSupplies());
				if (!*(uint8_t*)(proxy + 168))
					(*(void(__fastcall**)(unsigned long long, unsigned long long, ItemStack*))(**(unsigned long long**)(proxy + 176) + 72i64))(
						*(unsigned long long*)(proxy + 176),
						*(unsigned int*)(proxy + 16),
						item);  // Player::selectItem

				 //Game.getLocalPlayer()->sendInventory();
			}
			free(EnchantData);
		}
		clientMessageF("%sEnchant successful!", GREEN);
	} else {
		void* EnchantData = malloc(0x60);
		if (EnchantData != nullptr)
			memset(EnchantData, 0x0, 0x60);

		getEnchantsFromUserData(item, EnchantData);

		__int64 enchantPair = ((__int64)enchantLevel << 32) | enchantId;

		if (addEnchant(EnchantData, enchantPair)) {  // Upper 4 bytes = level, lower 4 bytes = enchant type
			saveEnchantsToUserData(item, EnchantData);
			__int64 proxy = reinterpret_cast<__int64>(Game.getLocalPlayer()->getSupplies());
			if (!*(uint8_t*)(proxy + 168))
				(*(void(__fastcall**)(unsigned long long, unsigned long long, ItemStack*))(**(unsigned long long**)(proxy + 176) + 72i64))(
					*(unsigned long long*)(proxy + 176),
					*(unsigned int*)(proxy + 16),
					item);  // Player::selectItem

			//Game.getLocalPlayer()->sendInventory();
			clientMessageF("%sEnchant successful!", GREEN);
		} else
			clientMessageF("%sEnchant failed, try using a lower enchant-level", RED);

		free(EnchantData);
	}

	if (isAuto) {
		if (strcmp(Game.getRakNetInstance()->serverIp.getText(), "mco.mineplex.com") == 0)
			firstAction = new InventoryAction(0, desc, nullptr, item, nullptr, item->count, 32766, 100);
		else
			firstAction = new InventoryAction(0, desc, nullptr, item, nullptr, item->count, 507, 99999);
		secondAction = new InventoryAction(supplies->selectedHotbarSlot, nullptr, desc, nullptr, item, item->count);
		manager->addInventoryAction(*firstAction);
		manager->addInventoryAction(*secondAction);
		delete firstAction;
		delete secondAction;
	}

	return true;
}