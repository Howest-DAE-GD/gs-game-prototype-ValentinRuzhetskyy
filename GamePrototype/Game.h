#pragma once
#include "BaseGame.h"
#include <utils.h>
#include <iostream>
#include "enemies.h"
#include <vector>
#include "RobotWorkPlace.h"
#include "Player.h"
#include "PowerUps.h"
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
	void DeleteEnemy(int index);
	void DrawGridView() const ;
	Point2f getRandomPoint2f(float x_min, float x_max, float y_min, float y_max);
	float  getRandomFloat(float lower_bound, float upper_bound);
	void CheckPlacement(const Point2f& pos);
	void SpawnEnemies(float elapsedSec);
	int CreateRandomNumber(  int max);
	void DrawExplosion() const;
private:
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;


	Point2f m_FactoryLocationOuterWall{GetViewPort().width/2,GetViewPort().height/2};
	float	m_FactoryWidthOuterWall{260};
	float	m_FactoryHeightOuterWall{260};
	Point2f m_outerwallPosition{283.0f,110.0f};
	Point2f m_FactoryLocationCamp{ (GetViewPort().width / 2) ,(GetViewPort().height / 2) };
	float	m_FactoryWidthCamp{ 240 };
	float	m_FactorHeightCamp{ 240 };
	Rectf m_FactoryGround { m_FactoryLocationCamp.x - m_FactoryWidthCamp / 2, m_FactoryLocationCamp.y - m_FactorHeightCamp / 2, m_FactoryWidthCamp, m_FactorHeightCamp };
	std::vector<Point2f>VerticesOuterWall
	{
		Point2f{m_outerwallPosition.x,m_outerwallPosition.y},
		Point2f{m_outerwallPosition.x+m_FactoryWidthOuterWall, m_outerwallPosition.y},
		Point2f{m_outerwallPosition.x + m_FactoryWidthOuterWall,m_outerwallPosition.y+m_FactoryHeightOuterWall},
		Point2f{m_outerwallPosition.x,m_outerwallPosition.y + m_FactoryHeightOuterWall},
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
	std::vector<std::vector<Point2f>>VerticesPlayer{
		ScreenBorder
	};
	std::vector<std::vector<Point2f>>m_EnemyVertices;

	const int Rows{ 5 };
	const int Collumns{ 7 };

//	std::vector<RobotWorkPlace*> g_CapacityOfWorkSpaces[40]{};
	RobotWorkPlace*m_PworkPlaces[40]{};
	//std::vector<RobotWorkPlace*> m_PworkPlaces;
	std::vector<enemies*> AmountofEnemies{1};
	//std::vector<Robot*>Robots{};

	enemies* enemy;

	PowerUps* PowerUp;


	int TotalAmountRobots{0};
	int m_Amountworkplaces{0};
	int id = AmountofEnemies.size();

	float timer{ 0 };
	float explossionCounter{ 0 };

	Player* Player1;

	Point2f rectfOffset{ 2,2 };
	Point2f m_rectf1Position{350 ,225};
	Point2f m_rectf2Position{ 350 ,225 };
	Point2f m_rectf3Position{ 350 ,225 };
	Point2f m_rectf4Position{ 350 ,225 };
	Point2f m_rectf5Position{ 350 ,225 };
	Point2f m_rectf6Position{ 350 ,225 };
	Point2f m_rectf7Position{ 350 ,225 };
	Point2f m_rectf8Position{ 350 ,225 };
	Point2f CurrentMousePosition;
	bool m_enemyOutOfRange{ false };
	bool m_isExplosionReady{ false };
	bool m_isPlayerWithinWalls{ false };
};