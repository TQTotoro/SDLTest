#ifndef __MAINMENUSTATE_H__
#define __MAINMENUSTATE_H__

#include <vector>

#include "GameObject.h"
#include "MenuState.h"

class MainMenuState : public MenuState
{
public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; }

private:

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	// callback functions for menu items
	static void s_menuToPlay();
	static void s_exitFromMenu();

	static const std::string s_menuID;
	std::vector<GameObject*> m_gameObjects;
};

#endif // __MAINMENUSTATE_H__