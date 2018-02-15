#include "stdafx.h"

#include "Scene\SceneSteering.h"
#include "Scene\SceneMenu.h"
#include "Scene\SceneGame.h"
#include <string>

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

	//Create path
	path = new vector<Obstacle*>();

	path->push_back(new Obstacle(Vector2f(20.0f, 20.0f), 10.0f));
	path->push_back(new Obstacle(Vector2f(20.0f, 280.0f), 10.0f));
	path->push_back(new Obstacle(Vector2f(600.0f, 360.0f), 10.0f));
	path->push_back(new Obstacle(Vector2f(700.0f, 450.0f), 10.0f));
	path->push_back(new Obstacle(Vector2f(700.0f, 600.0f), 10.0f));
	path->push_back(new Obstacle(Vector2f(400.0f, 580.0f), 10.0f));

	m_pMouseEntity = m_pGM->getEntity("mouseEntity");
	m_pMouseEntity->addComponent(new Steering(1, Vector2f(), 500, 200));

	Entity* balista = m_pGM->getEntity("balista1");

	Entity* peon = m_pGM->getEntity("peon1");

	vector<Entity*> m_vPeonEntities;
	m_vPeonEntities.push_back(peon);
	
	// Define targets
	targets = new vector<Steering*>();
	targets->push_back(balista->getComponent<Steering>());

	for (int i = 0; i < 4; i++)
	{
		Entity* newEntity = m_pGM->getEntity("peon" + to_string(i + 2));
		string path = DATAAGENTPATH;
		path+= "Peon/Peon" + std::to_string(i + 2) + ".ent";
		newEntity->loadFromFileJSON(path);
		newEntity->init();
		newEntity->getComponent<SpriteRenderer>()->getSprite()->setOrigin(36.0f, 46.0f);
		newEntity->setPosition(Vector2f(100.0f + 50.0f * i, 75.0f));
		m_pGM->addEntity(newEntity);
		targets->push_back(newEntity->getComponent<Steering>());
		m_vPeonEntities.push_back(newEntity);
	}


	//Find obstacles
	obstacles = new vector<Obstacle*>();
	int iMin, iMax, jMin, jMax;
	m_pMap->getTileIndexLimits(iMin, iMax, jMin, jMax);
	for (int i = iMin; i < iMax; i++)
	{
		for (int j = jMin; j < jMax; j++)
		{
			if (m_pMap->getNode(i, j)->getTileCollisionId() != 0)
			{
				Vector2f position = Vector2f(i * 32 + 32, j*32 + 32);
				obstacles->push_back(new Obstacle(position, 16.0f));
			}
		}
	}
	
	/*MapStringCollider* pStaticColliders = PhysicsManager::getSingleton()->getStaticColliders();
	MapStringCollider* pDynamicColliders = PhysicsManager::getSingleton()->getDynamicColliders();
	for (auto i = pStaticColliders->begin(); i != pStaticColliders->end(); i++)
	{
		float radius;
		Vector2f position;

		switch ((*i).second->getColliderType())
		{
		case EnumColliderType::Collider_Box:
			radius = ((BoxCollider*)(*i).second)->getSize().getX() / 2.0f;
			position = ((BoxCollider*)(*i).second)->getOrigin() - Vector2f(radius, radius);
			break;
		case EnumColliderType::Collider_Circle:
			radius = ((CircleCollider*)(*i).second)->getRadius();
			position = ((CircleCollider*)(*i).second)->getCenter();
			break;
		}
		obstacles->push_back(new Obstacle(position, radius));
	}
*/
	/*for (auto i = pDynamicColliders->begin(); i != pDynamicColliders->end(); i++)
	{
		float radius;

		switch ((*i).second->getColliderType())
		{
		case EnumColliderType::Collider_Box:
			radius = ((BoxCollider*)(*i).second)->getSize().getX() / 2.0f;
			break;
		case EnumColliderType::Collider_Circle:
			radius = ((CircleCollider*)(*i).second)->getRadius();
			break;
		}
		obstacles->push_back(new Obstacle((*i).second->getEntity()->getPosition(), radius));
	}*/
	int id = 0;
	for (auto it = m_vPeonEntities.begin(); it != m_vPeonEntities.end(); it++)
	{
		FSMSteering* fsm =(*it)->getComponent<FSMSteering>();
		fsm->m_pTarget = m_pMouseEntity->getComponent<Steering>();
		targets->clear();
		for (auto j = m_vPeonEntities.begin(); j != m_vPeonEntities.end(); j++)
		{
			if ((*j) != (*it))
			{
				targets->push_back((*j)->getComponent<Steering>());
			}
		}
		targets->push_back(balista->getComponent<Steering>());
		fsm->m_vTargets = targets;
		fsm->m_vPath = path;
		fsm->m_vObstacles = obstacles;
		fsm->id = id++;
	}
	
	// Steering Tools
	if (m_bUseSteeringTools)
	{
		m_pSteeringTools->onInit();
	}

	return true;
}

bool SceneSteering::onUpdate()
{
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
	delete path;
	delete targets;
	delete obstacles;
	return true;
}

