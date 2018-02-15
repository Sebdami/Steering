/***************************************************/
/* Nom:	CellsScriptFactory.h
/* Description: CellsScriptFactory
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __CellsScriptFactory_H_
#define __CellsScriptFactory_H_

#include "Core\Script.h"
#include "CharacterController.h"
#include "UserController.h"
#include "Scripts\FSMPeon.h"
#include "Scripts\FSMBalista.h"
#include "Scripts\FSMSteering.h"


class CellsScriptFactory : public ScriptFactory
{
	virtual Script* create(string& _szName)
	{ 
		if (_szName == "CharacterController")
		{
			return new CharacterController;
		}
		else if (_szName == "CharacterControllerBalista")
		{
			return new CharacterController;
		}
		else if (_szName == "CharacterController2")
		{
			return new CharacterController;
		}
		else if (_szName == "CharacterController3")
		{
			return new CharacterController;
		}
		else if (_szName == "CharacterController4")
		{
			return new CharacterController;
		}
		else if (_szName == "CharacterController5")
		{
			return new CharacterController;
		}
		else if (_szName == "UserController")
		{
			return new UserController;
		}
		else if (_szName == "FSMPeon")
		{
			return new FSMPeon;
		}
		else if (_szName == "FSMBalista")
		{
			return new FSMBalista;
		}
		else if (_szName == "FSMSteering")
		{
			return new FSMSteering;
		}
		else if (_szName == "FSMSteering2")
		{
			return new FSMSteering;
		}
		else if (_szName == "FSMSteering3")
		{
			return new FSMSteering;
		}
		else if (_szName == "FSMSteering4")
		{
			return new FSMSteering;
		}
		else if (_szName == "FSMSteering5")
		{
			return new FSMSteering;
		}
		return nullptr;
	}
};

#endif
