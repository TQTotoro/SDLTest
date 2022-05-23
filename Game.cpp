#include <iostream>
#include <vector>
#include "Game.h"
#include "TextureManager.h"
#include "InputHandle.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"


// 静态变量初始化
Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = 0;
		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}

		std::cout << "SDL init success\n";
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow != 0) // window init success
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}

	m_gameWidth = width;
	m_gameHeight = height;

	// 事件类 初始化
	TheInputHandler::Instance()->initialiseJoysticks();

	std::cout << "init success\n";
	m_bRunning = true; // everything inited successfully, start the main loop

	TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

	// 游戏引擎初始化
	m_pGameStateMachine = new GameStateMachine();
	// 直接进入 MainMenuState
	m_pGameStateMachine->changeState(new MainMenuState());


//	m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
//	m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "animate")));

	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	/*
	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
	*/

	m_pGameStateMachine->render();

	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = NULL;
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = NULL;

	/*
	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		m_gameObjects[i] = NULL;
	}
	*/

	if (m_pGameStateMachine != NULL) {
		delete m_pGameStateMachine;
		m_pGameStateMachine = NULL;
	}
	if (s_pInstance != NULL) {
		delete s_pInstance;
		s_pInstance = NULL;
	}

	TheInputHandler::Instance()->clean();

	SDL_Quit();

}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(new PlayState());
	}
}

void Game::update()
{
	/*
	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
	*/

	m_pGameStateMachine->update();

}

