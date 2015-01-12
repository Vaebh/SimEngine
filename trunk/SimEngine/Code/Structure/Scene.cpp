/*#include "../Structure/Scene.h"

// TODO - reconfigure to work with gameobjects and as a member variable of each state

Scene::Scene()
{

}

void Scene::AddToScene(GameObject* inGameObject)
{
	if(inGameObject)
	{
		mGameObjects.push_back(inGameObject);
		//inGameObject->SetOwningScene(const_cast<Scene*>(this));
	}
}

void Scene::RemoveFromScene(GameObject* inGameObject)
{
	if(inGameObject)
	{
		std::vector<GameObject*>::const_iterator iter;

		for(iter = mGameObjects.begin(); iter != mGameObjects.end(); ++iter)
		{
			if(*iter == inGameObject)
			{
				mGameObjects.erase(iter);
				break;
			}
		}
	}
}

void Scene::Update(float inDT)
{
    for(uint32_t i = 0; i < mGameObjects.size(); ++i)
    {
        mGameObjects[i]->Update(inDT);
    }
}*/