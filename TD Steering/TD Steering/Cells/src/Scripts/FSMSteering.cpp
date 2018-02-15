#include "stdafx.h"

#include "Scripts\FSMSteering.h"
#include "Scripts\Messages.h"
#include "AI\Behaviour.h"
#include <string.h>

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

		OnMsg(MSG_Pursuit)
			SetState(STATE_Pursuit);

		OnMsg(MSG_Evasion)
			SetState(STATE_Evasion);

		OnMsg(MSG_Arrival)
			SetState(STATE_Arrival);

		OnMsg(MSG_ObstacleAvoidance)
			SetState(STATE_ObstacleAvoidance);

		OnMsg(MSG_Wander)
			SetState(STATE_Wander);

		OnMsg(MSG_PathFollowing)
			SetState(STATE_PathFollowing);

		OnMsg(MSG_UCA)
			SetState(STATE_UCA);

		OnMsg(MSG_Separation)
			SetState(STATE_Separation);

		OnMsg(MSG_Cohesion)
			SetState(STATE_Cohesion);

		OnMsg(MSG_Alignement)
			SetState(STATE_Alignement);

		OnMsg(MSG_Flocking)
			SetState(STATE_Flocking);

		OnMsg(MSG_LeadFollowing)
			SetState(STATE_LeadFollowing);

		OnMsg(MSG_FormationV)
			SetState(STATE_FormationV);

		OnMsg(MSG_FormationLine)
			SetState(STATE_FormationLine);

		OnMsg(MSG_FormationCircle)
			SetState(STATE_FormationCircle);

		OnMsg(MSG_Formation2Level)
			SetState(STATE_Formation2Level);

		OnMsg(MSG_FF)
			SetState(STATE_FF);

		OnMsg(MSG_FormationDynamique)
			SetState(STATE_FormationDynamique);
			
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
					m_pCharacterController->setAction(kAct_Walk);
					m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_Flee)
			OnEnter
				m_pCharacterController->setCondition(kACond_Default);
				m_pCharacterController->setAction(kAct_Walk);
				m_pSteering->ClearBehaviors();
				m_pSteering->AddBehavior(new Flee(m_pSteering, m_pTarget), 1.0f);
			OnUpdate
				m_pCharacterController->setAction(kAct_Walk);
				m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_Pursuit)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
			m_pCharacterController->setAction(kAct_Walk);
			m_pSteering->ClearBehaviors();
			m_pSteering->AddBehavior(new Pursuit(m_pSteering, m_pTarget, 200.0f), 1.0f);
		OnUpdate
			m_pCharacterController->setAction(kAct_Walk);
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_Evasion)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
			m_pCharacterController->setAction(kAct_Walk);
			m_pSteering->ClearBehaviors();
			m_pSteering->AddBehavior(new Evasion(m_pSteering, m_pTarget, 200.0f), 1.0f);
		OnUpdate
			m_pCharacterController->setAction(kAct_Walk);
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_Arrival)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
			m_pCharacterController->setAction(kAct_Walk);
			m_pSteering->ClearBehaviors();
			m_pSteering->AddBehavior(new Arrival(m_pSteering, m_pTarget, 200.0f), 1.0f);
		OnUpdate
			m_pCharacterController->setAction(kAct_Walk);
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_ObstacleAvoidance)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
			m_pCharacterController->setAction(kAct_Walk);
			m_pSteering->ClearBehaviors();
			m_pSteering->AddBehavior(new ObstacleAvoidance(m_pSteering, 32.0f, 5.0f, m_vObstacles), 200.0f);
			m_pSteering->AddBehavior(new Seek(m_pSteering, m_pTarget), 1.0f);
		OnUpdate
			m_pCharacterController->setAction(kAct_Walk);
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_Wander)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
			m_pCharacterController->setAction(kAct_Walk);
			m_pSteering->ClearBehaviors();
			m_pSteering->AddBehavior(new Wander(m_pSteering, 32.0f, 32.0f, 2.0f), 1.0f);
			m_pSteering->AddBehavior(new ObstacleAvoidance(m_pSteering, 32.0f, 5.0f, m_vObstacles), 20.0f);
		OnUpdate
			m_pCharacterController->setAction(kAct_Walk);
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_PathFollowing)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
			m_pCharacterController->setAction(kAct_Walk);
			m_pSteering->ClearBehaviors();
			m_pSteering->AddBehavior(new PathFollowing(m_pSteering, 1.5f, 5.0f, 10.0f, m_vPath), 1.0f);
		OnUpdate
			m_pCharacterController->setAction(kAct_Walk);
			m_pCharacterController->move(m_pSteering->getVelocity());
		OnExit
			m_pSteering->pTarget = NULL;
		///////////////////////////////////////////////////////////////
		State(STATE_UCA)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
		m_pCharacterController->setAction(kAct_Walk);
		m_pSteering->ClearBehaviors();
		m_pSteering->AddBehavior(new UnalignedCollisionAvoidance(m_pSteering, 120.0f, m_vTargets), 200.0f);
		m_pSteering->AddBehavior(new Seek(m_pSteering, m_pTarget), 1.0f);
		
		OnUpdate
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_Separation)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
		m_pCharacterController->setAction(kAct_Walk);
		m_pSteering->ClearBehaviors();
		m_pSteering->AddBehavior(new Separation(m_pSteering, 100.0f, m_vTargets), 2.0f);
		m_pSteering->AddBehavior(new Seek(m_pSteering, m_pTarget), 1.0f);
		OnUpdate
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_Cohesion)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
		m_pCharacterController->setAction(kAct_Walk);
		m_pSteering->ClearBehaviors();
		m_pSteering->AddBehavior(new Cohesion(m_pSteering, 100.0f, m_vTargets), 2.0f);
		m_pSteering->AddBehavior(new Seek(m_pSteering, m_pTarget), 1.0f);
		OnUpdate
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_Alignement)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
		m_pCharacterController->setAction(kAct_Walk);
		m_pSteering->ClearBehaviors();
		m_pSteering->AddBehavior(new Alignment(m_pSteering, 50.0f, m_vTargets), 50.0f);
		m_pSteering->AddBehavior(new Seek(m_pSteering, m_pTarget), 1.0f);
		OnUpdate
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_Flocking)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
		m_pCharacterController->setAction(kAct_Walk);
		m_pSteering->ClearBehaviors();
		m_pSteering->AddBehavior(new Swarming(m_pSteering, m_pTarget, 2.0f), 10.0f);

		OnUpdate
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_LeadFollowing)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
		m_pCharacterController->setAction(kAct_Walk);
		m_pSteering->ClearBehaviors();
		m_pSteering->AddBehavior(new LeadFollowing(m_pSteering, m_pTarget, 75.0f, 180.0f, 30.0f, 45.0f), 1.0f);
		OnUpdate
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_FormationV)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
		m_pCharacterController->setAction(kAct_Walk);
		m_pSteering->ClearBehaviors();
		m_pSteering->AddBehavior(new FormationV(m_pSteering, m_pTarget, false, 5, id, 5, 50.0f, 30.0f, 20.0f), 1.0f);
		OnUpdate
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_FormationLine)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
		m_pCharacterController->setAction(kAct_Walk);
		m_pSteering->ClearBehaviors();
		m_pSteering->AddBehavior(new FormationLine(m_pSteering, m_pTarget, 5, id, 5, 40.0f, 30.0f, 40.0f), 1.0f);
		OnUpdate
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_FormationCircle)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
		m_pCharacterController->setAction(kAct_Walk);
		m_pSteering->ClearBehaviors();
		m_pSteering->AddBehavior(new FormationCircle(m_pSteering, m_pTarget, false, 5, id, 5, 100.0f, 40.0f, 0.0f, 360.0f, 80.0f), 1.0f);
		OnUpdate
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_Formation2Level)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
		m_pCharacterController->setAction(kAct_Walk);
		m_pSteering->ClearBehaviors();
		m_pSteering->AddBehavior(new Seek(m_pSteering, m_pTarget), 1.0f);
		OnUpdate
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_FF)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
		m_pCharacterController->setAction(kAct_Walk);
		m_pSteering->ClearBehaviors();
		m_pSteering->AddBehavior(new Seek(m_pSteering, m_pTarget), 1.0f);
		OnUpdate
			m_pCharacterController->move(m_pSteering->getVelocity());
		///////////////////////////////////////////////////////////////
		State(STATE_FormationDynamique)
			OnEnter
			m_pCharacterController->setCondition(kACond_Default);
		m_pCharacterController->setAction(kAct_Walk);
		m_pSteering->ClearBehaviors();
		m_pSteering->AddBehavior(new FormationDynamic(m_pSteering, m_pTarget, false, 5, id, 5, 40.0f, 30.0f, 0.0f, 360.0f, 80.0f), 1.0f);
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