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
	for (int i = 0; i < 10; i++)
	{
		AmountofEnemies[i] = new enemies{ 100.0f,10.0f };
		AmountofEnemies[i]->setId(i);
	};
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}

	for (int indexEnemies = 0; indexEnemies < AmountofEnemies.size(); indexEnemies++)
	{
		AmountofEnemies[indexEnemies]->Movement( elapsedSec);
		AmountofEnemies[indexEnemies]->RayCast(Vertices);
		for (int indexWorkplace = 0; indexWorkplace <40 ; indexWorkplace++)
		{
			if (g_PworkPlaces[indexWorkplace] != nullptr)
			{
				g_PworkPlaces[indexWorkplace]->SetEnemyPosition(AmountofEnemies[indexEnemies]->GetPosition());
			}
			else if (g_PworkPlaces[indexWorkplace] != nullptr)
			{
				std::cout << "nullptr" << std::endl;
			}
		}
	}
	for (int i = 0; i < 40; i++)
	{
		if (g_PworkPlaces[i]!=nullptr)
		{
			g_PworkPlaces[i]->Update(Vertices);
		}
	}

}

void Game::Draw( ) const
{
	ClearBackground();
	utils::SetColor(Color4f{ 0.0f, 0.0f, 0.0f,1.0f });
	utils::FillRect(g_FactoryLocationOuterWall.x - g_FactoryWidthOuterWall / 2, g_FactoryLocationOuterWall.y - g_FactoryHeightOuterWall / 2, g_FactoryWidthOuterWall, g_FactoryHeightOuterWall);

	utils::SetColor(Color4f{ 1.0f,1.0f,1.0f,1.0f });
	utils::FillRect(g_FactoryGround);
	DrawGridView();

	for (int i = 0; i  < Rows*Collumns; ++i )
	{
		if (g_PworkPlaces[i]!=nullptr)
		{
			g_PworkPlaces[i]->Display();
		}
	}
	for (int i = 0; i < 10; i++)
	{
		AmountofEnemies[i]->Display();
		if (AmountofEnemies[i]->GetPosition().x <= 0 || AmountofEnemies[i]->GetPosition().x >= GetViewPort().width || AmountofEnemies[i]->GetPosition().y <= 0 || AmountofEnemies[i]->GetPosition().y >= GetViewPort().height)
		{
			AmountofEnemies[i]->SetPosition(Point2f{ 20.0f,40.0f });
		}
	}
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
		for (int i = 0; i < 40; i++)
		{
			g_PworkPlaces[i]->CreateRobotWorkPlace(g_FactoryGround.left, g_FactoryGround.bottom, g_FactoryGround.width, g_FactoryGround.height,Rows, Collumns,Point2f{float(e.x), float(e.y)},g_PworkPlaces);
			/*CheckPlacement(Point2f{float( e.x),float(e.y) });*/
		}
		
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
	float cellWidth	{ g_FactoryGround.width / Collumns };
	float cellHeight{ g_FactoryGround.height / Rows };
	utils::SetColor(Color4f{ 0.0f,0.0f,0.0f,1.0f });
	for (int rows = 0; rows < Rows; ++rows)
	{
		for (int col = 0; col < Collumns; col++)
		{
			utils::DrawRect(g_FactoryGround.left + col * cellWidth,
			g_FactoryGround.bottom + rows * cellHeight,
			cellWidth, cellHeight);
		}
	}
}

void Game::CheckPlacement(const Point2f& pos)
{
	const float cellW{ g_FactoryGround.width / Collumns };
	const float cellH{ g_FactoryGround.height /Rows};

	int col{ int((pos.x - g_FactoryGround.left) / cellW) };
	int row{ int((pos.y - g_FactoryGround.bottom) / cellH) };

	const float x{ g_FactoryGround.left + col * cellW };
	const float  y{ g_FactoryGround.bottom + row * cellH };

	const int index{ row * Collumns + col };

	if (g_PworkPlaces[index]==nullptr)
	{
		RobotWorkPlace* pRoboyWorkPlace{ new RobotWorkPlace(Point2f{x,y}) };
		g_PworkPlaces[index] = pRoboyWorkPlace;
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
