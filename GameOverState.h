#ifndef __GAMEOVERSTATE_H__
#define __GAMEOVERSTATE_H__

#include <vector>
#include <string>

//#include "GameState.h"
#include "MenuState.h"


class GameObject;

class GameOverState : public MenuState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_gameOverID; }

private:
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
	
	static void s_gameOverToMain();
	static void s_restartPlay();

	static const std::string s_gameOverID;
	std::vector<GameObject*> m_gameObjects;
};

#endif // __GAMEOVERSTATE_H__