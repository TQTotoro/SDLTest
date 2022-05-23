#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* pState)
{
	m_gameStates.push_back(pState);

	// 一旦进入状态机，立即进行初始化
	m_gameStates.back()->onEnter();
}

void GameStateMachine::popStatePrivate()
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExit())
		{
			// 先释放资源，然后从状态机中删除
			delete m_gameStates.back(); 
			m_gameStates.pop_back();
		}
	}
}

void GameStateMachine::changeStatePrivate(GameState* pState)
{
	if (!m_gameStates.empty())
	{
		// 保持同一状态，不需要更新
		if (m_gameStates.back()->getStateID() == pState->getStateID())
		{
			return; // do nothing
		}
		// 释放旧状态
		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}

		// 对于即将进入状态机的GameState, 如果状态机中已有该状态，则先删除原有GameState，防止占用多余资源
		// we eliminate them to free memory and an unneeded State
		for (auto it = m_gameStates.begin(); it != m_gameStates.end(); ++it)
		{
			if (((*it)->getStateID() == pState->getStateID()) && ((*it)->onExit()))
			{
				delete (*it);
				m_gameStates.erase(it);
				break;
			}
		}
	}

	// push back our new state
	m_gameStates.push_back(pState);

	// initialise it
	m_gameStates.back()->onEnter();
}

void GameStateMachine::update()
{
	// 先更新当前状态，然后根据需要进一步处理状态机
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update();
	}

	if (changeStateFlag)
	{
		changeStatePrivate(newState);
		changeStateFlag = false;
	}
	else if (popStateFlag)
	{
		popStatePrivate();
		popStateFlag = false;
	}
}

void GameStateMachine::render()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->render();
	}
}

void GameStateMachine::changeState(GameState* pState)
{
	changeStateFlag = true;
	newState = pState;
}

void GameStateMachine::popState()
{
	popStateFlag = true;
}

