/***************************************************/
/* Nom:	Steering.h
/* Description: Steering
/* Auteur: DAMIENS Sébastien
/***************************************************/
#ifndef __Steering_H_
#define __Steering_H_

#include "Core\Component.h"
#include "AI.h"

namespace crea
{
	class Behaviour;

	typedef std::pair<float, Behaviour*> typeWBehavior;

	class CREAENGINE_API Steering : public Component
	{
	protected:
		float m_mass;
		Vector2f m_velocity;
		float m_maxForce;
		float m_maxSpeed;

		//last force to render
		Vector2f m_lastForce;
		Vector2f m_lastR;

		int m_index;

		std::vector<typeWBehavior*> m_behaviors; // All the behaviors and their weight associated

	public:

		Steering();
		Steering(float _mass, Vector2f _velocity, float _maxForce, float _maxSpeed);
		virtual ~Steering();

		Vector2f Steer();

		void AddBehavior(Behaviour* _behavior, float _weight);
		void ClearBehaviors();

		inline float getMass() const { return m_mass; }
		Vector2f getPosition();
		inline Vector2f getVelocity() const { return m_velocity; }
		inline float getMaxForce() const { return m_maxForce; }
		inline float getMaxSpeed() const { return m_maxSpeed; }
		inline Vector2f getLastForce() const { return m_lastForce; }
		inline Vector2f getLastR() const { return m_lastR; }
		inline int getIndex() const { return m_index; }

		inline void setMass(const float& _mass) { m_mass = _mass; }
		inline void setVelocity(const Vector2f& _velocity) { m_velocity = _velocity; }
		inline void setMaxForce(const float& _maxForce) { m_maxForce = _maxForce; }
		inline void setMaxSpeed(const float& _maxSpeed) { m_maxSpeed = _maxSpeed; }
		inline void setLastR(const Vector2f& _lastR) { m_lastR = _lastR; }
		inline void setIndex(const int& _index) { m_index = _index; }


		bool loadFromFileJSON(string _filename);

		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();


	};

} // namespace crea

#endif
