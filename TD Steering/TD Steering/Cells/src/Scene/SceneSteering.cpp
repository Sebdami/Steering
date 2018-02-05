#include "stdafx.h"

#include "Scene\SceneSteering.h"
#include "Scene\SceneMenu.h"
#include "Scene\SceneGame.h"


SceneSteering::SceneSteering()
{
	// Steering Tools
	m_bUseSteeringTools = true;
	m_pSteeringTools = new SteeringTools();
}

SceneSteering::~SceneSteering()
{
	// Steering Tools
	delete m_pSteeringTools;
}
	
bool SceneSteering::onInit()
{
	m_pGM = GameManager::getSingleton();

	// Set Script factory
	m_pCellsScriptFactory = new CellsScriptFactory;
	m_pGM->setScriptFactory(m_pCellsScriptFactory);

	// Load Map
	m_pEntity3 = m_pGM->getEntity("map0");
	m_pGM->addEntity(m_pEntity3);
	m_pMap = m_pGM->getMap("map0.json"); // CB: TO CHANGE: map id loaded after entity added to display map first (order in tree matters)
	m_pMapRenderer = m_pGM->getMapRenderer("MapRenderer1");
	m_pMapRenderer->setMap(m_pMap);
	m_pEntity3->addComponent(m_pMapRenderer);

	m_pMouseEntity = m_pGM->getEntity("mouseEntity");
	m_pMouseEntity->addComponent(new Steering(1, Vector2f(), 500, 200));
	m_pGM->getEntity("peon1")->getComponent<FSMSteering>()->m_pTarget = m_pMouseEntity->getComponent<Steering>();
	// Steering Tools
	if (m_bUseSteeringTools)
	{
		m_pSteeringTools->onInit();
	}

	return true;
}

bool SceneSteering::onUpdate()
{
	if (m_pGM->isKeyPressed(Key::Num1))
	{
		m_pGM->setScene(new SceneMenu());
		return true;
	}
	if (m_pGM->isKeyPressed(Key::Num2))
	{
		m_pGM->setScene(new SceneGame());
		return true;
	}
	m_pMouseEntity->getComponent<Steering>()->setVelocity((InputManager::getSingleton()->getMousePosition() - m_pMouseEntity->getPosition()) * 100.0f);
	m_pMouseEntity->setPosition(InputManager::getSingleton()->getMousePosition());

	// Steering Tools
	if (m_bUseSteeringTools)
	{
		m_pSteeringTools->onUpdate();
	}

	return true;
}

bool SceneSteering::onDraw()
{
	// Steering Tools
	if (m_bUseSteeringTools)
	{
		m_pSteeringTools->onDraw();
	}

	return true;
}

bool SceneSteering::onQuit()
{
	// Steering Tools
	if (m_bUseSteeringTools)
	{
		m_pSteeringTools->onQuit();
	}

	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	delete m_pCellsScriptFactory;

	return true;
}

