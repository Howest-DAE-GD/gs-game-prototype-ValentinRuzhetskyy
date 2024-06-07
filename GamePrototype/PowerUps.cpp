#include "pch.h"
#include "PowerUps.h"
#include "Player.h"
#include "Bullet.h"

void PowerUps::PowerupSpeed(Player& Player)
{
	Player.m_Speed += 1;
}

void PowerUps::PowerupMagazine(Player& Player)
{
	Bullet* m_pBulletPowerup;
	m_pBulletPowerup = new Bullet{ Player.m_PlayerPosition };
	Player.m_pBullet.push_back(m_pBulletPowerup);
}
