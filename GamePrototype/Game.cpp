#include "pch.h"
#include "Game.h"
#include <random>

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );

}

void Game::Initialize( )
{
	Player1 = new Player{ Point2f{20.0f,460.0f}, Point2f{300.0f,200.0f}, Point2f{720.0f,460.0f },Point2f{375,460} };
	PowerUp = new PowerUps{  };
	//for (int i = 0; i < AmountofEnemies.size(); i++)
	//{
	//	//AmountofEnemies[i] = new enemies{ getRandomPoint2f(20, 820,20 ,480), ,1,10 };
	//	//AmountofEnemies[i]->setId(i);
	//};
	std::cout << "-Welcome to Nuke Factory. To progress in the game you will need 2 resources cash and plutonium." << std::endl;
	std::cout << "-The objective of the game is to obtain 40 plutonium while staying alive. Once 40 is obtained all enemies will die" << std::endl;
	std::cout << "-Cash is obtained through killing enemies" << std::endl;
	std::cout << "-Plutonium is obtained by creating factories with the obtained cash. It takes 200 cash to make 1 factory" << std::endl;
	std::cout << "-1 factory can make 5 plutonium" << std::endl;
	std::cout << "-These can be placeed on the grid in the middle" << std::endl;
	std::cout << "-When entering the grid you will aslo get the option to get upgrades which makes you stronger" << std::endl;
	std::cout << "-Enemies strength are based on the saturation of the color. The darker the enemy the stronger the enemy." << std::endl;
	std::cout << "-All upgrades cost 5 plutonium" << std::endl;
	std::cout << " " << std::endl;
	std::cout << "Left mousebutton pressed down: shooting" << std::endl;
	std::cout << "Left mouseButton Released: Factory placed/upgrade chosen" << std::endl;
	std::cout << "A: Moving left"<< std::endl;
	std::cout << "D: Moving right"<< std::endl;
	std::cout << "S: Moving Down"<< std::endl;
	std::cout << "W: Moving Up"	<< std::endl;
	
	//std::cout<<""

}

void Game::Cleanup( )
{
	if (m_Amountworkplaces>-1)
	{
		//for (int i = 0; i < m_Amountworkplaces - 1; i++)
		//{
		//	delete[]  m_PworkPlaces[i];
		//	m_PworkPlaces[i] = nullptr;
		//}
	}


	for (int i = 0; i < AmountofEnemies.size(); i++)
	{
		delete AmountofEnemies[i];
		AmountofEnemies[i] = nullptr;
	}
	AmountofEnemies.clear();
}

void Game::Update( float elapsedSec )
{
	//std::cout << timer<<std::endl;
	if (AmountofEnemies.size()<10)
	{
		if (timer < 0.5)
		{
			timer += elapsedSec;
		}
		else if (timer > 0.5)
		{
			SpawnEnemies(elapsedSec);
			timer = 0;
		}
	}
	if (!Player1->GetIsDeath()) {
		
		Player1->Update(elapsedSec);
		Player1->RayCast(VerticesPlayer);
		Player1->ManageBullets(0, 0, 846.f, 500.f, m_outerwallPosition.x, m_outerwallPosition.y, m_FactoryWidthOuterWall, m_FactoryHeightOuterWall);
		Player1->SetBulletDirection(Point2f{ float(CurrentMousePosition.x),float(CurrentMousePosition.y) });
	}

	Player1->UpdateUnits();
	if (!m_isExplosionReady&&!Player1->GetIsDeath())
	{
		for (int indexEnemies = 0; indexEnemies < AmountofEnemies.size(); indexEnemies++)
		{
			if (AmountofEnemies[indexEnemies] != nullptr)
			{
				AmountofEnemies[indexEnemies]->Update(elapsedSec);
				AmountofEnemies[indexEnemies]->SetEnemyVertices(m_EnemyVertices);
				AmountofEnemies[indexEnemies]->RayCast(Vertices);
				if (AmountofEnemies[indexEnemies]->GetIsCollidedWithWall() == false)
				{
					AmountofEnemies[indexEnemies]->IsPlayerCloseBy(Player1->GetPlayerPosition(), m_isPlayerWithinWalls);
				}
				AmountofEnemies[indexEnemies]->HitByBullet(Player1->GetBulletAmount(),Player1->GetBullletDamage());
				if (utils::IsOverlapping(Player1->GetPlayerHitbox(), AmountofEnemies[indexEnemies]->GetHitbox()))
				{
					Player1->Collision();
					DeleteEnemy(indexEnemies);
				}
			}

		}
		for (int index = 0; index < AmountofEnemies.size(); index++)
		{
			if (index = AmountofEnemies.size())
			{
				m_EnemyVertices.clear();
			}
		}
	}
	else
	{
		AmountofEnemies.clear();
		Player1->SetIsShooting(false);
		if (explossionCounter<4)
		{
			explossionCounter += elapsedSec;
		}
	}

	if (!m_isExplosionReady && !Player1->GetIsDeath())
	{
		for (int i = 0; i < 40; i++)
		{
			if (m_PworkPlaces[i] != nullptr)
			{
				if (!m_isPlayerWithinWalls)
				{
					m_PworkPlaces[i]->SetOuterWalls(m_outerwallPosition.x, m_outerwallPosition.y, m_FactoryWidthOuterWall, m_FactoryHeightOuterWall);
					m_PworkPlaces[i]->Update(Vertices);
					if (m_PworkPlaces[i]->IsPlutoniumReady())
					{
						Player1->AddPlutonium(m_PworkPlaces[i]->GetReadyPlutonium());
					}
				}
			}
		}
	}

	for (int i = 0; i < AmountofEnemies.size(); i++)
	{
		if (AmountofEnemies[i] != nullptr)
		{
			if (AmountofEnemies[i]->GetHealth() <= 0)
			{
				Player1->Addcash(AmountofEnemies[i]->GetCurrency());
				DeleteEnemy(i);
			}
		}
	}

	if (Player1->GetPlutonium()>=40)
	{
		m_isExplosionReady = true;
	}
	if (m_isExplosionReady)
	{
		rectfOffset.x += 2;
		rectfOffset.y += 2;
	}
	if (utils::IsPointInRect(Player1->GetPlayerPosition(),m_FactoryGround))
	{
		m_isPlayerWithinWalls = true;
	}
	else
	{
		m_isPlayerWithinWalls = false;
	}

}

void Game::Draw( ) const
{
	ClearBackground();
	utils::SetColor(Color4f{ 0.0f, 0.0f, 0.0f,1.0f });
	utils::FillRect(m_FactoryLocationOuterWall.x - m_FactoryWidthOuterWall / 2, m_FactoryLocationOuterWall.y - m_FactoryHeightOuterWall / 2, m_FactoryWidthOuterWall, m_FactoryHeightOuterWall);

	utils::SetColor(Color4f{ 1.0f,1.0f,1.0f,1.0f });
	utils::FillRect(m_FactoryGround);
	DrawGridView();

	for (int i = 0; i  < Rows*Collumns; ++i )
	{
		if (m_PworkPlaces[i]!=nullptr)
		{
			m_PworkPlaces[i]->Display();
		}
	}
	for (int i = 0; i < AmountofEnemies.size(); i++)
	{
		if (AmountofEnemies[i] != nullptr)
		{
			AmountofEnemies[i]->Display();
			if (AmountofEnemies[i]->GetPosition().x <= 0&&AmountofEnemies[i]->GetPosition().y<=0)
			{
				AmountofEnemies[i]->SetPosition(Point2f{ GetViewPort().width,10.0f});
			}
			else if (AmountofEnemies[i]->GetPosition().x <= 0 && AmountofEnemies[i]->GetPosition().y >= GetViewPort().height)
			{
				AmountofEnemies[i]->SetPosition(Point2f{ GetViewPort().width,GetViewPort().height-10});
			}
			else if (AmountofEnemies[i]->GetPosition().x>=GetViewPort().width&&AmountofEnemies[i]->GetPosition().y <= 0)
			{
				AmountofEnemies[i]->SetPosition(Point2f{ 0,10 });
			}
			else if (AmountofEnemies[i]->GetPosition().x >= GetViewPort().width && AmountofEnemies[i]->GetPosition().y >= GetViewPort().height)
			{
				AmountofEnemies[i]->SetPosition(Point2f{ 0,GetViewPort().height-10});
			}
		}
	}
	if (utils::IsPointInRect(  Player1->GetPlayerPosition(), m_FactoryGround)&&!m_isExplosionReady)
	{
		PowerUp->Draw(Player1->GetPlutonium());
	}
	Player1->DisplayPlayer(m_isExplosionReady,explossionCounter);

	Player1->DisplayResources();
	DrawExplosion();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	CurrentMousePosition.x = e.x;
	CurrentMousePosition.y = e.y;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
//	std::cout << "left click" << std::endl;

		switch (e.button)
		{
		default:
			break;
		case SDL_BUTTON_LEFT:
			if (!Player1->GetIsDeath() && !m_isExplosionReady)
			{
				if (Player1->GetPlayerPosition().x<m_outerwallPosition.x || Player1->GetPlayerPosition().x>m_outerwallPosition.x + m_FactoryWidthOuterWall || Player1->GetPlayerPosition().y<m_outerwallPosition.y || Player1->GetPlayerPosition().y>m_outerwallPosition.y + m_FactoryWidthOuterWall)
				{
					Player1->SetIsShooting(true);
				}
			}
			//	std::cout << e.x << " " << (e.y) << std::endl;
			break;
		}
	

}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
//	std::cout << "mouse released" << std::endl;
	//std::cout << "MOUSEBUTTONUP event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		if (!Player1->GetIsDeath()&&!m_isExplosionReady)
		{
			Player1->SetIsReleased(true);
			for (int i = 0; i < Rows * Collumns; i++)
			{
				if (e.x <= m_FactoryGround.left + m_FactoryGround.width && e.x >= m_FactoryGround.left && e.y <= m_FactoryGround.bottom + m_FactoryGround.height && e.y >= m_FactoryGround.bottom && Player1->GetCash() >= 200)
				{
					//Player1->RemoveCash(RobotWorkPlace::m_BuildPrice);
					m_PworkPlaces[i]->CreateRobotWorkPlace(m_FactoryGround.left, m_FactoryGround.bottom, m_FactoryGround.width, m_FactoryGround.height, Rows, Collumns, Point2f{ float(e.x), float(e.y) }, m_PworkPlaces, Player1);
				}
				/*CheckPlacement(Point2f{float(e.x),float(e.y)}); */
			}
			if (utils::IsPointInRect(Player1->GetPlayerPosition(), m_FactoryGround))
			{
				PowerUp->BulletCooldownSpeedPressed(Point2f{ float(e.x),float(e.y) }, Player1);
				PowerUp->ExtraHealthPressed(Point2f{ float(e.x),float(e.y) }, Player1);
				PowerUp->BulletExtraDamage(Point2f{ float(e.x),float(e.y) }, Player1);
				PowerUp->BulletExtraSpeed(Point2f{ float(e.x),float(e.y) }, Player1);
				PowerUp->SetIsReleased(true);
		
			}
			Player1->SetIsShooting(false);

			m_Amountworkplaces += 1;
		}
		break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	}

}

void Game::DeleteEnemy(int index)
{
	delete AmountofEnemies[index];
	AmountofEnemies.erase(AmountofEnemies.begin() + index);
	--index;
}



void Game::DrawGridView()const
{
	float cellWidth	{ m_FactoryGround.width / Collumns };
	float cellHeight{ m_FactoryGround.height / Rows };
	utils::SetColor(Color4f{ 0.0f,0.0f,0.0f,1.0f });
	for (int rows = 0; rows < Rows; ++rows)
	{
		for (int col = 0; col < Collumns; col++)
		{
			utils::DrawRect(m_FactoryGround.left + col * cellWidth,m_FactoryGround.bottom + rows * cellHeight, cellWidth, cellHeight);
		}
	}
}

Point2f Game::getRandomPoint2f(float x_min, float x_max, float y_min, float y_max)
{
	Point2f point;
	point.x = getRandomFloat(x_min, x_max);
	point.y = getRandomFloat(y_min, y_max);
	do
	{
		point.x = getRandomFloat(x_min, x_max);
		point.y = getRandomFloat(y_min, y_max);
	} while (utils::IsPointInRect(point, Rectf{ m_outerwallPosition.x - 25,m_outerwallPosition.y - 25,m_FactoryWidthOuterWall + 45,m_FactoryHeightOuterWall + 45 }) || utils::IsPointInRect(point, Rectf{ Player1->GetPlayerPosition().x - 40,Player1->GetPlayerPosition().y - 40,80,80 }));
	m_enemyOutOfRange = true;
	if (m_enemyOutOfRange)
	{
		return point;
		m_enemyOutOfRange = false;
	}

}



float Game::getRandomFloat(float lower_bound, float upper_bound)
{
	static std::random_device rd;  // Seed for the random number engine
	static std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_real_distribution<float> dis(lower_bound, upper_bound);
	return dis(gen);
}

void Game::DrawExplosion() const
{ 
	if (m_isExplosionReady)
	{
		utils::SetColor(Color4f{ 0.5f,0.0f, 0.0f, 0.5f });
		utils::FillRect( m_rectf1Position.x -rectfOffset.x, m_rectf1Position.y+rectfOffset.y,100, 100);
		utils::FillRect( m_rectf2Position.x - rectfOffset.x, m_rectf2Position.y - rectfOffset.y,100, 100);
		utils::FillRect( m_rectf3Position.x + rectfOffset.x, m_rectf3Position.y + rectfOffset.y, 100, 100);
		utils::FillRect( m_rectf4Position.x + rectfOffset.x, m_rectf4Position.y - rectfOffset.y, 100, 100);
		utils::SetColor(Color4f{ 0.0f,0.0f, 0.0f, 0.5f });
		utils::FillRect(m_rectf5Position.x - rectfOffset.x, m_rectf5Position.y, 100, 100);
		utils::FillRect(m_rectf6Position.x, m_rectf6Position.y - rectfOffset.y, 100, 100);
		utils::FillRect(m_rectf7Position.x , m_rectf7Position.y + rectfOffset.y, 100, 100);
		utils::FillRect(m_rectf8Position.x + rectfOffset.x, m_rectf8Position.y, 100, 100);
	}
}

void Game::CheckPlacement(const Point2f& pos)
{
	const float cellW{ m_FactoryGround.width / Collumns };
	const float cellH{ m_FactoryGround.height /Rows};

	int col{ int((pos.x - m_FactoryGround.left) / cellW) };
	int row{ int((pos.y - m_FactoryGround.bottom) / cellH) };

	const float x{ m_FactoryGround.left + col * cellW };
	const float  y{ m_FactoryGround.bottom + row * cellH };

	const int index{ row * Collumns + col };

	if (m_PworkPlaces[index] == nullptr)
	{
		RobotWorkPlace* pRoboyWorkPlace{ new RobotWorkPlace(Point2f{x,y}) };
		m_PworkPlaces[index] = pRoboyWorkPlace;

	}

}

void Game::SpawnEnemies(float elapsedSec)
{
	if (Player1->GetPlutonium()<5)
	{
		enemies* NewEnemy = new enemies{ getRandomPoint2f(GetViewPort().left + 20,GetViewPort().width - 30 ,GetViewPort().bottom + 20 , GetViewPort().height - 30),1,10,0,1};
		AmountofEnemies.push_back(NewEnemy);
	}
	else if (Player1->GetPlutonium() >= 5&&  Player1->GetPlutonium()<10)
	{
		enemies* NewEnemy = new enemies{ getRandomPoint2f(GetViewPort().left + 20,GetViewPort().width - 30 ,GetViewPort().bottom + 20 , GetViewPort().height - 30),3,15,1,0.8 };
		AmountofEnemies.push_back(NewEnemy);
	}
	else if (Player1->GetPlutonium()>=10&&Player1->GetPlutonium() < 20)
	{
		enemies* NewEnemy = new enemies{ getRandomPoint2f(GetViewPort().left + 20,GetViewPort().width - 30 ,GetViewPort().bottom + 20 , GetViewPort().height - 30),4,25,2,0.7 };
		AmountofEnemies.push_back(NewEnemy);
	}
	else if ( Player1->GetPlutonium()>=20 && Player1->GetPlutonium() < 30)
	{
		enemies* NewEnemy = new enemies{ getRandomPoint2f(GetViewPort().left + 20,GetViewPort().width - 30 ,GetViewPort().bottom + 20 , GetViewPort().height - 30),5,30,3,0.5 };
		AmountofEnemies.push_back(NewEnemy);
	}
	else if (Player1->GetPlutonium() >= 30 && Player1->GetPlutonium() <= 40)
	{
		enemies* NewEnemy = new enemies{ getRandomPoint2f(GetViewPort().left+ 20,GetViewPort().width- 30 ,GetViewPort().bottom +20 , GetViewPort().height - 30),6,40,4,0.3 };
		AmountofEnemies.push_back(NewEnemy);
	}
}

int Game::CreateRandomNumber( int max)
{
	int RandomNumber;
	RandomNumber = rand() % max;
	return RandomNumber;
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
