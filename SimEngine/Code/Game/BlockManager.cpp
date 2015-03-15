#include "../Game/BlockManager.h"
#include "../Game/BreakoutFactory.h"
#include "../Collision/FragileCollisionComponent.h"
#include "../Foundation/Foundation.h"
#include "../Foundation/StringUtils.h"

BlockManager::BlockManager(std::vector<GameObject*>& outGameObjects, std::string instrLevelLayout) : mAllBlocksDead(false)
{
	for(uint32_t i = 0; i < BLOCK_COLS; ++i)
	{
		for(uint32_t j = 0; j < BLOCK_ROWS; ++j)
		{
			//mBlocks[i][j] = CreateBlock(Vector3(-0.8f + i * 0.3f, 0.8f - j * 0.3f, 0.f));
			mBlocks[i][j]->SetName("Block" + ConvertNumber(i));
		}
	}
}

BlockManager::~BlockManager()
{
	for(uint32_t i = 0; i < BLOCK_COLS; ++i)
	{
		for(uint32_t j = 0; j < BLOCK_ROWS; ++j)
		{
			SAFE_DELETE(mBlocks[i][j]);
		}
	}
}

void BlockManager::Update(float in_dt)
{
	if(mAllBlocksDead)
		return;

	bool blocksDead = true;

	for(uint32_t i = 0; i < BLOCK_COLS; ++i)
	{
		for(uint32_t j = 0; j < BLOCK_ROWS; ++j)
		{
			if(mBlocks[i][j] != NULL)
			{
				blocksDead = false;

                for(uint32_t k = 0; k < mBlocks[i][j]->m_components.size(); ++k)
				{
					// TODO Replace FragileCollisionComp with a BlockModel component and have it just listen to collision events from it's owner
					FragileCollisionComponent* const fragComp = dynamic_cast<FragileCollisionComponent*>(mBlocks[i][j]->m_components[k]);
					if(fragComp)
					{
						mBlocks[i][j]->Update(in_dt);

						if(fragComp->mDead)
						{
                            // Probably shouldn't be deleting this here, instead should be in StateLevelone
							SAFE_DELETE(mBlocks[i][j]);

							break;
						}
					}
				}
			}
		}
	}

	if(blocksDead)
		mAllBlocksDead = true;
}