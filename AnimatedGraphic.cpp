#include <SDL2/SDL.h>
#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : SDLGameObject()
{
}

void AnimatedGraphic::draw()
{
	SDLGameObject::draw();
}

// Game Over ��˸Ч��
void AnimatedGraphic::update()
{
	m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % 2));
}

void AnimatedGraphic::clean()
{
}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);

	// ���в���
	m_animSpeed = pParams->getAnimSpeed();
}