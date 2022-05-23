#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

// ���Ա����ֱ�Ӽ̳ж�������Ա��������������д
class Player : public SDLGameObject
{
public:
	// �ز�����
	Player();

	void draw();
	void update();
	void clean();
	void load(const LoaderParams* pParams);

	// ����������������
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