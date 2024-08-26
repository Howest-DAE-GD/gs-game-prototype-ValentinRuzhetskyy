#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(Point2f Position, int travelspeed)
	:m_bulletPosition(Position),
	m_Width(5.0f),
	m_height(5.0f),
	m_TravelTime{0},
	m_TravelSpeed{travelspeed},
	m_IsbulletTravelling{false}
{
	m_Hitbox.width = 5;
	m_Hitbox.height = 5;
}

Bullet::~Bullet()
{
}

void Bullet::Display()
{
	if (this!=nullptr)
	{
		utils::SetColor(Color4f{ 0.0f,1.0f,0.0f,1.0f });
		utils::FillRect(m_bulletPosition.x, m_bulletPosition.y, m_Width, m_height);
	}

}

//void Bullet::BulletDirection(Point2f& EnemylastPosition)
//{
//
//	if (EnemylastPosition.x>m_bulletPosition.x&&EnemylastPosition.y>m_bulletPosition.y)
//	{
//		//std::cout << "passed thru x++" << std::endl;
//		m_bulletPosition.x++;
//		m_bulletPosition.y++;
//	}
//	else if (EnemylastPosition.x < m_bulletPosition.x && EnemylastPosition.y < m_bulletPosition.y)
//	{
//		//std::cout << "passed thru x++" << std::endl;
//		m_bulletPosition.x--;
//		m_bulletPosition.y--;
//	}
//	else if (EnemylastPosition.x > m_bulletPosition.x && EnemylastPosition.y < m_bulletPosition.y)
//	{
//		//std::cout << "passed thru x++" << std::endl;
//		m_bulletPosition.x++;
//		m_bulletPosition.y--;
//	}
//	else if (EnemylastPosition.x < m_bulletPosition.x && EnemylastPosition.y > m_bulletPosition.y)
//	{
//		//std::cout << "passed thru x++" << std::endl;
//		m_bulletPosition.x--;
//		m_bulletPosition.y++;
//	}
//	else if (EnemylastPosition.y > m_bulletPosition.y)
//	{
//		//std::cout << "passed thru y++" << std::endl;
//		m_bulletPosition.y++;
//	}
//	else if (EnemylastPosition.y < m_bulletPosition.y)
//	{
//		//std::cout << "passed thru y--" << std::endl;
//		m_bulletPosition.y--;
//	}	if (EnemylastPosition.x > m_bulletPosition.x)
//	{
//		//std::cout << "passed thru y++" << std::endl;
//		m_bulletPosition.x++;
//	}
//	else if (EnemylastPosition.x < m_bulletPosition.x)
//	{
//		//std::cout << "passed thru y--" << std::endl;
//		m_bulletPosition.x--;
//	}
//	
//
//}


void Bullet::SetPosition(Point2f& PlayerPosition)
{
	if (this!=nullptr)
	{
		m_bulletPosition = PlayerPosition;
	}

}

void Bullet::Update()
{
	if (this!=nullptr)
	{
		if (m_IsbulletTravelling)
		{

			m_length = sqrt(m_DirectionX * m_DirectionX + m_DirectionY * m_DirectionY);
			if (m_length != 0) {
				m_DirectionX /= m_length;
				m_DirectionY /= m_length;
			}

			m_VectorX = m_DirectionX * m_TravelSpeed;
			m_VectorY = m_DirectionY * m_TravelSpeed;

			m_bulletPosition.x += m_VectorX;
			m_bulletPosition.y += m_VectorY;
			UpdateHitbox();
		}
	}
	//std::cout << m_bulletPosition.x << "/" << m_bulletPosition.y<<std::endl;


}

void Bullet::UpdateHitbox()
{
	m_Hitbox.left	= m_bulletPosition.x;
	m_Hitbox.bottom = m_bulletPosition.y;
}


void Bullet::UpdateBulletVelocity(Point2f ShootingVelocity)
{
	if (this!=nullptr)
	{
		m_DirectionX = ShootingVelocity.x - m_bulletPosition.x;
		m_DirectionY = ShootingVelocity.y - m_bulletPosition.y;
		//if		(xOperator == "+")		m_bulletPosition.x += m_TravelSpeed;
		//else if (xOperator == "-")		m_bulletPosition.x -= m_TravelSpeed;
		//
		//if (yOperator == "+")			m_bulletPosition.y += m_TravelSpeed;
		//else if (yOperator == "-")		m_bulletPosition.y -= m_TravelSpeed;
		//std::cout << "passed thru here" << std::endl;

		m_IsbulletTravelling = true;
	}

}



Rectf Bullet::GetHitbox()
{
	return m_Hitbox;
}

Point2f Bullet::GetPosition()
{
	if (this!=nullptr)
	{
		return m_bulletPosition;
	}

}

bool Bullet::GetIsTraveling()
{
	return m_IsbulletTravelling;
}
