#include "stdafx.h"

#include "AI\Steering.h"
#include "AI\Behaviour.h"
#include "Core\GameManager.h"
#include "json/json.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace crea
{
	Steering::Steering() :
		m_mass(1.0f),
		m_velocity(Vector2f(0.0f, 0.0f)),
		m_maxForce(100.0f),
		m_maxSpeed(100.0f),
		m_lastForce(Vector2f(0.0f, 0.0f)),
		m_lastR(Vector2f(1.0f, 0.0f))
		//pTarget(NULL)
	{}

	Steering::Steering(float _mass, Vector2f _velocity, float _maxForce, float _maxSpeed) :
		m_mass(_mass),
		m_velocity(_velocity),
		m_maxForce(_maxForce),
		m_maxSpeed(_maxSpeed),
		m_lastForce(Vector2f(0.0f, 0.0f)),
		m_lastR(Vector2f(1.0f, 0.0f))
		//pTarget(NULL)
	{}

	Steering::~Steering()
	{
		ClearBehaviors();
	}

	Vector2f Steering::getPosition() { return getEntity()->getPosition(); }

	void Steering::AddBehavior(Behaviour* _behavior, float _weight)
	{
		m_behaviors.push_back(new typeWBehavior(_weight, _behavior));
	}

	void Steering::ClearBehaviors()
	{
		for (int i = 0; i < (int)m_behaviors.size(); i++)
		{
			typeWBehavior* p = m_behaviors.back();
			delete(p->second);
			delete(p);
			m_behaviors.pop_back();
		}
		m_behaviors.clear();
	}

	Vector2f Steering::Steer()
	{
		Vector2f steeringDirection;
		for (int i = 0; i < (int)m_behaviors.size(); i++)
		{
			typeWBehavior* t = m_behaviors[i];
			Behaviour* b = (Behaviour*)t->second;
			steeringDirection += (t->second->Update() * t->first);
		}
		return steeringDirection;
	}

	bool Steering::update()
	{
		double _dt = TimeManager::getSingleton()->getFrameTime().asSeconds();
		Vector2f steeringDirection = Steer();

		if (!MathTools::zeroByEpsilon(steeringDirection.lengthSq()))
		{
			Vector2f steeringForce = MathTools::truncate(steeringDirection, m_maxForce);
			Vector2f acceleration = steeringForce / m_mass;
			m_velocity = MathTools::truncate(m_velocity + acceleration * _dt, m_maxSpeed);

			m_lastForce = steeringForce;
		}
		else
		{
			m_lastForce = Vector2f(0.0f, 0.0f);
		}
		//getEntity()->setVelocity(m_velocity);
		//getEntity()->move(m_velocity);
		return true;
	}

	bool Steering::loadFromFileJSON(string _filename)
	{
		Json::Value root;
		std::ifstream config_doc(_filename, std::ifstream::binary);
		config_doc >> root;

		m_mass = (short) root["Mass"].asFloat();
		m_maxForce = (short) root["MaxForce"].asFloat();
		m_maxSpeed = (short) root["MaxSpeed"].asFloat();

		return true;
	}

	bool Steering::init()
	{
		return true;
	}

	bool Steering::draw()
	{
		return true;
	}

	bool Steering::quit()
	{
		return true;
	}

} // namespace crea
