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

// ��ʼ��װ��һ����Ϸ����һ�����ں�һ����Ⱦ��
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
	// һ�����clean()������ר�Ÿ�����������
	~Game() {}

	// ���𴴽����ڼ���Ⱦ��
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	// ������Ⱦ
	void render();

	// ������Ϸ״̬
	void update();

	// �����û�����
	void handleEvents();

	// ɨβ����
	void clean();

	// �ж���Ϸ�Ƿ����
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

	// ��Ҫ�õ�����Ϸ����
//	GameObject m_go;
//	Player m_player;
// 
	// ����ָ�������Ϸ����, ���ö�̬����
//	GameObject* m_go;
//	GameObject* m_player;
//	GameObject* m_enemy;

	// �����׹������е���Ϸ����
//	std::vector<GameObject*> m_gameObjects;

	GameStateMachine* m_pGameStateMachine;

	static Game* s_pInstance;

};

typedef Game TheGame;

#endif // __GAME_H__