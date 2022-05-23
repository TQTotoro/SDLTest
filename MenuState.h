#ifndef __MENUSTATE_H__
#define __MENUSTATE_H__

#include "GameState.h"
#include "GameObject.h"
#include <vector>


class MenuState : public GameState
{
protected:
	// ��ť�������еĳ�Ա
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

	// ��������һ��ϸ�֣��� Game �·ŵ���ͬ�� Object ����
	std::vector<GameObject*> m_gameObjects;

	// �����°����󳡾����л����ص�����
	static void s_menuToPlay();
	static void s_exitFromMenu();
	*/

#endif // __MENUSTATE_H__