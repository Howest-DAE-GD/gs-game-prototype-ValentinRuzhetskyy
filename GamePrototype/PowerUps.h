#pragma once
#include <Texture.h>
#include <iostream>
class Player;

class PowerUps
{
public:
	PowerUps();
	static void PowerupSpeed(Player& player);
	static void PowerupMagazine(Player& Player);
	void Draw(const int& Plutonium);
	void DrawBulletCooldownUpgrade();
	void BulletCooldownSpeedPressed(const Point2f& MousePosition, Player*& player);
	void ExtraHealthPressed(const Point2f& MousePosition, Player*& player);
	void BulletExtraDamage(const Point2f& MousePosition, Player*& player);
	void DrawHealthIncreaser();
	void DrawDamageIncreaser();
	void SetIsReleased(bool Released);
	//void Draw
private:
	const int m_PowerUpSpeed{ 1 };
	std::string m_textpath{ "Inktype-MAp2J.ttf" };
	std::string BulletWord{"Bullet "};
	std::string CooldownWord{ "Cooldown" };
	std::string ExtraWord{ "Extra" };
	std::string HealthWord{ "Health" };
	std::string DamageWord{ "Damage" };
	Texture* m_Extra;
	Texture* m_Health;
	Texture* m_CooldownSpeed;
	Texture* m_Bullet;
	Texture* m_Damage;

	Rectf m_CooldownSpeedBounds;
	Rectf m_ExtraHealthBounds;
	Rectf m_bulletDamageIncreaserBounds;
	bool m_isReleased;
};

