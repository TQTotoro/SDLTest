#include "Enemy.h"
#include <string>
#include <SDL2/SDL.h>"

/*
Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	m_velocity.setY(2);
	m_velocity.setX(0.001);
}
*/

Enemy::Enemy() : SDLGameObject()
{

}

void Enemy::draw()
{
	SDLGameObject::draw();
}

// ��֤Enermy��������
void Enemy::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));

	if (m_position.getY() < 0)
	{
		m_velocity.setY(2);
	}
	else if (m_position.getY() > 400)
	{
		m_velocity.setY(-2);
	}

	SDLGameObject::update();
}

void Enemy::clean() {}

void Enemy::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);

	// ��ʼ�ٶ�
	m_velocity.setY(2);
}
