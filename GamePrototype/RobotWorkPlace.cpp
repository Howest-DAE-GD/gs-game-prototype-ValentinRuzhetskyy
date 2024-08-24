#include "pch.h"
#include "RobotWorkPlace.h"

RobotWorkPlace::RobotWorkPlace(Point2f pos) :
	m_Position(pos),
	m_heightFrameProgressBar{ 10.0f },
	m_widthFrameProgressBar{ 20.0f },
	m_heightProgressBar{ 10.0f },
	m_widthProgressBar{ 0.0f },
	m_BuildTimer{ 0 },
	m_IsCreated{false},
	m_Plutonium{0},
	m_plutoniumLimit{5}
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
	m_IsPlutoniumReady = false;

	if (m_widthProgressBar < m_widthFrameProgressBar && m_cycle == true)
	{
		m_widthProgressBar = m_widthProgressBar + 1.0f;

	}
	else if(m_widthProgressBar>=m_widthFrameProgressBar&&m_Plutonium<m_plutoniumLimit)
	{
		m_IsPlutoniumReady = true;
		m_Plutonium += 1;
		m_widthProgressBar = 0;
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
	//for (int i{0}; i < Robots.size(); i++)
	//{
	//	if (Robots[i]!=nullptr)
	//	{
	//		Robots[i]->RayCast(AllVertices);
	//		Robots[i]->Update();
	//		Robots[i]->Setid(i);
	//		if (Robots[i]->GetRobothealth()<=0)
	//		{
	//			std::cout << "Robot" << i << std::endl;
	//			delete Robots[i];
	//			Robots.erase(Robots.begin() + i);
	//			--i;
	//		}
	//	}
	//	else if(Robots[i]==nullptr)
	//	{
	//		std::cout << "this is a nullptr in update" << std::endl;
	//
	//	}
	//}


	//std::cout << m_widthProgressBar << std::endl;
}

void RobotWorkPlace::SetEnemyCollision(std::vector<enemies*> AmountofEnemies)
{
	//for (int i{0}; i < Robots.size(); i++)
	//{
	//	if (Robots[i]!=nullptr)
	//	{
	//		Robots[i]->IsEnemyWithinRange(AmountofEnemies);
	//	}
	//	else if(Robots[i] == nullptr)
	//	{
	//	//	std::cout << "this is a nullptr in SetEnemyPosition" << std::endl;
	//	}
	//

	//}
}

void RobotWorkPlace::SetOuterWalls(float left, float bottom, float width, float height)
{
	//for (int i = 0; i < Robots.size(); i++)
	//{
	//	Robots[i]->isWithinCastleWalls(left, bottom, width, height);
	//}
}

//std::vector< Robot*> RobotWorkPlace::GetAmountOfRobots()
//{
//	return Robots;
//}

RobotWorkPlace::~RobotWorkPlace()
{
	//for (int  i = 0; i < Robots.size(); i++)
	//{
	//	delete[] Robots[i];
	//	Robots[i] = nullptr;
	//}
}

void RobotWorkPlace::Display()
{
	utils::SetColor(Color4f{ 0.5f,0.5f,0.5f,1.0f });
	utils::FillRect(m_Position.x + 7, m_Position.y + 15, 20, 20);
	utils::SetColor(Color4f{ 0.0f, 1.0f, 1.0f, 1.0f });
	utils::DrawRect(m_Position.x + 7, m_Position.y + 5, m_widthFrameProgressBar, m_heightFrameProgressBar);
	utils::SetColor(Color4f{ 0.0f,1.0f,0.0f,1.0f });
	utils::FillRect(m_Position.x + 7, m_Position.y + 5, m_widthProgressBar, m_heightProgressBar);
	//for (int i{0}; i < Robots.size(); i++)
	//{
	//	if (Robots[i]!=nullptr)
	//	{
	//		Robots[i]->Draw();
	//	}
	//}

}

bool RobotWorkPlace::IsPlutoniumReady()
{
	return m_IsPlutoniumReady;
}

int RobotWorkPlace::GetReadyPlutonium()
{
	return 1;
}
