#pragma once
#include <utils.h>
#include <iostream>

class Bullet
{
public:
	Bullet(Point2f Position);
	~Bullet();
	void Display();
	void SetPosition(Point2f& RobotPosition);
	void Update();
	void UpdateBulletVelocity(Point2f ShootingVelocity);

	Point2f GetPosition();
	
protected:
	Point2f m_bulletPosition;

	int m_Damage;
	int m_TravelTime;
	int m_TravelSpeed;
	
	float m_width;
	float m_height;
	float m_DirectionX;
	float m_DirectionY;
	float m_VectorX;
	float m_VectorY;
	float m_length;

	bool m_IsbulletTravelling;

};

