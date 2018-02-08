#ifndef __OBSTACLE_H_
#define __OBSTACLE_H_

#include "Core/Math.h"
namespace crea
{
	class CREAENGINE_API Obstacle
	{
	public:
		Vector2f m_position;
		double m_radius;

		Obstacle(Vector2f position, double radius){ 
			m_position = position;
			m_radius = radius;
		}
	};

 }
#endif
