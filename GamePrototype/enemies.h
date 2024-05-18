#pragma once
#include <utils.h>
#include<iostream>

class enemies
{
public:
	enemies(float posX, float posY);
	void RayCast(const std::vector< std::vector<Point2f>>& AllVertices);
	void Movement( float elapsedsec);
	Point2f GetPosition();
	void SetPosition(Point2f newPosition);
	void setId(int Id);
	void Display();
	~enemies();

private:
	enum class Direction {
		left,
		right, 
		up,
		down,
		LeftUp,
		LeftDown,
		RightUp,
		RightDown
	};

	Point2f m_pos;
	int		m_Width{10};
	int		m_Height{10};
	int		counter;
	int		m_EnemyId;
	int		m_Speed{5};
	utils::HitInfo m_hitInfo;
	int m_RandomDirection;
	Direction EnemyDirection;
};

