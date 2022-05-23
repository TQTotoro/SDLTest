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
	// 存储不同的游戏状态，使用多态技术
	std::vector<GameState*> m_gameStates;

	// 负责状态变化的具体工作
	void popStatePrivate();
	void changeStatePrivate(GameState* pState);

	GameState* newState;
	bool popStateFlag;
	bool changeStateFlag;
};

#endif // __GAMESTATEMACHINE_H__