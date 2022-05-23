#ifndef __MENUSTATE_H__
#define __MENUSTATE_H__

#include "GameState.h"
#include "GameObject.h"
#include <vector>


class MenuState : public GameState
{
protected:
	// 按钮对象特有的成员
	typedef void(*Callback)();
	virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

	std::vector<Callback> m_callbacks;
};
	/*
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; }

private:

	static const std::string s_menuID;

	// 对象管理进一步细分，由 Game 下放到不同的 Object 类型
	std::vector<GameObject*> m_gameObjects;

	// 处理按下按键后场景的切换，回调函数
	static void s_menuToPlay();
	static void s_exitFromMenu();
	*/

#endif // __MENUSTATE_H__