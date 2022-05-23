#ifndef __SDLGAMEOBJECT_H__
#define __SDLGAMEOBJECT_H__

#include <string>

#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
	// 不可缺少，需要初始化基类
//	SDLGameObject(const LoaderParams* pParams);
	SDLGameObject();

	virtual void load(const LoaderParams* pParams);

	virtual void draw();

	// 交由具体的子类去实现
	virtual void update();

	// 不做处理，交由子类处理
	virtual void clean() {};

	// 获取基本属性
	Vector2D& getPosition() { return m_position; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

protected:
	// 扩展原有的位置坐标
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

//	int m_x;
//	int m_y;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;
	int m_numFrames;


	std::string m_textureID;
};

#endif // __SDLGAMEOBJECT_H__