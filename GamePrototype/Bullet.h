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
	void UpdateHitbox();
	void UpdateBulletVelocity(Point2f ShootingVelocity);

	Rectf   GetHitbox();
	Point2f GetPosition();
	bool GetIsTraveling();
protected:
	Point2f m_bulletPosition;

	int m_Damage;
	int m_TravelTime;
	int m_TravelSpeed;
	
	float m_Width;
	float m_height;
	float m_DirectionX;
	float m_DirectionY;
	float m_VectorX;
	float m_VectorY;
	float m_length;

	bool m_IsbulletTravelling;
	Rectf m_Hitbox;
};

