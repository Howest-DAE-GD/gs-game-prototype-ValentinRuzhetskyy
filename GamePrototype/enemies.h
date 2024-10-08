#pragma once
#include <utils.h>
#include<iostream>
#include<vector>

class Bullet;
class enemies
{
public:
	enemies(Point2f position, int health, int cash, int id,float saturation);
	void RayCast(const std::vector< std::vector<Point2f>>& AllVertices);
	void IsPlayerCloseBy(Point2f playerPosition, const bool& isplayerWithinWalls);
	void Update( float elapsedsec);
	void SetPosition(Point2f newPosition);
	void setId(int Id);
	void Display();
	void Sethealth(int health);
	void HitByBullet(std::vector<Bullet*>& Bulletpositions, const int& damage);
	bool GetIsCollidedWithWall();
	int GetCurrency();
	int GetHealth();
	Rectf GetHitbox();
	Point2f GetPosition();

	std::vector<std::vector<Point2f>> SetEnemyVertices(std::vector<std::vector<Point2f>>&enemyVertices);
	~enemies();

private:
	enum class Direction {
		left,
		right, 
		up,
		down,
		LeftUp,
		LeftDown,
		RightUp,
		RightDown
	};
	float	m_Speed;
	float	m_saturation;
	Point2f m_Enemypos;

	int		m_Width{30};
	int		m_Height{30};
	int		m_EnemyId;
	int		m_health;
	int		m_cash;
	int		m_counter;
	int		m_id;
	int		m_RandomDirection;

	utils::HitInfo m_hitInfo;
	
	Direction EnemyDirection;

	bool	  m_IsPlayerCloseBy;
	bool	  m_isCollidedWithWall;
	bool	  m_isCollidedWithCeiling;
	bool	  m_isCollidedWithLeftWall;
	bool	  m_isCollidedWithRightWall;
	bool	  m_isCollidedWithLowerGround;
	bool	  m_isAlive;
	bool	  m_isCollidedWithBullet{ false };
	std::vector<Point2f>m_EnemyVertices{
		Point2f{m_Enemypos.x,m_Enemypos.y},
		Point2f{m_Enemypos.x + m_Width,m_Enemypos.y },
		Point2f{m_Enemypos.x + m_Width,m_Enemypos.y + m_Height},
		Point2f{m_Enemypos.x,m_Enemypos.y + m_Height},
		Point2f{m_Enemypos.x,m_Enemypos.y}

	};

	Rectf m_enemybounds;
};

