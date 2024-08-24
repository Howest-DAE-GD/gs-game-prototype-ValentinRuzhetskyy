#pragma once
#include <vector>
#include <utils.h>
#include <iostream>
#include <Texture.h>
#include <string.h>
#include "PowerUps.h"


class Bullet;
class Player
{
public:
	Player(Point2f ScorePosition,Point2f PlayerPosition, Point2f PlutoniumPosition,Point2f HealthPosition);
	~Player();
	void DisplayResources();
	void DisplayPlayer();
	void Update(float elapsedSec);
	void Addcash(int m_cash);
	void SetBulletDirection(Point2f BulletDirection);
	void RemoveCash(int m_cash);
	void AddPlutonium(int plutonium);
	void UpdateHitboxPostion();
	void RayCast(const std::vector< std::vector<Point2f>>& AllVertices);
	void ManageBullets( float xposition,  float yposition,  float width,  float heigth);
	bool IsShot();
	
	bool GetIsDeath();
	Point2f GetBulletPosition();
	Point2f GetPlayerPosition();
	void Collision();
	Rectf	GetBulletHitbox();
	Rectf	GetPlayerHitbox();

	std::vector<Bullet*> GetBulletAmount();
	int getBullets();
	friend void PowerUps::PowerupMagazine(Player& Player);

	friend void PowerUps::PowerupSpeed(Player& Player);
	int GetCash();

	int GetPlutonium();

private:

	enum PlayerDirection
	{
		RightUp,
		RightDown,
		LeftUp,
		LeftDown,
		Right,
		Left,
		Up,
		Down
	};
	PlayerDirection m_PlayerDirection;

	int m_Plutonium;
	int m_Cash;
	int m_Size;
	int m_Speed;
	int m_bulletId;
	int m_Cooldown;

	std::string m_textpath{ "FaqroExtendedItalic-nAL5Y.ttf" };
	std::string AmountOfCash;
	std::string AmountOfPlutonium;
	std::string m_CashWord{"cash"};
	std::string m_PlutoniumWord{"plutonium"};
	std::string m_HealthWord{ "Health" };
	std::string AmountOfHealth;

	Texture* m_PCashDisplay;
	Texture* m_pPlutonium;
	Texture* m_pHealth;
	Point2f m_Scoreposition;
	Point2f m_Plutoniumposition;
	Point2f m_PlayerPosition;
	Point2f m_HealthPostion;

	std::vector<Bullet* >m_pBullet;

	std::string m_xOperator;
	std::string m_yOperator;

	bool m_IsShot;
	bool m_ChangesCash;
	bool m_IsCooldownBetweenBullet;
	bool m_ChangesPlutonium;
	bool m_updateHealth;
	bool m_isDeath{ false };
	bool m_rightBorderCollission;
	bool m_leftBorderCollission;
	bool m_downBorderCollission;
	bool m_upBorderCollission;
	float m_timer;
	float m_seconds;
	float  m_CooldownBetweenShot;
	int m_health{5};
	float m_Width;
	float m_Heigth;
	Rectf m_hitbox;
	utils::HitInfo m_hitInfo;
};


