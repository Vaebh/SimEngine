#include "../Structure/StateManager.h"
#include "../Foundation/Foundation.h"
#include <iostream>

StateManager* StateManager::mStateManager = NULL;

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
	while(!mStateHierarchy.empty())
	{
		SAFE_DELETE(mStateHierarchy.back());
		mStateHierarchy.pop_back();
	}

	mActiveState = NULL;
}

StateManager* StateManager::GetSingleton()
{
	if(!mStateManager)
	{
		mStateManager = new StateManager();
	}

	return mStateManager;
}

void StateManager::PushState(IState* const inNewState)
{
	mStateHierarchy.push_back(inNewState);
	mActiveState = inNewState;
    
    std::cout << "State pushed" << std::endl;
}

void StateManager::PopState()
{
	if(mStateHierarchy.empty())
		return;

	SAFE_DELETE(mStateHierarchy.back());
	mStateHierarchy.pop_back();

	if(!mStateHierarchy.empty())
		mActiveState = mStateHierarchy.back();
	else
		mActiveState = NULL;
}

const IState* StateManager::GetActiveState() const
{
	return mStateHierarchy.back();
}

void StateManager::Update(float inDT)
{
	if(mActiveState != NULL)
		mActiveState->Update(inDT);
}