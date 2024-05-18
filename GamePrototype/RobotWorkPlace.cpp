#include "pch.h"
#include "RobotWorkPlace.h"
#include "Robot.h"

RobotWorkPlace::RobotWorkPlace(Point2f pos) :
	m_Position(pos),
	m_cash{ 200 },
	m_heightFrameProgressBar{ 10.0f },
	m_widthFrameProgressBar{ 20.0f },
	m_heightProgressBar{ 10.0f },
	m_widthProgressBar{ 0.0f },
	m_BuildTimer{ 0 },
	Robots{},
	m_IsCreated{false},
	AmountOfRobots{0}

{
	
}

void RobotWorkPlace::CreateRobotWorkPlace(float left, float bottom, float width, float height, int Rows, int Collumns,const Point2f& pos, RobotWorkPlace* RobotWorkplaces[])
{
	const float cellW{ width / Collumns };
	const float cellH{ height / Rows };

	int col{ int((pos.x - left) / cellW) };
	int row{ int((pos.y - bottom) / cellH) };

	const float x{ left + col * cellW };
	const float  y{ bottom + row * cellH };

	const int index{ row * Collumns + col };

	if (RobotWorkplaces[index] == nullptr)
	{
		RobotWorkPlace* pRoboyWorkPlace{ new RobotWorkPlace(Point2f{x,y}) };
		RobotWorkplaces[index] = pRoboyWorkPlace;
	}
}

void RobotWorkPlace::Update(const std::vector< std::vector<Point2f>>& AllVertices)
{
	if (m_widthProgressBar < m_widthFrameProgressBar && m_cycle == true)
	{
		m_widthProgressBar = m_widthProgressBar + 1.0f;
	}
	else if(m_widthProgressBar>=m_widthFrameProgressBar)
	{
		std::cout << "check" << std::endl;
		m_widthProgressBar = 0;
		Robots.push_back(new Robot{m_Position});
		m_IsCreated = true;
		AmountOfRobots++;
	}
	
	if (m_BuildTimer>20)
	{
		m_cycle = true;
		m_BuildTimer = 0;
	}
	else
	{
		m_BuildTimer++;
		m_cycle = false;
	}
	for (int i{0}; i < AmountOfRobots; i++)
	{
		if (Robots[i]!=nullptr)
		{
			Robots[i]->RayCast(AllVertices);
			Robots[i]->Update();
			
		}
		else if(Robots[i]==nullptr)
		{
			std::cout << "this is a nullptr in update" << std::endl;
		}
		
	}
	//std::cout << m_widthProgressBar << std::endl;
}

void RobotWorkPlace::SetEnemyPosition(Point2f enemyPos)
{
	for (int i{0}; i < AmountOfRobots; i++)
	{
		if (Robots[i]!=nullptr)
		{
			Robots[i]->IsEnemyWithinRange(enemyPos);
		}
		else if(Robots[i] == nullptr)
		{
			std::cout << "this is a nullptr in SetEnemyPosition" << std::endl;
		}
	

	}
}

int RobotWorkPlace::GetAmountOfRobots()
{
	return AmountOfRobots;
}

void RobotWorkPlace::Display()
{
	utils::SetColor(Color4f{ 0.5f,0.5f,0.5f,1.0f });
	utils::FillRect(m_Position.x + 7, m_Position.y + 15, 20, 20);
	utils::SetColor(Color4f{ 0.0f, 1.0f, 1.0f, 1.0f });
	utils::DrawRect(m_Position.x + 7, m_Position.y + 5, m_widthFrameProgressBar, m_heightFrameProgressBar);
	utils::SetColor(Color4f{ 0.0f,1.0f,0.0f,1.0f });
	utils::FillRect(m_Position.x + 7, m_Position.y + 5, m_widthProgressBar, m_heightProgressBar);
	for (int i{0}; i < AmountOfRobots; i++)
	{
		Robots[i]->Draw();
	}

}