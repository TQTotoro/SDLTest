#ifndef __ANIMATEDGRAPHIC_H__
#define __ANIMATEDGRAPHIC_H__

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
public:

	AnimatedGraphic();

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void load(const LoaderParams* pParams);

private:

	// Ö¡ÇÐ»»ËÙ¶È
	int m_animSpeed;
};

class AnimatedGraphicCreator : public BaseCreator
{
public:
	GameObject* createGameObject() const
	{
		return new AnimatedGraphic();
	}
};

#endif /* defined(__ANIMATEDGRAPHIC_H__) */