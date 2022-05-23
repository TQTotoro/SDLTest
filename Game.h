#ifndef __GAME_H__
#define __GAME_H__

#include <SDL2/SDL.h>
#include <vector>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"

// 开始封装，一个游戏包含一个窗口和一个渲染器
class Game
{
public:
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
		}
		return s_pInstance;
	}
	// 一般调用clean()函数（专门负责清理工作）
	~Game() {}

	// 负责创建窗口及渲染器
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	// 负责渲染
	void render();

	// 更新游戏状态
	void update();

	// 处理用户输入
	void handleEvents();

	// 扫尾工作
	void clean();

	// 判断游戏是否进行
	bool running() { return m_bRunning; }
	void quit() { m_bRunning = false; }
	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

private:
	Game() {
		m_pWindow = NULL;
		m_pRenderer = NULL;
		m_bRunning = false;
		m_pGameStateMachine = NULL;
	};

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
//	SDL_Texture* m_pTexture; // the new SDL_Texture variable
//	SDL_Rect m_sourceRectangle; // the first rectangle
//	SDL_Rect m_destinationRectangle; // another rectangle

	bool m_bRunning;

//	int m_currentFrame;

	// 需要用到的游戏对象
//	GameObject m_go;
//	Player m_player;
// 
	// 改用指针管理游戏对象, 利用多态技术
//	GameObject* m_go;
//	GameObject* m_player;
//	GameObject* m_enemy;

	// 更容易管理所有的游戏对象
//	std::vector<GameObject*> m_gameObjects;

	GameStateMachine* m_pGameStateMachine;

	static Game* s_pInstance;

};

typedef Game TheGame;

#endif // __GAME_H__