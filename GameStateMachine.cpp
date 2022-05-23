#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* pState)
{
	m_gameStates.push_back(pState);

	// һ������״̬�����������г�ʼ��
	m_gameStates.back()->onEnter();
}

void GameStateMachine::popStatePrivate()
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExit())
		{
			// ���ͷ���Դ��Ȼ���״̬����ɾ��
			delete m_gameStates.back(); 
			m_gameStates.pop_back();
		}
	}
}

void GameStateMachine::changeStatePrivate(GameState* pState)
{
	if (!m_gameStates.empty())
	{
		// ����ͬһ״̬������Ҫ����
		if (m_gameStates.back()->getStateID() == pState->getStateID())
		{
			return; // do nothing
		}
		// �ͷž�״̬
		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}

		// ���ڼ�������״̬����GameState, ���״̬�������и�״̬������ɾ��ԭ��GameState����ֹռ�ö�����Դ
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
	// �ȸ��µ�ǰ״̬��Ȼ�������Ҫ��һ������״̬��
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

