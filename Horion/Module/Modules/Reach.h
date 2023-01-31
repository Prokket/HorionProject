#pragma once

#include "Module.h"

class Reach : public IModule {
public:
	Reach();
	~Reach();

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
