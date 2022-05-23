#ifndef __INPUTHANDLE_H__
#define __INPUTHANDLE_H__

#include <vector>
#include <utility>

#include <SDL2/SDL.h>
#include "Vector2D.h"


enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

// 处理不同的事件
class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new InputHandler();
		}

		return s_pInstance;
	}

	// 处理不同的事件
	void update();
	void clean();

	void initialiseJoysticks();
	bool joysticksInitialised() { return m_bJoysticksInitialised; }
	bool getButtonState(int joy, int buttonNumber)
	{
		return m_buttonStates[joy][buttonNumber];
	}

	// 鼠标
	bool getMouseButtonState(int buttonNumber)
	{
		return m_mouseButtonStates[buttonNumber];
	}
	Vector2D* getMousePosition()
	{
		return m_mousePosition;
	}

	// 键盘
	bool isKeyDown(SDL_Scancode key);

	void reset();

private:
	InputHandler();
	~InputHandler() { delete m_mousePosition; }

	static InputHandler* s_pInstance;

	// 操纵杆
	std::vector<SDL_Joystick*> m_joysticks;
	bool m_bJoysticksInitialised;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<std::vector<bool>> m_buttonStates;
	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);

	// 鼠标
	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;

	// 键盘
	const Uint8* m_keystates;

	const int m_joystickDeadZone = 10000;

	// handle keyboard events
	void onKeyDown();
	void onKeyUp();

	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	// handle joysticks events
	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);
};
typedef InputHandler TheInputHandler;

#endif // __INPUTHANDLE_H__