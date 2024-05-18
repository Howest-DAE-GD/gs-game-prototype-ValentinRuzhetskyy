#pragma once
#include <iostream>
#include <utils.h>
class Robot
{
public:
	Robot(Point2f Position);
	~Robot();
	void IsEnemyWithinRange(Point2f enemyPos);
	void Draw();
	void Update();
	void RayCast(const std::vector< std::vector<Point2f>>& AllVertices);


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

	int m_Robothealth;
	Point2f m_RobotPosition;
	int		m_Speed{ 5 };
	int m_RandomDirection;
	Direction RobotDirection;
	utils::HitInfo m_hitInfo;
	int counter;
	bool isEnemycloseBy;
	float m_Width;
	float m_Height;
	
};


