#include "stdafx.h"

#include "AI\Behaviour.h"
#include "AI\Steering.h"
#include "Core\GameManager.h"
#include "json/json.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace crea
{
	Behaviour::Behaviour(Steering* _steering)
		: m_steering(_steering), m_desiredVelocity(), m_steeringForce(Vector2f()), m_offset(Vector2f())
	{
	};

	Vector2f& Seek::Update()
	{
		Vector2f m_vTargetPos = m_target->getPosition();
		m_desiredVelocity = m_vTargetPos - m_steering->getPosition();
		m_desiredVelocity.normalize();
		m_desiredVelocity *= m_steering->getMaxSpeed();
		m_steeringForce = m_desiredVelocity - m_steering->getVelocity();
		return m_steeringForce;
	}

	Vector2f& Flee::Update()
	{
		m_desiredVelocity = m_steering->getPosition() - m_target->getPosition();
		m_desiredVelocity.normalize();
		m_desiredVelocity *= m_steering->getMaxSpeed();
		m_steeringForce = m_desiredVelocity - m_steering->getVelocity();
		return m_steeringForce;
	}

	//Vector2f& Pursuit::Update()
	//{
	//	Vector2f targetOffset = m_steering->getPosition() - m_target->getPosition();
	//	double fT = MathTools::min(m_fTmax, targetOffset.length());
	//	Vector2f prediction = m_target->getPosition() + m_target->getVelocity() * fT;
	//	m_desiredVelocity = prediction - m_steering->getPosition();
	//	m_desiredVelocity.normalize();
	//	m_desiredVelocity *= m_steering->getMaxSpeed();
	//	m_steeringForce = m_desiredVelocity - m_steering->getVelocity();
	//	return m_steeringForce;
	//}

	//Vector2f& Evasion::Update()
	//{
	//	Vector2f targetOffset = m_steering->getPosition() - m_target->getPosition();
	//	double fT = MathTools::min(m_fTmax, targetOffset.length());
	//	Vector2f prediction = m_target->getPosition() + m_target->getVelocity() * fT;
	//	m_desiredVelocity = m_steering->getPosition() - prediction;
	//	m_desiredVelocity.normalize();
	//	m_desiredVelocity *= m_steering->getMaxSpeed();
	//	m_steeringForce = m_desiredVelocity - m_steering->getVelocity();
	//	return m_steeringForce;
	//}

	//Vector2f& Arrival::Update()
	//{
	//	Vector2f targetOffset = m_target->getPosition() - m_steering->getPosition();
	//	double distance = targetOffset.length();
	//	double rampedSpeed = m_steering->getMaxSpeed() * distance / m_fSlowingDistance;
	//	double clippedSpeed = MathTools::min(rampedSpeed, m_steering->getMaxSpeed());
	//	m_desiredVelocity = targetOffset * (clippedSpeed / distance);
	//	m_steeringForce = m_desiredVelocity - m_steering->getVelocity();
	//	return m_steeringForce;
	//}

	//Vector2f& Wander::Update()
	//{
	//	Vector2f direction = m_steering->getVelocity();
	//	direction.normalize();

	//	Vector2f center = direction * (m_steering->getMaxForce() - m_radius);

	//	double value = (double)(rand() % 360);
	//	Vector2f r(sin(value*PI / 180.0f) * m_littleRadius, cos(value*PI / 180.0f) * m_littleRadius);
	//	Vector2f R = m_steering->getLastR();
	//	R += r;
	//	R.normalize();
	//	R *= m_radius;
	//	m_steeringForce = center + R;
	//	m_steering->setLastR(R);

	//	return m_steeringForce;
	//}

	//Vector2f& PathFollowing::Update()
	//{
	//	Vector2f position = m_steering->getPosition() + m_steering->getVelocity() * m_fC;
	//	double distMin = INFINITY;
	//	std::vector<Obstacle*>::iterator j;

	//	// if no target yet
	//	if (m_steering->pTarget == NULL)
	//	{
	//		// Compute closest waypoints
	//		for (std::vector<Obstacle*>::iterator i = m_obstacles->begin(); i != m_obstacles->end(); i++)
	//		{
	//			Vector2f obstaclePosition = (*i)->m_position;
	//			double dist = (position - obstaclePosition).length();

	//			if (dist < distMin) {
	//				distMin = dist;
	//				// take next as target (if one exist)
	//				j = i;
	//				j++;
	//				if (j != m_obstacles->end())
	//					m_steering->pTarget = *j;
	//				else
	//					m_steering->pTarget = *i;
	//			}
	//		}
	//	}

	//	if ((m_steering->pTarget->m_position - m_steering->getPosition()).length() < m_steering->pTarget->m_radius)
	//	{
	//		// Find next waypoint
	//		for (std::vector<Obstacle*>::iterator i = m_obstacles->begin(); i != m_obstacles->end(); i++)
	//		{
	//			if (*i == m_steering->pTarget)
	//			{
	//				// take next as target (if one exist)
	//				j = i;
	//				j++;
	//				if (j != m_obstacles->end())
	//					m_steering->pTarget = *j;
	//				else
	//					m_steering->pTarget = *i;
	//				break;
	//			}
	//		}
	//	}

	//	// Seek on target
	//	m_desiredVelocity = m_steering->pTarget->m_position - m_steering->getPosition();
	//	m_desiredVelocity.normalize();
	//	m_desiredVelocity *= m_steering->getMaxSpeed();
	//	m_steeringForce = m_desiredVelocity - m_steering->getVelocity();

	//	return m_steeringForce;
	//}

	//Vector2f& UnalignedCollisionAvoidance::Update()
	//{
	//	Vector2f nextPosition = m_steering->getPosition() + m_steering->getVelocity() / 2.0f;
	//	Vector2f nextPosition2, diff;
	//	m_steeringForce = ORIGIN2;
	//	for (std::vector<Steering*>::iterator i = m_entities->begin(); i != m_entities->end(); i++)
	//	{
	//		if ((*i) != m_steering)
	//		{
	//			nextPosition2 = (*i)->getPosition() + (*i)->getVelocity() / 2.0f;
	//			diff = nextPosition - nextPosition2;
	//			if (diff.length() < m_radius)
	//			{
	//				m_steeringForce += diff;
	//			}
	//		}
	//	}
	//	return m_steeringForce;
	//}

	//Vector2f& ObstacleAvoidance::Update()
	//{
	//	Vector2f position = m_steering->getPosition();
	//	Vector2f direction = m_steering->getVelocity();
	//	direction.normalize();

	//	double distance = INFINITY;
	//	double fleeDirection;

	//	for (std::vector<Obstacle*>::iterator i = m_obstacles->begin(); i != m_obstacles->end(); i++)
	//	{
	//		Vector2f positionToObstacle = (*i)->m_position - position;

	//		// Projection du vecteur positionToObstacle sur le vecteur direction normalisé (r) et son vecteur orthogonal (s)
	//		double r = positionToObstacle.x * direction.x + positionToObstacle.y * direction.y;
	//		double s = positionToObstacle.x * direction.y - positionToObstacle.y * direction.x;

	//		if (r > 0
	//			&& r - (*i)->m_radius < m_farView * m_steering->getVelocity().length() / m_steering->getMaxSpeed()
	//			&& r + (*i)->m_radius < distance
	//			&& s < (m_radius + (*i)->m_radius)
	//			&& s > -(m_radius + (*i)->m_radius)) {
	//			distance = r - (*i)->m_radius;
	//			fleeDirection = s;
	//		}
	//	}
	//	if (distance == INFINITY)
	//	{
	//		m_steeringForce = ORIGIN2;
	//	}
	//	else
	//	{
	//		direction *= m_steering->getMaxForce();
	//		if (fleeDirection > 0)
	//		{
	//			m_steeringForce = Vector2f(-direction.y, direction.x);
	//		}
	//		else
	//		{
	//			m_steeringForce = Vector2f(direction.y, -direction.x);
	//		}
	//	}
	//	return m_steeringForce;
	//}
	//Vector2f& Separation::Update()
	//{
	//	Vector2f direction;
	//	double distance;
	//	m_steeringForce = ORIGIN2;
	//	for (std::vector<Steering*>::iterator i = m_entities->begin(); i != m_entities->end(); i++)
	//	{
	//		if ((*i) != m_steering)
	//		{
	//			direction = m_steering->getPosition() - (*i)->getPosition();
	//			distance = direction.length();
	//			if (distance <= m_distanceMax && distance != 0.0f)
	//			{
	//				direction.normalize();
	//				m_steeringForce += direction * 1 / distance;
	//			}
	//		}
	//	}
	//	m_steeringForce.normalize();
	//	m_steeringForce *= m_steering->getMaxForce();
	//	return m_steeringForce;
	//}

	//Vector2f& Cohesion::Update()
	//{
	//	Vector2f direction, center = ORIGIN2;
	//	double distance;
	//	int nbNeighbors = 0;
	//	for (std::vector<Steering*>::iterator i = m_entities->begin(); i != m_entities->end(); i++)
	//	{
	//		if ((*i) != m_steering)
	//		{
	//			direction = m_steering->getPosition() - (*i)->getPosition();
	//			distance = direction.length();
	//			if (distance <= m_distanceMax)
	//			{
	//				center += (*i)->getPosition();
	//				nbNeighbors++;
	//			}
	//		}
	//	}
	//	if (nbNeighbors)
	//	{
	//		center /= nbNeighbors;
	//		m_steeringForce = center - m_steering->getPosition();
	//	}

	//	return m_steeringForce;
	//}


	//Vector2f& Alignment::Update()
	//{
	//	Vector2f direction;
	//	double distance;
	//	int nbNeighbors = 0;
	//	m_desiredVelocity = ORIGIN2;
	//	for (std::vector<Steering*>::iterator i = m_entities->begin(); i != m_entities->end(); i++)
	//	{
	//		if ((*i) != m_steering)
	//		{
	//			direction = m_steering->getPosition() - (*i)->getPosition();
	//			distance = direction.length();
	//			if (distance <= m_distanceMax)
	//			{
	//				m_desiredVelocity += (*i)->getVelocity();
	//				nbNeighbors++;
	//			}
	//		}
	//	}
	//	if (nbNeighbors)
	//	{
	//		m_desiredVelocity /= nbNeighbors;
	//		m_steeringForce = m_desiredVelocity - m_steering->getVelocity();
	//	}

	//	return m_steeringForce;
	//}

	//Vector2f& LeadFollowing::Update()
	//{
	//	Vector2f steeringPosition = m_steering->getPosition();
	//	Vector2f steeringToLeader = steeringPosition - m_leader->getPosition();
	//	Vector2f leadDirection = m_leader->getVelocity();
	//	leadDirection.normalize();

	//	float ang = leadDirection.angle(steeringToLeader);
	//	if (ang < m_angle && steeringToLeader.length()<m_distance)
	//	{
	//		// Flee in front of leader
	//		Vector2f frontOfLeader = (m_leader->getPosition() + leadDirection * m_distanceFlee);
	//		m_desiredVelocity = steeringPosition - frontOfLeader;
	//		m_desiredVelocity.normalize();
	//		m_desiredVelocity *= m_steering->getMaxSpeed();
	//		m_steeringForce = m_desiredVelocity - m_steering->getVelocity();

	//	}
	//	else
	//	{
	//		// Arrive behind leader
	//		Vector2f backOfLeader = (m_leader->getPosition() - leadDirection * m_distanceArrive);
	//		double velocitylength = m_steering->getVelocity().length();
	//		double slowingDistance = velocitylength * velocitylength / (m_steering->getMaxForce() / m_steering->getMass());
	//		Vector2f targetOffset = backOfLeader - m_steering->getPosition();
	//		double distance = targetOffset.length();
	//		double rampedSpeed = m_steering->getMaxSpeed() * (distance / slowingDistance);
	//		double clippedSpeed = MathTools::min(rampedSpeed, m_steering->getMaxSpeed());
	//		m_desiredVelocity = targetOffset * (clippedSpeed / distance);
	//		m_steeringForce = m_desiredVelocity - m_steering->getVelocity();
	//		m_steeringForce.normalize();
	//		m_steeringForce *= m_steering->getMaxForce();
	//	}

	//	return m_steeringForce;
	//}

	//Vector2f& Swarming::Update()
	//{
	//	Vector2f velocity = m_steering->getVelocity();
	//	velocity.normalize();
	//	Vector2f velocityTangent(-velocity.y, velocity.x);
	//	Vector2f vsteeringToTarget = m_target->getPosition() - m_steering->getPosition();
	//	if (vsteeringToTarget.LengthSquare() > m_fSwarmDistanceSquare)
	//	{
	//		// Outer zone

	//		// Increase speed to maximum
	//		m_steeringForce = velocity * m_steering->getMaxForce();

	//		float fAngle = vsteeringToTarget.angle(velocity);
	//		if (fAngle < 0.1f)
	//		{
	//			// Vary the steering as a function of the index of the Steering
	//			double dRandTurn = (MathTools::global_counter - m_steering->getIndex()) * 0.01f;
	//			m_steeringForce += velocityTangent * dRandTurn;
	//		}
	//		else
	//		{
	//			if (vsteeringToTarget.isLeft(velocity))
	//			{
	//				m_steeringForce = velocityTangent * -100;
	//			}
	//			else
	//			{
	//				m_steeringForce = velocityTangent * 100;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		// Inner zone

	//		if (vsteeringToTarget.isLeft(velocity))
	//		{
	//			m_steeringForce = velocityTangent * -100;
	//		}
	//		else
	//		{
	//			m_steeringForce = velocityTangent * 100;
	//		}
	//	}
	//	return m_steeringForce;
	//}

	//Vector2f& FormationV::Update()
	//{
	//	Vector2f forward(1.0f, 0.0f);
	//	Vector2f right(0.0f, 1.0f);
	//	if (m_bUseLeaderOrientation)
	//	{
	//		forward = m_leader->getVelocity().Normalized();
	//		right = Vector2f(forward.y, -forward.x);
	//	}

	//	// Add 1 unit per line to have an odd number 
	//	if (m_nbInLine % 2 == 0)
	//	{
	//		m_nbInLine++;
	//	}
	//	// Use minimum between nbInLine and max units
	//	if (m_nbInLine > m_maxId)
	//	{
	//		m_nbInLine = m_maxId;
	//	}

	//	int idRight = (m_id%m_nbInLine) - m_nbInLine / 2;
	//	int idBack = m_id / m_nbInLine;
	//	double fX = idRight * m_distanceMax;
	//	double fY = abs(fX) * (double)tan(m_angle) + idBack * m_distanceMax; // Fleche + recul
	//	Vector2f arrivalOffset = right * fX - forward * fY;
	//	Vector2f arrivalPos = m_leader->getPosition() + arrivalOffset;

	//	//Arrival
	//	Vector2f target_offset = arrivalPos - m_steering->getPosition();
	//	double distance = target_offset.length();
	//	double max_speed = m_steering->getMaxSpeed();
	//	double ramped_speed = max_speed * (distance / m_slowingDistance);
	//	double clipped_speed = (ramped_speed < max_speed) ? ramped_speed : max_speed;
	//	Vector2f desired_velocity = target_offset * (clipped_speed / distance);
	//	m_steeringForce = desired_velocity - m_steering->getVelocity();

	//	return m_steeringForce;
	//}

	//Vector2f& FormationCircle::Update()
	//{
	//	Vector2f forward(1.0f, 0.0f);
	//	Vector2f right(0.0f, 1.0f);
	//	if (m_bUseLeaderOrientation)
	//	{
	//		forward = m_leader->getVelocity().Normalized();
	//		right = Vector2f(forward.y, -forward.x);
	//	}

	//	int idInCircle = m_id%m_nbInCircle;
	//	int iCircle = m_id / m_nbInCircle;
	//	int idMax = (m_maxAngle - m_minAngle) == 360.0f ? m_nbInCircle : m_nbInCircle - 1;
	//	double angle = MathTools::lerp(MathTools::degreetoradian(m_minAngle), MathTools::degreetoradian(m_maxAngle), ((double)(idInCircle) / (double)(idMax)));
	//	double distanceToLeader = m_minRadius + iCircle * m_distanceMax;
	//	double fX = sin(angle) * distanceToLeader;
	//	double fY = cos(angle) * distanceToLeader;
	//	Vector2f arrivalOffset = right * fX + forward * fY;
	//	Vector2f arrivalPos = m_leader->getPosition() + arrivalOffset;

	//	//Arrival
	//	Vector2f target_offset = arrivalPos - m_steering->getPosition();
	//	double distance = target_offset.length();
	//	double max_speed = m_steering->getMaxSpeed();
	//	double ramped_speed = max_speed * (distance / m_slowingDistance);
	//	double clipped_speed = (ramped_speed < max_speed) ? ramped_speed : max_speed;
	//	Vector2f desired_velocity = target_offset * (clipped_speed / distance);
	//	m_steeringForce = desired_velocity - m_steering->getVelocity();

	//	return m_steeringForce;
	//}

	//Vector2f& FormationDynamic::Update()
	//{
	//	Vector2f forward(1.0f, 0.0f);
	//	Vector2f right(0.0f, 1.0f);
	//	if (m_bUseLeaderOrientation)
	//	{
	//		forward = m_leader->getVelocity().Normalized();
	//		right = Vector2f(forward.y, -forward.x);
	//	}

	//	//Move slots
	//	m_angleStart += _dT;

	//	//Circle
	//	int idInCircle = m_id%m_nbInCircle;
	//	int iCircle = m_id / m_nbInCircle;
	//	int idMax = (m_maxAngle - m_minAngle) == 360.0f ? m_nbInCircle : m_nbInCircle - 1;
	//	double angle = m_angleStart + MathTools::lerp(MathTools::degreetoradian(m_minAngle), MathTools::degreetoradian(m_maxAngle), ((double)(idInCircle) / (double)(idMax)));
	//	double distanceToLeader = m_minRadius + iCircle * m_distanceMax;
	//	double fX = sin(angle) * distanceToLeader;
	//	double fY = cos(angle) * distanceToLeader;
	//	Vector2f arrivalOffset = right * fX + forward * fY;
	//	Vector2f arrivalPos = m_leader->getPosition() + arrivalOffset;

	//	//Arrival
	//	Vector2f target_offset = arrivalPos - m_steering->getPosition();
	//	double distance = target_offset.length();
	//	double max_speed = m_steering->getMaxSpeed();
	//	double ramped_speed = max_speed * (distance / m_slowingDistance);
	//	double clipped_speed = (ramped_speed < max_speed) ? ramped_speed : max_speed;
	//	Vector2f desired_velocity = target_offset * (clipped_speed / distance);
	//	m_steeringForce = desired_velocity - m_steering->getVelocity();

	//	return m_steeringForce;
	//}

} // namespace crea
