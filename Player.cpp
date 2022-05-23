#include "Player.h"
#include "InputHandle.h"
#include <string>
#include <SDL2/SDL.h>"

Player::Player() : SDLGameObject() {}

void Player::draw()
{
	SDLGameObject::draw();
}

// ��д�Լ��� update �汾, �����¼�����״̬
/*
void Player::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(0.5);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-0.5);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		m_velocity.setY(-0.5);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_velocity.setY(0.5);
	}

	SDLGameObject::update();

//	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
//	m_acceleration.setX(0.01);
//	SDLGameObject::update();
}
*/

void Player::update()
{
	handleInput();

	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));

	SDLGameObject::update();
}

void Player::clean() {}

// ��������ƶ�
void Player::handleInput()
{
	Vector2D* target = TheInputHandler::Instance()->getMousePosition();
	m_velocity = *target - m_position;
	m_velocity /= 20;
}

void Player::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}
