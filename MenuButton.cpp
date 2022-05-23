#include "MenuButton.h"
#include "Vector2D.h"
#include "InputHandle.h"

MenuButton::MenuButton() : SDLGameObject() 
{
	m_currentFrame = MOUSE_OUT; // start at frame 0
}

void MenuButton::draw()
{
	SDLGameObject::draw(); // use the base class drawing
}

// ��ť����Ҫ�ƶ�����д update ����
void MenuButton::update()
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

	if (pMousePos->getX() < (m_position.getX() + m_width)
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height)
		&& pMousePos->getY() > m_position.getY())
	{
		// ����������
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;
			m_callback(); // call our callback function
			m_bReleased = false;
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			// ���λ�ڰ�ť��
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}

void MenuButton::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	// �������в���
	m_callbackID = pParams->getCallbackID();
	m_currentFrame = MOUSE_OUT;
}