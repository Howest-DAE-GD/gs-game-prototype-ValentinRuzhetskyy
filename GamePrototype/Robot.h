#pragma once
#include <iostream>
#include <utils.h>

class Bullet;
class enemies;
class Robot
{
public:
	Robot(Point2f Position);
	~Robot();
	void IsEnemyWithinRange(std::vector<enemies*> AmountofEnemies);
	int GetRobothealth();
	void Draw();
	void Update();
	void RayCast(const std::vector< std::vector<Point2f>>& AllVertices);
	void isWithinCastleWalls(float left, float bottom, float width, float heigth);
	int	GetId();
	void Setid(int id);
	Point2f GetPosition();
protected:
	Point2f m_lastEnemyPosition;
	Point2f m_RobotPosition;
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

	Direction RobotDirection;

	int	  m_RandomDirection;
	int	  m_RobotID;
	int	  m_Robothealth;
	int	  m_Speed{ 5 };
	int   m_counter;
	int	  m_coolDownDamage;
	int	  m_bulletCooldown;
	int	  m_damage;

	float m_Width;
	float m_Height;

	bool  m_isEnemycloseBy;
	bool  m_isCollided;
	bool  m_isWithinWalls;
	bool  m_isAlive;
	bool  m_isEnemyWithinShootingRange;
	bool  m_isBulletShot;
	
	Bullet* m_pBullet;
	
	utils::HitInfo m_hitInfo;
};


