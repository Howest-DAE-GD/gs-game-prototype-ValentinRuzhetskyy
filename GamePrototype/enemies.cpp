#include "pch.h"
#include "enemies.h"

enemies::enemies(float pointX,float pointY):
m_pos{pointX,pointY},
counter{ 0 }
{
	m_RandomDirection = 2;
}

void enemies::RayCast(const std::vector<std::vector<Point2f>>& AllVertices)
{
	for (int index{}; index < AllVertices.size(); ++index)
	{
		if (utils::Raycast(AllVertices[index], Point2f(m_pos.x - 8, m_pos.y), Point2f(m_pos.x + m_Width / 2, m_pos.y), m_hitInfo))
		{
			//std::cout << "hit1" << std::endl;
			if (EnemyDirection == Direction::left || EnemyDirection == Direction::LeftUp || EnemyDirection == Direction::LeftDown)
			{
				m_Speed = 0;
			//	m_pos.x++;
			}


		}
		if (utils::Raycast(AllVertices[index], Point2f(m_pos.x + m_Width / 2, m_pos.y), Point2f(m_pos.x + m_Width + 8, m_pos.y), m_hitInfo))
		{
			//std::cout << "hit2" << std::endl;
			if (EnemyDirection == Direction::right || EnemyDirection == Direction::RightDown || EnemyDirection == Direction::RightUp)
			{
			//	m_pos.x--;
				m_Speed = 0;
			}
			else
			{
				m_Speed = 3;
			}
		}
		if (utils::Raycast(AllVertices[index], Point2f(m_pos.x - 8, m_pos.y + m_Height), Point2f(m_pos.x + m_Width / 2, m_pos.y + m_Height), m_hitInfo))
		{
			//std::cout << "hit3" << std::endl;
			if (EnemyDirection == Direction::left || EnemyDirection == Direction::LeftDown || EnemyDirection == Direction::LeftUp)
			{
				m_Speed = 0;
			//	m_pos.x++;
			}
			else
			{
				m_Speed = 3;
			}
		}
		 if (utils::Raycast(AllVertices[index], Point2f(m_pos.x + m_Width / 2, m_pos.y + m_Height), Point2f(m_pos.x + m_Width + 8, m_pos.y + m_Height),m_hitInfo))
		{
			 //std::cout << "hit4" << std::endl;
			if (EnemyDirection==Direction::right||EnemyDirection==Direction::RightUp||EnemyDirection==Direction::RightDown)
			{
			//	m_pos.x--;
				m_Speed = 0;
			}
			else
			{
				m_Speed = 3;
			}
		}
		 if (utils::Raycast(AllVertices[index], Point2f(m_pos.x, m_pos.y - 8), Point2f(m_pos.x, m_pos.y + m_Height / 2),m_hitInfo))
		 {
			 if (EnemyDirection==Direction::down||EnemyDirection==Direction::LeftDown||EnemyDirection==Direction::RightDown)
			 {
			//	 m_pos.y++;
				 m_Speed = 0;
			 }
			 else
			 {
				 m_Speed = 3;
			 }
		 }
		 if (utils::Raycast(AllVertices[index], Point2f(m_pos.x, m_pos.y + m_Height / 2), Point2f(m_pos.x, m_pos.y + m_Height + 8), m_hitInfo))
		 {
			 if (EnemyDirection == Direction::up || EnemyDirection == Direction::LeftUp || EnemyDirection == Direction::RightUp)
			 {
				// m_pos.y--;
				 m_Speed = 0;
			 }
			 else
			 {
				 m_Speed = 3;
			 }
		 }
		 if (utils::Raycast(AllVertices[index], Point2f(m_pos.x + m_Width, m_pos.y - 8), Point2f(m_pos.x + m_Width, m_pos.y + m_Height / 2), m_hitInfo))
		 {
			 if (EnemyDirection == Direction::down || EnemyDirection == Direction::LeftDown || EnemyDirection == Direction::RightDown)
			 {
			//	 m_pos.y++;
				 m_Speed = 0;
			 }
			 else
			 {
				 m_Speed = 3;
			 }
		 }
		 if (utils::Raycast(AllVertices[index], Point2f(m_pos.x + m_Width, m_pos.y + m_Height / 2), Point2f(m_pos.x + m_Width, m_pos.y + m_Height + 8), m_hitInfo))
		 {
			 if (EnemyDirection == Direction::up || EnemyDirection == Direction::LeftUp || EnemyDirection == Direction::RightUp)
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

void enemies::Movement( float elapsedsec)
{

	if (counter>=50)
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
		m_pos.x -= m_Speed;
		break;
	case Direction::right:
		m_pos.x += m_Speed;
		break;
	case Direction::up:
		m_pos.y += m_Speed;
		break;
	case Direction::down:
		m_pos.y -= m_Speed;
		break;
	case Direction::LeftUp:
		m_pos.x -= m_Speed;
		m_pos.y += m_Speed;
		break;
	case Direction::LeftDown:
		m_pos.x -= m_Speed;
		m_pos.y -= m_Speed;
		break;
	case Direction::RightUp:
		m_pos.x += m_Speed;
		m_pos.y += m_Speed;
		break;
	case Direction::RightDown:
		m_pos.x += m_Speed;
		m_pos.y -= m_Speed;
		break;

	};
	

	//std::cout << m_pos.x << std::endl;
	//std::cout<<m_pos.y<<std::endl;

}

Point2f enemies::GetPosition()
{
	return m_pos;
}

void enemies::SetPosition(Point2f newPosition)
{
	m_pos = newPosition;
}

void enemies::setId(int id)
{
	m_EnemyId = id;
}

void enemies::Display()
{
	utils::SetColor(Color4f{ 1.0f,0.0f,0.0f,1.0f });
	utils::DrawRect(m_pos.x,m_pos.y, m_Width, m_Height);
	utils::DrawLine(Point2f(m_pos.x - 4, m_pos.y), Point2f(m_pos.x + m_Width / 2, m_pos.y));
	utils::DrawLine(Point2f(m_pos.x + m_Width / 2, m_pos.y), Point2f(m_pos.x + m_Width + 4, m_pos.y));
	utils::DrawLine(Point2f(m_pos.x - 4, m_pos.y + m_Height), Point2f(m_pos.x + m_Width / 2, m_pos.y + m_Height));
	utils::DrawLine(Point2f(m_pos.x + m_Width / 2, m_pos.y+m_Height), Point2f(m_pos.x + m_Width + 4, m_pos.y + m_Height));
	utils::DrawLine(Point2f(m_pos.x, m_pos.y - 4), Point2f(m_pos.x, m_pos.y + m_Height / 2));
	utils::DrawLine(Point2f(m_pos.x, m_pos.y + m_Height / 2), Point2f(m_pos.x, m_pos.y + m_Height+4));
	utils::DrawLine(Point2f(m_pos.x + m_Width, m_pos.y-4), Point2f(m_pos.x + m_Width, m_pos.y + m_Height / 2));
	utils::DrawLine(Point2f(m_pos.x + m_Width, m_pos.y + m_Height / 2), Point2f(m_pos.x + m_Width, m_pos.y + m_Height+4));



}
