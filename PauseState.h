#ifndef __PAUSESTATE_H__
#define __PAUSESTATE_H__


#include <string>
#include <vector>
#include "MenuState.h"

class GameObject;

class PauseState : public MenuState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; }

private:
	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void s_pauseToMain();
	static void s_resumePlay();

	static const std::string s_pauseID;

	std::vector<GameObject*> m_gameObjects;
};



/*
#include "GameState.h"

class GameObject;

class PauseState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; }

private:
	static const std::string s_pauseID;
	
	// »Øµ÷º¯Êý
	static void s_pauseToMain();
	static void s_resumePlay();

	std::vector<GameObject*> m_gameObjects;
};
*/

#endif // __PAUSESTATE_H__
