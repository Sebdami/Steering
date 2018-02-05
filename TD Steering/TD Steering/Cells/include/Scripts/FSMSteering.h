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
};

#endif
