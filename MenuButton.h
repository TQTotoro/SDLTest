#ifndef __MENUBUTTON_H__
#define __MENUBUTTON_H__

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class MenuButton : public SDLGameObject
{
public:

	MenuButton();

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void load(const LoaderParams* pParams);
	void setCallback(void(*callback)()) { m_callback = callback; }
	int getCallbackID() { return m_callbackID; }

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};
	
	// 回调函数
	void(*m_callback)();

	// 辅助确认是否按下按钮
	bool m_bReleased;

	// 回调函数ID
	int m_callbackID;
};

class MenuButtonCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new MenuButton();
	}
};


#endif // __MENUBUTTON_H__