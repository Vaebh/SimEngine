#ifndef BLOCKMANAGER_SIMENGINE
#define BLOCKMANAGER_SIMENGINE

#include "../Structure/GameObject.h"
#include <vector>

const int BLOCK_COLS = 2;//6;
const int BLOCK_ROWS = 2;//4;

class BlockManager
{
public:
	BlockManager(std::vector<GameObject*>& outGameObjects, std::string instrLevelLayout);
	~BlockManager();

	void Update(float inDT);

	inline bool AreAllBlocksDead() const {return mAllBlocksDead;}

private:
	GameObject* mBlocks[BLOCK_COLS][BLOCK_ROWS];

	bool mAllBlocksDead;
};

#endif