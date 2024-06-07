#include "pch.h"
#include "Game.h"

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
	Player1 = new Player{ Point2f{20.0f,460.0f}, Point2f{300.0f,200.0f}, Point2f{650.0f,460.0f } };
	for (int i = 0; i < AmountofEnemies.size(); i++)
	{
		AmountofEnemies[i] = new enemies{ 100.0f,10.0f };
		AmountofEnemies[i]->setId(i);
	};
}

void Game::Cleanup( )
{
	for (int i = 0; i < m_Amountworkplaces; i++)
	{
		delete	m_PworkPlaces[i];
		m_PworkPlaces[i] = nullptr;
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
	if (timer<3)
	{
		timer += elapsedSec;
	}
	else if (timer>3)
	{
		
		SpawnEnemies();
		timer = 0;
	}
	Player1->Update(elapsedSec);

	for (int indexEnemies = 0; indexEnemies < AmountofEnemies.size(); indexEnemies++)
	{
		AmountofEnemies[indexEnemies]->Update( elapsedSec);
		AmountofEnemies[indexEnemies]->SetEnemyVertices(m_EnemyVertices);
		AmountofEnemies[indexEnemies]->RayCast(Vertices);
		if (AmountofEnemies[indexEnemies]->GetIsCollidedWithWall()==false)
		{
			AmountofEnemies[indexEnemies]->IsPlayerCloseBy(Player1->GetPlayerPosition());
		}
			AmountofEnemies[indexEnemies]->HitByBullet(Player1->GetBulletAmount());
		
		
		

	}
	for (int index = 0; index < AmountofEnemies.size(); index++)
	{
		if (index=AmountofEnemies.size())
		{
			m_EnemyVertices.clear();
		}
	}
	for (int i = 0; i < 40; i++)
	{
		if (m_PworkPlaces[i]!=nullptr)
		{
			m_PworkPlaces[i]->SetOuterWalls(m_outerwallPosition.x, m_outerwallPosition.y,m_FactoryWidthOuterWall,m_FactoryHeightOuterWall);
			m_PworkPlaces[i]->Update(Vertices);
			if (m_PworkPlaces[i]->IsPlutoniumReady()==true)
			{
				Player1->AddPlutonium(m_PworkPlaces[i]->GetReadyPlutonium());
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
				delete AmountofEnemies[i];
				AmountofEnemies.erase(AmountofEnemies.begin() + i);
				--i;
			}
		}
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
	Player1->DisplayResources();
	Player1->DisplayPlayer();
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

	switch (e.button)
	{
	default:
		break;
	case SDL_BUTTON_LEFT:
		if (Player1->IsShot()==false)
		{
			if (Player1->GetPlayerPosition().x<m_outerwallPosition.x || Player1->GetPlayerPosition().x>m_outerwallPosition.x + m_FactoryWidthOuterWall && Player1->GetPlayerPosition().y<m_outerwallPosition.y || Player1->GetPlayerPosition().y>m_outerwallPosition.y + m_FactoryWidthOuterWall)
			{
				Player1->SetBulletDirection(Point2f{ float(e.x),float(e.y) });
			}
		}

		for (int i = 0; i <Rows*Collumns; i++)
		{
			if (e.x <= m_FactoryGround.left + m_FactoryGround.width && e.x >= m_FactoryGround.left && e.y <= m_FactoryGround.bottom + m_FactoryGround.height && e.y >= m_FactoryGround.bottom&&Player1->GetCash()>=200)
			{
				Player1->RemoveCash(RobotWorkPlace::m_BuildPrice);
				m_PworkPlaces[i]->CreateRobotWorkPlace(m_FactoryGround.left, m_FactoryGround.bottom, m_FactoryGround.width, m_FactoryGround.height, Rows, Collumns, Point2f{ float(e.x), float(e.y) }, m_PworkPlaces);
			}
			/*CheckPlacement(Point2f{float(e.x),float(e.y)}); */
		}
		m_Amountworkplaces += 1;
		std::cout << e.x << " " << (e.y) << std::endl;
		break;
	}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
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
			utils::DrawRect(m_FactoryGround.left + col * cellWidth,
			m_FactoryGround.bottom + rows * cellHeight,
			cellWidth, cellHeight);
		}
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

void Game::SpawnEnemies()
{
	enemies* NewEnemy = new enemies{ 100,10 };
	AmountofEnemies.push_back(NewEnemy);
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
