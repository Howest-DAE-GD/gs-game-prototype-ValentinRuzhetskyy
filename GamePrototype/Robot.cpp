#include "pch.h"
#include "Robot.h"
#include "enemies.h"
#include "Bullet.h"

Robot::Robot(Point2f Position) :
	m_RobotPosition(Position),
	m_counter{ 0 },
	m_isEnemycloseBy{ false },
	m_Height{ 20 },
	m_Width{ 20 },
	m_coolDownDamage{ 0 },
	m_Robothealth{ 4 },
	m_isAlive{ true },
	m_lastEnemyPosition{ Point2f{0.0f,0.0f} },
	m_isBulletShot{ false },
	m_bulletCooldown{ 0 },
	m_damage(1)
{
	m_pBullet = new Bullet{ m_RobotPosition };
}

Robot::~Robot()
{
	
}

void Robot::IsEnemyWithinRange(std::vector<enemies*> AmountofEnemies)
{
	
	/*for (int indexEnemies = 0; indexEnemies < AmountofEnemies.size(); indexEnemies++)
	{
		if (abs(AmountofEnemies[indexEnemies]->GetPosition().x - m_RobotPosition.x) < 60.0f)
		{
			if (abs(AmountofEnemies[indexEnemies]->GetPosition().y- m_RobotPosition.y) < 60.0f)
			{
				m_isEnemycloseBy = true;
				if (AmountofEnemies[indexEnemies]->GetPosition().x > m_RobotPosition.x)
				{
					m_RobotPosition.x += 3;
				}
				else if (AmountofEnemies[indexEnemies]->GetPosition().x > m_RobotPosition.x)
				{
					m_RobotPosition.x -= 3;
				}

				if (AmountofEnemies[indexEnemies]->GetPosition().y > m_RobotPosition.y)
				{
					m_RobotPosition.y += 3;
				}
				else if (AmountofEnemies[indexEnemies]->GetPosition().y > m_RobotPosition.y)
				{
					m_RobotPosition.y -= 3;
				}
			}
		}
	*/	
	/*for (int index = 0; index < EnemyVertices.size(); index++)
	{
	
		if (utils::Raycast(EnemyVertices[index], Point2f(m_RobotPosition.x - 8, m_RobotPosition.y), Point2f(m_RobotPosition.x + m_Width / 2, m_RobotPosition.y), m_hitInfo))
		{
			std::cout << "colided" << std::endl;
		}
		if (utils::Raycast(EnemyVertices[index], Point2f(m_RobotPosition.x + m_Width / 2, m_RobotPosition.y), Point2f(m_RobotPosition.x + m_Width + 8, m_RobotPosition.y), m_hitInfo))
		{
			std::cout << "colided" << std::endl;
		}
		if (utils::Raycast(EnemyVertices[index], Point2f(m_RobotPosition.x - 8, m_RobotPosition.y + m_Height), Point2f(m_RobotPosition.x + m_Width / 2, m_RobotPosition.y + m_Height), m_hitInfo))
		{
			std::cout << "colided" << std::endl;
		}
		if (utils::Raycast(EnemyVertices[index], Point2f(m_RobotPosition.x + m_Width / 2, m_RobotPosition.y + m_Height), Point2f(m_RobotPosition.x + m_Width + 8, m_RobotPosition.y + m_Height), m_hitInfo))
		{
			std::cout << "colided" << std::endl;
		}	
		if (utils::Raycast(EnemyVertices[index], Point2f(m_RobotPosition.x, m_RobotPosition.y - 8), Point2f(m_RobotPosition.x, m_RobotPosition.y + m_Height / 2), m_hitInfo))
		{
			std::cout << "colided" << std::endl;
		}
		if (utils::Raycast(EnemyVertices[index], Point2f(m_RobotPosition.x, m_RobotPosition.y + m_Height / 2), Point2f(m_RobotPosition.x, m_RobotPosition.y + m_Height + 8), m_hitInfo))
		{
			std::cout << "colided" << std::endl;
		}
		if (utils::Raycast(EnemyVertices[index], Point2f(m_RobotPosition.x + m_Width, m_RobotPosition.y - 8), Point2f(m_RobotPosition.x + m_Width, m_RobotPosition.y + m_Height / 2), m_hitInfo))
		{
			std::cout << "colided" << std::endl;
		}
		if (utils::Raycast(EnemyVertices[index], Point2f(m_RobotPosition.x + m_Width, m_RobotPosition.y + m_Height / 2), Point2f(m_RobotPosition.x + m_Width, m_RobotPosition.y + m_Height + 8), m_hitInfo))
		{
			std::cout << "colided" << std::endl;
		}
	}*/
	for (int indexEnemy = 0; indexEnemy < AmountofEnemies.size(); indexEnemy++)
	{
		if (AmountofEnemies[indexEnemy] !=nullptr)
		{
			if (abs(AmountofEnemies[indexEnemy]->GetPosition().x - m_RobotPosition.x) <= 40 && abs(AmountofEnemies[indexEnemy]->GetPosition().y - m_RobotPosition.y) <= 40)
			{
				m_isCollided = true;
			}
			else if (abs(AmountofEnemies[indexEnemy]->GetPosition().x - m_RobotPosition.x) >= 40 && abs(AmountofEnemies[indexEnemy]->GetPosition().y - m_RobotPosition.y) >= 40)
			{
				m_isCollided = false;
			}

			if (abs(AmountofEnemies[indexEnemy]->GetPosition().x - m_pBullet->GetPosition().x) <= 1 && abs(AmountofEnemies[indexEnemy]->GetPosition().y - m_pBullet->GetPosition().y <= 1))
			{
				AmountofEnemies[indexEnemy]->Sethealth(m_damage);
			}
		}

	}
	
	/*for (int  indexEnemy = 0; indexEnemy < AmountofEnemies.size(); indexEnemy++)
	{
		if (AmountofEnemies[indexEnemy] !=nullptr)
		{
			if (abs(AmountofEnemies[indexEnemy]->GetPosition().x - m_RobotPosition.x) <= 100 && abs(AmountofEnemies[indexEnemy]->GetPosition().y - m_RobotPosition.y) <= 100)
			{

				m_isEnemyWithinShootingRange = true;
				if (m_isEnemyWithinShootingRange && m_bulletCooldown >= 70)
				{
					m_lastEnemyPosition.x = AmountofEnemies[indexEnemy]->GetPosition().x;
					m_lastEnemyPosition.y = AmountofEnemies[indexEnemy]->GetPosition().y;
					m_bulletCooldown = 0;
				}
			}
			else if (abs(AmountofEnemies[indexEnemy]->GetPosition().x - m_RobotPosition.x) >= 100 && abs(AmountofEnemies[indexEnemy]->GetPosition().y - m_RobotPosition.y) >= 100)
			{
				m_isEnemyWithinShootingRange = false;
			}
			if (m_isEnemyWithinShootingRange && m_lastEnemyPosition.x != 0 && m_lastEnemyPosition.y != 0)
			{
				m_isBulletShot = true;
				m_pBullet->BulletDirection(m_lastEnemyPosition);
			}

			if (m_isEnemyWithinShootingRange == false && m_bulletCooldown >= 70)
			{
				m_isBulletShot = false;
				m_pBullet->SetPosition(m_RobotPosition);
			}
		}


	}*/

}

int Robot::GetRobothealth()
{
	return m_Robothealth;
}

void Robot::Draw()
{
	if (m_isAlive)
	{
		utils::SetColor(Color4f(0.0f, 0.0f, 1.0f, 1.0f));
		utils::FillRect(m_RobotPosition.x, m_RobotPosition.y, m_Width, m_Height);
		if (m_isBulletShot)
		{
			m_pBullet->Display();
		}
	}


}

void Robot::Update()
{
	if (m_bulletCooldown <= 200)
	{
		m_bulletCooldown += 1;
	}

	if (m_coolDownDamage<=70)
	{
		m_coolDownDamage+=1;
	}
	if (m_isEnemycloseBy==false)
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
			RobotDirection = Direction::left;

			break;
		case 1:
			RobotDirection = Direction::right;

			break;
		case 2:
			RobotDirection = Direction::up;

			break;
		case 3:
			RobotDirection = Direction::down;

			break;
		case 4:
			RobotDirection = Direction::LeftUp;

			break;
		case 5:
			RobotDirection = Direction::LeftDown;

			break;
		case 6:
			RobotDirection = Direction::RightUp;

			break;
		case 7:
			RobotDirection = Direction::RightDown;

			break;
		};



		switch (RobotDirection)
		{
		default:
			break;
		case Direction::left:
			m_RobotPosition.x -= m_Speed;
			break;
		case Direction::right:
			m_RobotPosition.x += m_Speed;
			break;
		case Direction::up:
			m_RobotPosition.y += m_Speed;
			break;
		case Direction::down:
			m_RobotPosition.y -= m_Speed;
			break;
		case Direction::LeftUp:
			m_RobotPosition.x -= m_Speed;
			m_RobotPosition.y += m_Speed;
			break;
		case Direction::LeftDown:
			m_RobotPosition.x -= m_Speed;
			m_RobotPosition.y -= m_Speed;
			break;
		case Direction::RightUp:
			m_RobotPosition.x += m_Speed;
			m_RobotPosition.y += m_Speed;
			break;
		case Direction::RightDown:
			m_RobotPosition.x += m_Speed;
			m_RobotPosition.y -= m_Speed;
			break;

		};
	}
	if (m_isCollided&&m_coolDownDamage>=70)
	{
		std::cout << "hit" << std::endl;
		m_Robothealth -= 1;
		m_coolDownDamage = 0;
	}
	if (m_Robothealth<=0)
	{
		m_isAlive = false;
	}
}

void Robot::RayCast(const std::vector< std::vector<Point2f>>& AllVertices)
{
	if (m_isWithinWalls==false)
	{
		for (int index{}; index < AllVertices.size(); ++index)
		{
			if (utils::Raycast(AllVertices[index], Point2f(m_RobotPosition.x - 8, m_RobotPosition.y), Point2f(m_RobotPosition.x + m_Width / 2, m_RobotPosition.y), m_hitInfo))
			{
				//std::cout << "hit1" << std::endl;
				if (RobotDirection == Direction::left || RobotDirection == Direction::LeftUp || RobotDirection == Direction::LeftDown)
				{
					m_Speed = 0;
					//	m_pos.x++;
				}
				else
				{
					m_Speed = 3;
				}


			}
			if (utils::Raycast(AllVertices[index], Point2f(m_RobotPosition.x + m_Width / 2, m_RobotPosition.y), Point2f(m_RobotPosition.x + m_Width + 8, m_RobotPosition.y), m_hitInfo))
			{
				//std::cout << "hit2" << std::endl;
				if (RobotDirection == Direction::right || RobotDirection == Direction::RightDown || RobotDirection == Direction::RightUp)
				{
					//	m_pos.x--;
					m_Speed = 0;
				}
				else
				{
					m_Speed = 3;
				}
			}
			if (utils::Raycast(AllVertices[index], Point2f(m_RobotPosition.x - 8, m_RobotPosition.y + m_Height), Point2f(m_RobotPosition.x + m_Width / 2, m_RobotPosition.y + m_Height), m_hitInfo))
			{
				//std::cout << "hit3" << std::endl;
				if (RobotDirection == Direction::left || RobotDirection == Direction::LeftDown || RobotDirection == Direction::LeftUp)
				{
					m_Speed = 0;
					//	m_pos.x++;
				}
				else
				{
					m_Speed = 3;
				}
			}
			if (utils::Raycast(AllVertices[index], Point2f(m_RobotPosition.x + m_Width / 2, m_RobotPosition.y + m_Height), Point2f(m_RobotPosition.x + m_Width + 8, m_RobotPosition.y + m_Height), m_hitInfo))
			{
				//std::cout << "hit4" << std::endl;
				if (RobotDirection == Direction::right || RobotDirection == Direction::RightUp || RobotDirection == Direction::RightDown)
				{
					//	m_pos.x--;
					m_Speed = 0;
				}
				else
				{
					m_Speed = 3;
				}
			}
			if (utils::Raycast(AllVertices[index], Point2f(m_RobotPosition.x, m_RobotPosition.y - 8), Point2f(m_RobotPosition.x, m_RobotPosition.y + m_Height / 2), m_hitInfo))
			{
				if (RobotDirection == Direction::down || RobotDirection == Direction::LeftDown || RobotDirection == Direction::RightDown)
				{
					//	 m_pos.y++;
					m_Speed = 0;
				}
				else
				{
					m_Speed = 3;
				}
			}
			if (utils::Raycast(AllVertices[index], Point2f(m_RobotPosition.x, m_RobotPosition.y + m_Height / 2), Point2f(m_RobotPosition.x, m_RobotPosition.y + m_Height + 8), m_hitInfo))
			{
				if (RobotDirection == Direction::up || RobotDirection == Direction::LeftUp || RobotDirection == Direction::RightUp)
				{
					// m_pos.y--;
					m_Speed = 0;
				}
				else
				{
					m_Speed = 3;
				}
			}
			if (utils::Raycast(AllVertices[index], Point2f(m_RobotPosition.x + m_Width, m_RobotPosition.y - 8), Point2f(m_RobotPosition.x + m_Width, m_RobotPosition.y + m_Height / 2), m_hitInfo))
			{
				if (RobotDirection == Direction::down || RobotDirection == Direction::LeftDown || RobotDirection == Direction::RightDown)
				{
					//	 m_pos.y++;
					m_Speed = 0;
				}
				else
				{
					m_Speed = 3;
				}
			}
			if (utils::Raycast(AllVertices[index], Point2f(m_RobotPosition.x + m_Width, m_RobotPosition.y + m_Height / 2), Point2f(m_RobotPosition.x + m_Width, m_RobotPosition.y + m_Height + 8), m_hitInfo))
			{
				if (RobotDirection == Direction::up || RobotDirection == Direction::LeftUp || RobotDirection == Direction::RightUp)
				{
					//	 m_pos.y--;
					m_Speed = 0;
				}
				else
				{
					m_Speed = 3;
				}
			}
		}
	}

}

void Robot::isWithinCastleWalls(float left, float bottom, float width, float heigth)
{
	if (this !=nullptr)
	{
		if (m_RobotPosition.x > left && m_RobotPosition.x < left + width&& m_RobotPosition.y > bottom && m_RobotPosition.y < bottom + heigth)
		{
			m_isWithinWalls = true;
		}
		else
		{
			m_isWithinWalls = false;
		}
	}

}

int Robot::GetId()
{
	return m_RobotID;
}


void Robot::Setid(int id)
{
	m_RobotID = id;
}

Point2f Robot::GetPosition()
{
	if (this!=nullptr)
	{
		return m_RobotPosition;
	}

}
