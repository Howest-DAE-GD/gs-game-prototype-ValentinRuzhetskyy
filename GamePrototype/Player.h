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
	Player(Point2f ScorePosition,Point2f PlayerPosition, Point2f PlutoniumPosition);
	~Player();
	void DisplayResources();
	void DisplayPlayer();
	void Update(float elapsedSec);
	void Addcash(int m_cash);
	void SetBulletDirection(Point2f BulletDirection);
	void RemoveCash(int m_cash);
	void AddPlutonium(int plutonium);
	bool IsShot();
	Point2f GetBulletPosition();
	Point2f GetPlayerPosition();
	std::vector<Bullet*> GetBulletAmount();
	friend void PowerUps::PowerupMagazine(Player& Player);
	friend void PowerUps::PowerupSpeed(Player& Player);
	int GetCash();

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

	Texture* m_PCashDisplay;
	Texture* m_pPlutonium;
	Point2f m_Scoreposition;
	Point2f m_Plutoniumposition;
	Point2f m_PlayerPosition;

	std::vector<Bullet* >m_pBullet;

	std::string m_xOperator;
	std::string m_yOperator;

	bool m_IsShot;
	bool m_ChangesCash;
	bool m_IsCooldownBetweenBullet;
	bool m_ChangesPlutonium;
	float m_timer;
	float m_seconds;
	float  m_CooldownBetweenShot;
	
};


