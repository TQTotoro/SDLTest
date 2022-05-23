#ifndef __SDLGAMEOBJECT_H__
#define __SDLGAMEOBJECT_H__

#include <string>

#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
	// ����ȱ�٣���Ҫ��ʼ������
//	SDLGameObject(const LoaderParams* pParams);
	SDLGameObject();

	virtual void load(const LoaderParams* pParams);

	virtual void draw();

	// ���ɾ��������ȥʵ��
	virtual void update();

	// ���������������ദ��
	virtual void clean() {};

	// ��ȡ��������
	Vector2D& getPosition() { return m_position; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

protected:
	// ��չԭ�е�λ������
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