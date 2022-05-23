#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

// 类成员变量直接继承而来，成员函数根据需求重写
class Player : public SDLGameObject
{
public:
	// 必不可少
	Player();

	void draw();
	void update();
	void clean();
	void load(const LoaderParams* pParams);

	// 主角新增交互功能
	void handleInput();

};

class PlayerCreator : public BaseCreator
{
public:
	GameObject* createGameObject() const
	{
		return new Player();
	}
};

#endif // __PLAYER_H__