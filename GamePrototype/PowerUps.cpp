#include "pch.h"
#include "PowerUps.h"
#include "Player.h"
#include "Bullet.h"

PowerUps::PowerUps()
{
	m_CooldownSpeed = new Texture(CooldownWord, m_textpath, 6, Color4f{ 0,0,0,1 });
	m_Bullet = new Texture(BulletWord, m_textpath, 6, Color4f{ 0,0,0,1 });
	m_Health = new Texture(HealthWord, m_textpath, 6, Color4f{ 0,0,0,1 });
	m_Extra = new Texture(ExtraWord, m_textpath, 6, Color4f{ 0,0,0,1 });
	m_CooldownSpeedBounds.left = 700;
	m_CooldownSpeedBounds.bottom = 250;
	m_CooldownSpeedBounds.width = 60;
	m_CooldownSpeedBounds.height = 60;

	m_ExtraHealthBounds.left = 100;
	m_ExtraHealthBounds.bottom = 250;
	m_ExtraHealthBounds.width = 60;
	m_ExtraHealthBounds.height = 60;
	
}

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

void PowerUps::Draw(const int& Plutonium)
{
	if (Plutonium>=5)
	{
		utils::SetColor(Color4f{ 0.0,1.0,0.0,1.0f });
	}
	else
	{
		utils::SetColor(Color4f{ 1.0,0.0,0.0,1.0f });
	}

	DrawBulletCooldownUpgrade();
	DrawBulletDamageIncreaser();
}

void PowerUps::DrawBulletCooldownUpgrade()
{

	utils::FillRect(m_CooldownSpeedBounds);
	m_CooldownSpeed->Draw(Point2f{ 700,260 });
	m_Bullet->Draw(Point2f{ 700,250 });
}

void PowerUps::DrawBulletDamageIncreaser()
{
	//utils::SetColor(Color4f{ 0.0,1.0,0.0,1.0f });
	utils::FillRect(m_ExtraHealthBounds);
	m_Extra->Draw(Point2f{ 100,260 });
	m_Health->Draw(Point2f{ 100,250 });

}
void PowerUps::BulletCooldownSpeedPressed(const Point2f& MousePosition, Player*& player)
{
	//std::cout << "passing" << std::endl;
	if (utils::IsPointInRect(MousePosition,m_CooldownSpeedBounds)&&player->GetPlutonium() >=5)
	{
		//std::cout << "decrease in cooldown" << std::endl;
		player->DecreaseCooldownSpeed(0.05);
		player->RemovePlutonium(5);
	}
}

void PowerUps::ExtraHealthPressed(const Point2f& MousePosition, Player*& player)
{
	if (utils::IsPointInRect(MousePosition, m_ExtraHealthBounds) && player->GetPlutonium() >= 5)
	{
		player->Addhealth(1);
		player->RemovePlutonium(5);
	}
}
