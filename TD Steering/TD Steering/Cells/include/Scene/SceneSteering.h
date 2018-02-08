/***************************************************/
/* Nom:	SceneSteering.h
/* Description: SceneSteering
/* Auteur: DAMIENS Sebastien
/***************************************************/
#ifndef __SceneSteering_H_
#define __SceneSteering_H_

#include "Core\Scene.h"
#include "SteeringTools.h"
#include "Scripts\CellsScriptFactory.h"
using namespace crea;

class SceneSteering : public Scene
{
	GameManager*	m_pGM;

	// Map
	Entity* m_pEntity3;
	Map* m_pMap;
	MapRenderer* m_pMapRenderer;

	Entity* m_pMouseEntity;

	// Steering Tools
	bool m_bUseSteeringTools;
	SteeringTools* m_pSteeringTools;

	// Scripts
	CellsScriptFactory* m_pCellsScriptFactory;

	vector<Obstacle*>* path;
	vector<Steering*>* targets;
public:

	SceneSteering();
	virtual ~SceneSteering();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
