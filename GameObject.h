#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include "LoaderParams.h"

// ³éÏó»ùÀà
class GameObject
{
public:
	virtual void load(const LoaderParams* pParams) = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

protected:
	GameObject() {}
	virtual ~GameObject() {}
};

#endif // __GAMEOBJECT_H__