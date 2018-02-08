/***************************************************/
/* Nom:	Behaviour.h
/* Description: Behaviour
/* Auteur: DAMIENS Sébastien
/***************************************************/
#ifndef __Behaviour_H_
#define __Behaviour_H_

#include "AI.h"

namespace crea
{
	class Steering;
	class Obstacle;

	class CREAENGINE_API Behaviour
	{
		public:

	protected:
		Steering* m_steering;
		Vector2f m_desiredVelocity;
		Vector2f m_steeringForce;
		Vector2f m_offset;
	public:
		Behaviour(Steering* _steering);
		void setOffset(Vector2f& _offset) { m_offset = _offset; };
		virtual Vector2f& Update() = 0;
	};


	class CREAENGINE_API Seek : public Behaviour
	{
		Steering* m_target;
	public:
		Seek(Steering* _steering, Steering* _target) : Behaviour(_steering), m_target(_target) { };
		Vector2f& Update();
	};

	class CREAENGINE_API Flee : public Behaviour
	{
		Steering* m_target;
	public:
		Flee(Steering* _steering, Steering* _target) : Behaviour(_steering), m_target(_target) { };
		Vector2f& Update();
	};

	class CREAENGINE_API Pursuit : public Behaviour
	{
		Steering* m_target;
		float m_fTmax;
	public:
		Pursuit(Steering* _steering, Steering* _target, float _fTmax) : Behaviour(_steering), m_target(_target), m_fTmax(_fTmax) { };
		Vector2f& Update();
	};

	class CREAENGINE_API Evasion : public Behaviour
	{
		Steering* m_target;
		float m_fTmax;
	public:
		Evasion(Steering* _steering, Steering* _target, float _fTmax) : Behaviour(_steering), m_target(_target), m_fTmax(_fTmax) { };
		Vector2f& Update();
	};

	class CREAENGINE_API Arrival : public Behaviour
	{
		Steering* m_target;
		float m_fSlowingDistance;
	public:
		Arrival(Steering* _steering, Steering* _target, float _fSlowingDistance) : Behaviour(_steering), m_target(_target), m_fSlowingDistance(_fSlowingDistance) { };
		Vector2f& Update();
	};

	class CREAENGINE_API Wander : public Behaviour
	{
		double m_distance;
		double m_radius;
		double m_littleRadius;
	public:
		Wander(Steering* _steering, double _distance, double _radius, double _littleRadius)
			: Behaviour(_steering), m_distance(_distance), m_radius(_radius), m_littleRadius(_littleRadius) { };
		Vector2f& Update();
	};

	class CREAENGINE_API PathFollowing : public Behaviour
	{
		float m_fC;
		double m_radius;
		double m_farView;
		std::vector<Obstacle*>* m_obstacles;
	public:
		PathFollowing(Steering* _steering, float _fC, double radius, double farView, std::vector<Obstacle*>* obstacles)
			: Behaviour(_steering), m_fC(_fC), m_radius(radius), m_farView(farView), m_obstacles(obstacles) { };
		Vector2f& Update();
	};

	class CREAENGINE_API UnalignedCollisionAvoidance : public Behaviour
	{
		double m_radius;
		std::vector<Steering*>* m_entities;
	public:
		UnalignedCollisionAvoidance(Steering* _steering, double radius, std::vector<Steering*>* entities)
			: Behaviour(_steering), m_radius(radius), m_entities(entities) { };
		Vector2f& Update();
	};

	//class CREAENGINE_API ObstacleAvoidance : public Behaviour
	//{
	//	double m_radius;
	//	double m_farView;
	//	std::vector<Obstacle*>* m_obstacles;
	//public:
	//	ObstacleAvoidance(Steering* _steering, double radius, double farView, std::vector<Obstacle*>* obstacles)
	//		: Behaviour(_steering), m_radius(radius), m_farView(farView), m_obstacles(obstacles) { };
	//	Vector2f& Update();
	//};

	//class CREAENGINE_API Separation : public Behaviour
	//{
	//	double m_distanceMax;
	//	std::vector<Steering*>* m_entities;
	//public:
	//	Separation(Steering* _steering, double distanceMax, std::vector<Steering*>* entities)
	//		: Behaviour(_steering), m_distanceMax(distanceMax), m_entities(entities) { };
	//	Vector2f& Update();
	//};

	//class CREAENGINE_API Cohesion : public Behaviour
	//{
	//	double m_distanceMax;
	//	std::vector<Steering*>* m_entities;
	//public:
	//	Cohesion(Steering* _steering, double distanceMax, std::vector<Steering*>* entities)
	//		: Behaviour(_steering), m_distanceMax(distanceMax), m_entities(entities) { };
	//	Vector2f& Update();
	//};

	//class CREAENGINE_API Alignment : public Behaviour
	//{
	//	double m_distanceMax;
	//	std::vector<Steering*>* m_entities;
	//public:
	//	Alignment(Steering* _steering, double distanceMax, std::vector<Steering*>* entities)
	//		: Behaviour(_steering), m_distanceMax(distanceMax), m_entities(entities) { };
	//	Vector2f& Update();
	//};

	//class CREAENGINE_API LeadFollowing : public Behaviour
	//{
	//	Steering* m_leader;
	//	double m_distance;
	//	double m_angle;
	//	double m_distanceFlee;
	//	double m_distanceArrive;
	//public:
	//	LeadFollowing(Steering* _steering, Steering* _leader, double _distance, double _angle, double _distanceFlee, double _distanceArrive)
	//		: Behaviour(_steering), m_leader(_leader), m_distance(_distance), m_angle(_angle), m_distanceFlee(_distanceFlee), m_distanceArrive(_distanceArrive) { };
	//	Vector2f& Update();
	//};

	//class CREAENGINE_API Swarming : public Behaviour
	//{
	//	Steering* m_target;
	//	float m_fSwarmDistanceSquare;
	//public:
	//	Swarming(Steering* _steering, Steering* _target, float _fSwarmDistance) : Behaviour(_steering), m_target(_target), m_fSwarmDistanceSquare(_fSwarmDistance*_fSwarmDistance) { };
	//	Vector2f& Update();
	//};

	//class CREAENGINE_API FormationV : public Behaviour
	//{
	//	Steering* m_leader;
	//	bool m_bUseLeaderOrientation;
	//	unsigned int m_id, m_maxId, m_nbInLine;
	//	double m_distanceMax, m_slowingDistance;
	//	double m_angle;

	//public:
	//	FormationV(Steering* _steering, Steering* _leader, bool _bUseLeaderOrientation,
	//		unsigned int _nbInLine, unsigned int _id, unsigned int _maxId,
	//		double _distanceMax, double _slowingDistance,
	//		double _angle)
	//		: Behaviour(_steering), m_leader(_leader), m_bUseLeaderOrientation(_bUseLeaderOrientation),
	//		m_nbInLine(_nbInLine), m_id(_id), m_maxId(_maxId),
	//		m_distanceMax(_distanceMax), m_slowingDistance(_slowingDistance),
	//		m_angle(_angle)
	//	{};
	//	Vector2f& Update();
	//};

	//class CREAENGINE_API FormationCircle : public Behaviour
	//{
	//	Steering* m_leader;
	//	bool m_bUseLeaderOrientation;
	//	unsigned int m_id, m_maxId, m_nbInCircle;
	//	double m_distanceMax, m_slowingDistance;
	//	double m_minAngle, m_maxAngle, m_minRadius;

	//public:
	//	FormationCircle(Steering* _steering, Steering* _leader, bool _bUseLeaderOrientation,
	//		unsigned int _nbInCircle, unsigned int _id, unsigned int _maxId,
	//		double _distanceMax, double _slowingDistance,
	//		double _minAngle, double _maxAngle, double _minRadius)
	//		: Behaviour(_steering), m_leader(_leader), m_bUseLeaderOrientation(_bUseLeaderOrientation),
	//		m_nbInCircle(_nbInCircle), m_id(_id), m_maxId(_maxId),
	//		m_distanceMax(_distanceMax), m_slowingDistance(_slowingDistance),
	//		m_minAngle(_minAngle), m_maxAngle(_maxAngle), m_minRadius(_minRadius)
	//	{};
	//	Vector2f& Update();
	//};

	//class CREAENGINE_API FormationDynamic : public Behaviour
	//{
	//	Steering* m_leader;
	//	bool m_bUseLeaderOrientation;
	//	unsigned int m_id, m_maxId, m_nbInCircle;
	//	double m_distanceMax, m_slowingDistance;
	//	double m_minAngle, m_maxAngle, m_minRadius;

	//	double m_angleStart;

	//public:
	//	FormationDynamic(Steering* _steering, Steering* _leader, bool _bUseLeaderOrientation,
	//		unsigned int _nbInCircle, unsigned int _id, unsigned int _maxId,
	//		double _distanceMax, double _slowingDistance,
	//		double _minAngle, double _maxAngle, double _minRadius)
	//		: Behaviour(_steering), m_leader(_leader), m_bUseLeaderOrientation(_bUseLeaderOrientation),
	//		m_nbInCircle(_nbInCircle), m_id(_id), m_maxId(_maxId),
	//		m_distanceMax(_distanceMax), m_slowingDistance(_slowingDistance),
	//		m_minAngle(_minAngle), m_maxAngle(_maxAngle), m_minRadius(_minRadius)
	//	{
	//		m_angleStart = 0.0f;
	//	};
	//	Vector2f& Update();
	//};
} // namespace crea
#endif
