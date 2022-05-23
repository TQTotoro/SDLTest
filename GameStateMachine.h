#ifndef __GAMESTATEMACHINE_H__
#define __GAMESTATEMACHINE_H__

#include <vector>

#include "GameState.h"

class GameStateMachine
{
public:
	GameStateMachine() : newState(nullptr), popStateFlag(false), changeStateFlag(false) {}
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

	void update();
	void render();

private:
	// �洢��ͬ����Ϸ״̬��ʹ�ö�̬����
	std::vector<GameState*> m_gameStates;

	// ����״̬�仯�ľ��幤��
	void popStatePrivate();
	void changeStatePrivate(GameState* pState);

	GameState* newState;
	bool popStateFlag;
	bool changeStateFlag;
};

#endif // __GAMESTATEMACHINE_H__