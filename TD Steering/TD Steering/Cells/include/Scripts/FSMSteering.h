/***************************************************/
/* Nom:	FSMSteering.h
/* Description: FSMSteering
/* Auteur: DAMIENS Sébastien
/***************************************************/
#ifndef __FSMSteering_H_
#define __FSMSteering_H_

#include "AI\StateMachine.h"
#include "Scripts\CharacterController.h"

using namespace crea;

class FSMSteering : public StateMachine
{
	Entity*			m_pEntity;
	CharacterController* m_pCharacterController;
	Agent*			m_pAgent;
	Steering*		m_pSteering;

	bool			m_bPaused;

	int				m_iLife;

public:
	FSMSteering();
	virtual ~FSMSteering();
	
	virtual bool States(StateMachineEvent _event, Msg* _msg, int _state);
	Steering*			m_pTarget;
	vector<Steering*>*	m_vTargets;
	vector<Obstacle*>*	m_vPath;
	vector<Obstacle*>*	m_vObstacles;
	int id;

	//Add new states here
	enum States {
		STATE_Spawn,
		STATE_Live,
		STATE_Die,
		STATE_Seek,
		STATE_Flee,
		STATE_Pursuit,
		STATE_Evasion,
		STATE_Arrival,
		STATE_ObstacleAvoidance,
		STATE_Wander,
		STATE_PathFollowing,
		STATE_UCA,
		STATE_Separation,
		STATE_Cohesion,
		STATE_Alignement,
		STATE_Flocking,
		STATE_LeadFollowing,
		STATE_FormationV,
		STATE_FormationLine,
		STATE_FormationCircle,
		STATE_Formation2Level,
		STATE_FF,
		STATE_FormationDynamique
	};
};

#endif
