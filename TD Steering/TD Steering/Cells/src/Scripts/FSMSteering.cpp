#include "stdafx.h"

#include "Scripts\FSMSteering.h"
#include "Scripts\Messages.h"
#include "AI\Behaviour.h"
#include <string.h>


//Add new states here
enum States {
	STATE_Spawn,
	STATE_Live,
	STATE_Die,
	STATE_Seek,
	STATE_Flee
};

FSMSteering::FSMSteering()
{

}

FSMSteering::~FSMSteering()
{

}

bool FSMSteering::States(StateMachineEvent _event, Msg* _msg, int _state)
{
	BeginStateMachine

		OnMsg(MSG_Reset)
			SetState(STATE_Spawn);

		OnMsg(MSG_Die)
			SetState(STATE_Die);

		OnMsg(MSG_Hit)
			m_iLife -= 20;
			if (m_iLife <= 0)
			{
				SetState(STATE_Die);
			}

		OnMsg(MSG_Boost)
			m_pAgent->setDexterity(m_pAgent->getDexterity() + 1);

		OnMsg(MSG_Seek)
			SetState(STATE_Seek);

		OnMsg(MSG_Flee)
			SetState(STATE_Flee);
			
		///////////////////////////////////////////////////////////////
		State(STATE_Spawn)
		OnEnter
			// Get Entity
			m_pEntity = getEntity();
			// Get CharacterController
			m_pCharacterController = m_pEntity->getComponent<CharacterController>();
			// Get Agent
			m_pAgent = m_pEntity->getComponent<Agent>();

			m_pSteering = m_pEntity->getComponent<Steering>();

			m_iLife = 100;

		OnUpdate
			SetState(STATE_Live);

		///////////////////////////////////////////////////////////////
		State(STATE_Seek)
			OnEnter
				m_pCharacterController->setCondition(kACond_Default);
				m_pCharacterController->setAction(kAct_Walk);
				m_pSteering->ClearBehaviors();
				m_pSteering->AddBehavior(new Seek(m_pSteering, m_pTarget), 1.0f);
				OnUpdate
					m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_Flee)
			OnEnter
				m_pCharacterController->setCondition(kACond_Default);
				m_pCharacterController->setAction(kAct_Walk);
				m_pSteering->ClearBehaviors();
				m_pSteering->AddBehavior(new Flee(m_pSteering, m_pTarget), 1.0f);
			OnUpdate
				m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_Live)

		OnUpdate
			if (m_iLife <= 0)
			{
				SetState(STATE_Die);
			}
			
		///////////////////////////////////////////////////////////////
		State(STATE_Die)
		OnUpdate
			m_pCharacterController->setCondition(kACond_Default);
			m_pCharacterController->setAction(kAct_Die);

EndStateMachine
}