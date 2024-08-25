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
	void RemovePlutonium(int plutonium);
	void UpdateHitboxPostion();
	void RayCast(const std::vector< std::vector<Point2f>>& AllVertices);
	void ManageBullets( float xposition,  float yposition,  float width,  float heigth, float factoryX, float factoryY, float factoryWidth, float factoryHeight);
	void DecreaseCooldownSpeed(float decrease);
	void SetIsShooting(bool isShooting);
	void SetIsReleased(bool isReleased);
	void Addhealth(int Health);
	void UpgradeBullet(int damage);
	void UpdateUnits();
	void Collision();
	void DrawYouDied();


	bool IsShot();
	bool GetIsDeath();

	Point2f GetBulletPosition();
	Point2f GetPlayerPosition();

	Rectf	GetBulletHitbox();
	Rectf	GetPlayerHitbox();

	std::vector<Bullet*>& GetBulletAmount();
	int getBullets();
	int GetPlutonium();
	int GetCash();
	int GetBullletDamage();
	float getCooldownSpeed();
	friend void PowerUps::PowerupMagazine(Player& Player);
	friend void PowerUps::PowerupSpeed(Player& Player);




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

	std::string m_textpath{ "Inktype-MAp2J.ttf" };
	std::string AmountOfCash;
	std::string AmountOfPlutonium;
	std::string m_CashWord{"cash"};
	std::string m_PlutoniumWord{"plutonium"};
	std::string m_HealthWord{ "Health" };
	std::string AmountOfHealth;
	std::string YouDied{ "You Died" };
	Texture* m_PCashDisplay;
	Texture* m_pPlutonium;
	Texture* m_pHealth;
	Texture* m_youDied;
	Point2f m_Scoreposition;
	Point2f m_Plutoniumposition;
	Point2f m_PlayerPosition;
	Point2f m_HealthPostion;

	std::vector<Bullet* >m_pBullet;

	std::string m_xOperator;
	std::string m_yOperator;

	bool m_isShooting;
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
	bool m_IsReleased;
	float m_timer;
	float m_seconds;
	float  m_TimeBetweenShot;
	float m_MaxTimeBetweenShot;
	float m_opacity{0};
	int m_health{1};
	int m_damage{ 1 };
	float m_Width;
	float m_Heigth;
	Rectf m_hitbox;
	utils::HitInfo m_hitInfo;
	const wchar_t* filePath = L"Resources/YouDied.bmp";
	HBITMAP hbitMap = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

};


