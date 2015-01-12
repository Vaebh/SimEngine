#ifndef SYSTEM_SIMENGINE
#define SYSTEM_SIMENGINE

#include "../Structure/Component.h"
#include <string>
#include <vector>

class ISystem
{
public:
	//ISystem();
	//virtual ~ISystem();

	virtual void Update(float inDT) = 0;

	//virtual std::string GetSystemID() = 0;

//protected:
	//std::vector<IComponent*> mComponents;
};

#endif