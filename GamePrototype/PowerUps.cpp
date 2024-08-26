#include "pch.h"
#include "PowerUps.h"
#include "Player.h"
#include "Bullet.h"

PowerUps::PowerUps()
{
	m_CooldownSpeed = new Texture(CooldownWord, m_textpath, 12, Color4f{ 0,0,0,1 });
	m_Bullet = new Texture(BulletWord, m_textpath, 12, Color4f{ 0,0,0,1 });
	m_Health = new Texture(HealthWord, m_textpath, 12, Color4f{ 0,0,0,1 });
	m_Extra  = new Texture(ExtraWord, m_textpath, 12, Color4f{ 0,0,0,1 });
	m_Damage = new Texture(DamageWord, m_textpath, 12, Color4f{ 0,0,0,1 });
	m_Speed = new Texture(SpeedText, m_textpath, 12, Color4f{ 0,0,0,1 });

	m_CooldownSpeedBounds.left = 700;
	m_CooldownSpeedBounds.bottom = 250;
	m_CooldownSpeedBounds.width = 60;
	m_CooldownSpeedBounds.height = 60;

	m_ExtraHealthBounds.left = 100;
	m_ExtraHealthBounds.bottom = 250;
	m_ExtraHealthBounds.width = 60;
	m_ExtraHealthBounds.height = 60;
	
	m_bulletDamageIncreaserBounds.left = 390;
	m_bulletDamageIncreaserBounds.bottom = 20;
	m_bulletDamageIncreaserBounds.width = 60;
	m_bulletDamageIncreaserBounds.height = 60;

	m_bulletSpeedIncreaseBounds.left = 390;
	m_bulletSpeedIncreaseBounds.bottom = 430;
	m_bulletSpeedIncreaseBounds.width = 60;
	m_bulletSpeedIncreaseBounds.height = 60;

}

void PowerUps::PowerupSpeed(Player& Player)
{
	Player.m_Speed += 1;
}

void PowerUps::PowerupMagazine(Player& Player)
{

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
	DrawHealthIncreaser();
	DrawDamageIncreaser();
	DrawBulletSpeedIncreaser();
}

void PowerUps::DrawBulletCooldownUpgrade()
{
	utils::FillRect(m_CooldownSpeedBounds);
	m_CooldownSpeed->Draw(Point2f{ 700,260 });
	m_Bullet->Draw(Point2f{ 700,250 });
}

void PowerUps::DrawHealthIncreaser()
{
	//utils::SetColor(Color4f{ 0.0,1.0,0.0,1.0f });
	utils::FillRect(m_ExtraHealthBounds);
	m_Extra	->Draw(Point2f{ 100,260 });
	m_Health->Draw(Point2f{ 100,250 });
}

void PowerUps::DrawDamageIncreaser()
{
	utils::FillRect(m_bulletDamageIncreaserBounds);
	m_Bullet->Draw(Point2f{ 390,30 });
	m_Damage->Draw(Point2f{ 390,20 });
}

void PowerUps::DrawBulletSpeedIncreaser()
{
	utils::FillRect(m_bulletSpeedIncreaseBounds);
	m_Speed->Draw(Point2f{ 390,440 });
	m_Damage->Draw(Point2f{ 390,430 });
}

void PowerUps::SetIsReleased(bool Released)
{
	m_isReleased = Released;
}

void PowerUps::BulletCooldownSpeedPressed(const Point2f& MousePosition, Player*& player)
{
	//std::cout << "passing" << std::endl;
	if (utils::IsPointInRect(MousePosition,m_CooldownSpeedBounds)&&player->GetPlutonium() >=5)
	{
		//std::cout << "decrease in cooldown" << std::endl;
		if (m_isReleased)
		{
			if (player->getCooldownSpeed()>0.03)
			{
				player->DecreaseCooldownSpeed(0.03);
			}
			player->RemovePlutonium(5);
			m_isReleased = false;
		}

	}
}

void PowerUps::ExtraHealthPressed(const Point2f& MousePosition, Player*& player)
{
	if (utils::IsPointInRect(MousePosition, m_ExtraHealthBounds) && player->GetPlutonium() >= 5)
	{
		if (m_isReleased)
		{
			player->Addhealth(1);
			player->RemovePlutonium(5);
			m_isReleased = false;
		}
	}
}

void PowerUps::BulletExtraDamage(const Point2f& MousePosition, Player*& player)
{
	if (utils::IsPointInRect(MousePosition, m_bulletDamageIncreaserBounds) && player->GetPlutonium() >= 5)
	{
		//std::cout << "decrease in cooldown" << std::endl;
		if (m_isReleased)
		{
			player->UpgradeBullet(1);
			player->RemovePlutonium(5);
			m_isReleased = false;
		}
	}
}

void PowerUps::BulletExtraSpeed(const Point2f& MousePosition, Player*& player)
{
	if (utils::IsPointInRect(MousePosition, m_bulletSpeedIncreaseBounds) && player->GetPlutonium() >= 5)
	{
		if (m_isReleased)
		{
			player->UpgradeBulletSpeed(1);
			player->RemovePlutonium(5);
			m_isReleased = false;
		}
	}
}
