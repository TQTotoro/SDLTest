#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include <string>
#include <vector>

// 记录游戏状态，虚基类
class GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;

	// 状态切换前后的处理工作
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;

protected:
	std::vector<std::string> m_textureIDList;
};

#endif // __GAMESTATE_H__
