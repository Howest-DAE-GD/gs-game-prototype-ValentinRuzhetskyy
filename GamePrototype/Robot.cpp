#include "pch.h"
#include "Robot.h"

Robot::Robot(Point2f Position) :
	m_RobotPosition(Position),
	counter{ 0 },
	isEnemycloseBy{ false },
	m_Height{20},
	m_Width{20}
{
}

Robot::~Robot()
{
}

void Robot::IsEnemyWithinRange(Point2f enemyPos)
{

	if (abs(enemyPos.x-m_RobotPosition.x)<20.0f)
	{
		if (abs(enemyPos.y-m_RobotPosition.y)<20.0f)
		{
			std::cout << abs(enemyPos.x - m_RobotPosition.x) << std::endl;
			isEnemycloseBy = true;
			if (enemyPos.x>m_RobotPosition.x)
			{
				m_RobotPosition.x++;
			}
			else if (enemyPos.x>m_RobotPosition.x)
			{
				m_RobotPosition.x--;
			}

			if (enemyPos.y > m_RobotPosition.y)
			{
				m_RobotPosition.x++;
			}
			else if (enemyPos.y > m_RobotPosition.y)
			{
				m_RobotPosition.x--;
			}
		}
	}
	else
	{
		isEnemycloseBy = false;
	}

}

void Robot::Draw()
{
	utils::SetColor(Color4f(0.0f, 0.0f, 1.0f, 1.0f));
	utils::FillRect(m_RobotPosition.x, m_RobotPosition.y, m_Width, m_Height);

}

void Robot::Update()
{
	if (isEnemycloseBy==false)
	{
		if (counter >= 50)
		{
			m_RandomDirection = int(rand() % 8);
			counter = 0;
		}
		else
		{
			counter++;
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


}

void Robot::RayCast(const std::vector< std::vector<Point2f>>& AllVertices)
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
