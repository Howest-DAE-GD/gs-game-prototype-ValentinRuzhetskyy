#include "pch.h"
#include "enemies.h"
#include "Robot.h"
#include "Bullet.h"
enemies::enemies(Point2f Position):
m_Enemypos{ Position },
m_counter{ 0 },
m_IsPlayerCloseBy{false},
m_isCollidedWithWall{false},
m_health{1},
m_isAlive{true},
m_cash{10}

{
	m_RandomDirection = 2;

	m_enemybounds.width = m_Width+10;
	m_enemybounds.height = m_Height+10;
}

void enemies::RayCast(const std::vector<std::vector<Point2f>>& AllVertices)
{
	//std::cout << m_isCollidedWithWall << std::endl
		for (int index{}; index < AllVertices.size(); ++index)
		{
			if (utils::Raycast(AllVertices[index], Point2f(m_Enemypos.x - 8, m_Enemypos.y), Point2f(m_Enemypos.x + m_Width / 2, m_Enemypos.y), m_hitInfo))
			{
				//std::cout << "hit1" << std::endl;
				if (EnemyDirection == Direction::left || EnemyDirection == Direction::LeftUp || EnemyDirection == Direction::LeftDown)
				{
					m_isCollidedWithWall = true;
					m_Speed = 0;
				/*m_Enemypos.x++;*/
				}
				else
				{
					m_isCollidedWithWall = false;
					m_Speed = 3.25;
				}
			}
			if (utils::Raycast(AllVertices[index], Point2f(m_Enemypos.x + m_Width / 2, m_Enemypos.y), Point2f(m_Enemypos.x + m_Width + 8, m_Enemypos.y), m_hitInfo))
			{
				//std::cout << "hit2" << std::endl;
				if (EnemyDirection == Direction::right || EnemyDirection == Direction::RightDown || EnemyDirection == Direction::RightUp)
				{
					m_Speed = 0;
					m_isCollidedWithWall = true;
					/*m_Enemypos.x--;*/
				}
				else
				{
					m_isCollidedWithWall = false;
					m_Speed = 3.25;
				}
			}
			if (utils::Raycast(AllVertices[index], Point2f(m_Enemypos.x - 8, m_Enemypos.y + m_Height), Point2f(m_Enemypos.x + m_Width / 2, m_Enemypos.y + m_Height), m_hitInfo))
			{
				//std::cout << "hit3" << std::endl;
				if (EnemyDirection == Direction::left || EnemyDirection == Direction::LeftDown || EnemyDirection == Direction::LeftUp)
				{
					m_Speed = 0;
					m_isCollidedWithWall = true;
					/*m_Enemypos.x++;*/
				}
				else
				{
					m_isCollidedWithWall = false;
					m_Speed = 3.25;
				}
			}
			if (utils::Raycast(AllVertices[index], Point2f(m_Enemypos.x + m_Width / 2, m_Enemypos.y + m_Height), Point2f(m_Enemypos.x + m_Width + 8, m_Enemypos.y + m_Height), m_hitInfo))
			{
				//std::cout << "hit4" << std::endl;
				if (EnemyDirection == Direction::right || EnemyDirection == Direction::RightUp || EnemyDirection == Direction::RightDown)
				{
					/*m_Enemypos.x--;*/
					m_Speed = 0;
					m_isCollidedWithWall = true;
				}
				else
				{
					m_isCollidedWithWall = false;
					m_Speed = 3.25;
				}
			}
			if (utils::Raycast(AllVertices[index], Point2f(m_Enemypos.x, m_Enemypos.y - 8), Point2f(m_Enemypos.x, m_Enemypos.y + m_Height / 2), m_hitInfo))
			{
				if (EnemyDirection == Direction::down || EnemyDirection == Direction::LeftDown || EnemyDirection == Direction::RightDown)
				{
					/*m_Enemypos.y++;*/
					m_Speed = 0;
					m_isCollidedWithWall = true;
				}
				else
				{
					m_isCollidedWithWall = false;
					m_Speed = 3.25;
				}
			}
			if (utils::Raycast(AllVertices[index], Point2f(m_Enemypos.x, m_Enemypos.y + m_Height / 2), Point2f(m_Enemypos.x, m_Enemypos.y + m_Height + 8), m_hitInfo))
			{
				if (EnemyDirection == Direction::up || EnemyDirection == Direction::LeftUp || EnemyDirection == Direction::RightUp)
				{
					/*m_Enemypos.y--;*/
					m_Speed = 0;
					m_isCollidedWithWall = true;
				}
				else
				{
					m_isCollidedWithWall = false;
					m_Speed = 3.25;
				}
			}
			if (utils::Raycast(AllVertices[index], Point2f(m_Enemypos.x + m_Width, m_Enemypos.y - 8), Point2f(m_Enemypos.x + m_Width, m_Enemypos.y + m_Height / 2), m_hitInfo))
			{
				if (EnemyDirection == Direction::down || EnemyDirection == Direction::LeftDown || EnemyDirection == Direction::RightDown)
				{
					/*m_Enemypos.y++;*/
					m_Speed = 0;
					m_isCollidedWithWall = true;
				}
				else
				{
					m_isCollidedWithWall = false;
					m_Speed = 3.25;
				}
			}
			if (utils::Raycast(AllVertices[index], Point2f(m_Enemypos.x + m_Width, m_Enemypos.y + m_Height / 2), Point2f(m_Enemypos.x + m_Width, m_Enemypos.y + m_Height + 8), m_hitInfo))
			{
				if (EnemyDirection == Direction::up || EnemyDirection == Direction::LeftUp || EnemyDirection == Direction::RightUp)
				{
					/*m_Enemypos.y--;*/
					m_Speed = 0;
					m_isCollidedWithWall = true;
				}
				else
				{
					m_isCollidedWithWall = false;
					m_Speed = 3.25;
				}
			}
		}

	
}

void enemies::IsPlayerCloseBy(Point2f PlayerPosition)
{
	if (this !=nullptr){

	//	
	//		if (Robots[indexRobots] != nullptr)
	//		{
	//			if (abs(Robots[indexRobots]->GetPosition().x - m_Enemypos.x) < 100.0f && abs(Robots[indexRobots]->GetPosition().y - m_Enemypos.y) < 100.0f)
	//			{
	//				//std::cout << "passing thru here" << std::endl;
	//				m_IsRobotCloseBy = true;
	//				if (Robots[indexRobots]->GetPosition().x > m_Enemypos.x)
	//				{
	//					m_Enemypos.x += m_Speed;
	//				}
	//				else if (Robots[indexRobots]->GetPosition().x < m_Enemypos.x)
	//				{
	//					m_Enemypos.x -= m_Speed;
	//				}

	//				if (Robots[indexRobots]->GetPosition().y > m_Enemypos.y)
	//				{
	//					m_Enemypos.y += m_Speed;
	//				}
	//				else if (Robots[indexRobots]->GetPosition().y < m_Enemypos.y)
	//				{
	//					m_Enemypos.y -= m_Speed;
	//				}
	//			}
	//		}
		if (abs(PlayerPosition.x-m_Enemypos.x)<100.0f&& abs(PlayerPosition.y-m_Enemypos.y)<100.0f)
		{
			m_IsPlayerCloseBy = true;
			if		(PlayerPosition.x > m_Enemypos.x)	m_Enemypos.x += m_Speed;
			else if (PlayerPosition.x < m_Enemypos.x)	m_Enemypos.x -= m_Speed;

			if (PlayerPosition.y > m_Enemypos.y)		m_Enemypos.y += m_Speed;
			else if (PlayerPosition.y < m_Enemypos.y)	m_Enemypos.y -= m_Speed;
		}

	}
}

void enemies::Update( float elapsedsec)
{
	m_enemybounds.left = m_Enemypos.x;
	m_enemybounds.bottom = m_Enemypos.y;
//	std::cout << m_enemybounds.left << "/" << m_enemybounds.bottom << std::endl;
	if (this !=nullptr)
	{


		if (m_IsPlayerCloseBy == false)
		{
			if (m_counter >= 50)
			{
				m_RandomDirection = int(rand() % 8);
				m_counter = 0;
			}
			else
			{
				m_counter++;
			}

			switch (m_RandomDirection)
			{
			default:
				break;
			case 0:
				EnemyDirection = Direction::left;

				break;
			case 1:
				EnemyDirection = Direction::right;

				break;
			case 2:
				EnemyDirection = Direction::up;

				break;
			case 3:
				EnemyDirection = Direction::down;

				break;
			case 4:
				EnemyDirection = Direction::LeftUp;

				break;
			case 5:
				EnemyDirection = Direction::LeftDown;

				break;
			case 6:
				EnemyDirection = Direction::RightUp;

				break;
			case 7:
				EnemyDirection = Direction::RightDown;

				break;
			};

			switch (EnemyDirection)
			{
			default:
				break;
			case Direction::left:
				m_Enemypos.x -= m_Speed;
				break;
			case Direction::right:
				m_Enemypos.x += m_Speed;
				break;
			case Direction::up:
				m_Enemypos.y += m_Speed;
				break;
			case Direction::down:
				m_Enemypos.y -= m_Speed;
				break;
			case Direction::LeftUp:
				m_Enemypos.x -= m_Speed;
				m_Enemypos.y += m_Speed;
				break;
			case Direction::LeftDown:
				m_Enemypos.x -= m_Speed;
				m_Enemypos.y -= m_Speed;
				break;
			case Direction::RightUp:
				m_Enemypos.x += m_Speed;
				m_Enemypos.y += m_Speed;
				break;
			case Direction::RightDown:
				m_Enemypos.x += m_Speed;
				m_Enemypos.y -= m_Speed;
				break;
			};
		}
	}
}

int enemies::GetHealth()
{
	if (this!=nullptr)
	{
		return m_health;
	}

}

Rectf enemies::GetHitbox()
{
	return m_enemybounds;
}

Point2f enemies::GetPosition()
{
	if (this!=nullptr)
	{
		return m_Enemypos;
	}

}

void enemies::SetPosition(Point2f newPosition)
{
	if (this!=nullptr)
	{
		m_Enemypos = newPosition;
	}

}

void enemies::setId(int id)
{
	if (this!=nullptr)
	{
		m_EnemyId = id;
	}

}

void enemies::Display()
{
	if (this != nullptr)
	{
		utils::SetColor(Color4f{ 1.0f,0.0f,0.0f,1.0f });
		utils::DrawRect(m_Enemypos.x, m_Enemypos.y, m_Width, m_Height);
		utils::DrawLine(Point2f(m_Enemypos.x - 4, m_Enemypos.y), Point2f(m_Enemypos.x + m_Width / 2, m_Enemypos.y));
		utils::DrawLine(Point2f(m_Enemypos.x + m_Width / 2, m_Enemypos.y), Point2f(m_Enemypos.x + m_Width + 4, m_Enemypos.y));
		utils::DrawLine(Point2f(m_Enemypos.x - 4, m_Enemypos.y + m_Height), Point2f(m_Enemypos.x + m_Width / 2, m_Enemypos.y + m_Height));
		utils::DrawLine(Point2f(m_Enemypos.x + m_Width / 2, m_Enemypos.y + m_Height), Point2f(m_Enemypos.x + m_Width + 4, m_Enemypos.y + m_Height));
		utils::DrawLine(Point2f(m_Enemypos.x, m_Enemypos.y - 4), Point2f(m_Enemypos.x, m_Enemypos.y + m_Height / 2));
		utils::DrawLine(Point2f(m_Enemypos.x, m_Enemypos.y + m_Height / 2), Point2f(m_Enemypos.x, m_Enemypos.y + m_Height + 4));
		utils::DrawLine(Point2f(m_Enemypos.x + m_Width, m_Enemypos.y - 4), Point2f(m_Enemypos.x + m_Width, m_Enemypos.y + m_Height / 2));
		utils::DrawLine(Point2f(m_Enemypos.x + m_Width, m_Enemypos.y + m_Height / 2), Point2f(m_Enemypos.x + m_Width, m_Enemypos.y + m_Height + 4));
	}
}

void enemies::Sethealth(int health)
{
	if (this!=nullptr)
	{
		if (m_health < 1)
		{
			std::cout << "death" << std::endl;
			m_isAlive = false;
		}
	}


}

void enemies::HitByBullet(std::vector<Bullet*> Bulletpositions)
{
	for (int i = 0; i < Bulletpositions.size(); i++)
	{
		if (utils::IsOverlapping(Bulletpositions[i]->GetHitbox(), m_enemybounds) )
		{
			m_health -= 1;
		}
	}

}

bool enemies::GetIsCollidedWithWall()
{
	if (this!=nullptr)
	{
		return m_isCollidedWithWall;
	}

}

int enemies::GetCurrency()
{
	return m_cash;
}

std::vector<std::vector<Point2f>> enemies::SetEnemyVertices(std::vector<std::vector<Point2f>>& enemyVertices)
{
	if (this!=nullptr)
	{
		enemyVertices.push_back(m_EnemyVertices);
		return enemyVertices;
	}
	/* std::cout << m_EnemyId << std::endl;
	std::cout << m_Enemypos.x << std::endl;
	std::cout << m_Enemypos.y<< std::endl;
	std::cout << m_Width <<std::endl;
	std::cout << m_Height << std::endl;*/

}

enemies::~enemies()
{

}
