#pragma once
#include "BaseGame.h"
#include <utils.h>
#include <iostream>
#include "enemies.h"

#include <vector>

#include "RobotWorkPlace.h"
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;
	void DrawGridView() const ;
	void CheckPlacement(const Point2f& pos);
	int CreateRandomNumber(  int max);


private:
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
	

	Point2f g_FactoryLocationOuterWall{GetViewPort().width/2,GetViewPort().height/2};
	float	g_FactoryWidthOuterWall{300};
	float	g_FactoryHeightOuterWall{300};
	Point2f m_outerwallPosition{273.0f,100.0f};

	Point2f g_FactoryLocationCamp{ (GetViewPort().width / 2) ,(GetViewPort().height / 2) };
	float	g_FactoryWidthCamp{ 240 };
	float	g_FactorHeightCamp{ 240 };
	Rectf g_FactoryGround { g_FactoryLocationCamp.x - g_FactoryWidthCamp / 2, g_FactoryLocationCamp.y - g_FactorHeightCamp / 2, g_FactoryWidthCamp, g_FactorHeightCamp };
	std::vector<Point2f>VerticesOuterWall
	{
		Point2f{m_outerwallPosition.x,m_outerwallPosition.y},
		Point2f{m_outerwallPosition.x+g_FactoryWidthOuterWall, m_outerwallPosition.y},
		Point2f{m_outerwallPosition.x + g_FactoryWidthOuterWall,m_outerwallPosition.y+g_FactoryHeightOuterWall},
		Point2f{m_outerwallPosition.x,m_outerwallPosition.y + g_FactoryHeightOuterWall},
		Point2f{m_outerwallPosition.x,m_outerwallPosition.y}

	};
	std::vector<Point2f>ScreenBorder{
		Point2f{0.0f,0.0f},
		Point2f{GetViewPort().width,0.0f},
		Point2f{GetViewPort().width,GetViewPort().height},
		Point2f{0.0f,GetViewPort().height},
		Point2f{0.0f,0.0f}
	};

	std::vector<std::vector<Point2f>>Vertices{
		VerticesOuterWall,
		ScreenBorder
	};

	const int Rows{ 5 };
	const int Collumns{ 7 };
//	std::vector<RobotWorkPlace*> g_CapacityOfWorkSpaces[40]{};
	RobotWorkPlace*g_PworkPlaces[40]{};
	std::vector<enemies*> AmountofEnemies{10};
	std::vector<Robot*>Robots[10]{};
	enemies* enemy;
	int TotalAmountRobots{0};
	


};