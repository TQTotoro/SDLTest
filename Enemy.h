#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <string>

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Enemy : public SDLGameObject
{
public:
//	Enemy(const LoaderParams* pParams);
	Enemy();
	void draw();
	void update();
	void clean();

	// 参数加载又交到了 load 函数手里
	virtual void load(const LoaderParams* pParams);
};

class EnemyCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Enemy();
	}
};

#endif // __ENEMY_H__