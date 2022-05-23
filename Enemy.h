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

	// ���������ֽ����� load ��������
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