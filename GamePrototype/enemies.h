#pragma once
#include <utils.h>
#include<iostream>
#include<vector>

class Bullet;
class enemies
{
public:
	enemies(float posX, float posY);
	void RayCast(const std::vector< std::vector<Point2f>>& AllVertices);
	void IsPlayerCloseBy(Point2f playerPosition);
	void Update( float elapsedsec);
	void SetPosition(Point2f newPosition);
	void setId(int Id);
	void Display();
	void Sethealth(int health);
	void HitByBullet(std::vector<Bullet*> Bulletpositions);
	bool GetIsCollidedWithWall();
	int GetCurrency();
	int GetHealth();

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

	Point2f m_Enemypos;
	int		m_Width{10};
	int		m_Height{10};
	float	m_Speed{ 3.25 };
	int		m_EnemyId;
	int		m_health;
	int		m_cash;
	int		m_counter;
	utils::HitInfo m_hitInfo;
	
	int		  m_RandomDirection;
	Direction EnemyDirection;
	bool	  m_IsPlayerCloseBy;
	bool	  m_isCollidedWithWall;
	bool	  m_isAlive;

	std::vector<Point2f>m_EnemyVertices{
		Point2f{m_Enemypos.x,m_Enemypos.y},
		Point2f{m_Enemypos.x + m_Width,m_Enemypos.y },
		Point2f{m_Enemypos.x + m_Width,m_Enemypos.y + m_Height},
		Point2f{m_Enemypos.x,m_Enemypos.y + m_Height},
		Point2f{m_Enemypos.x,m_Enemypos.y}

	};

	Rectf m_enemybounds;
};

