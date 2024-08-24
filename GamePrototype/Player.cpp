#include "pch.h"
#include "Player.h"
#include "Bullet.h"

Player::Player(Point2f ScorePosition, Point2f PlayerPostion, Point2f PlutoniumPosition, Point2f HealthPosition) :
	m_Scoreposition{ ScorePosition },
	m_PlayerPosition{ PlayerPostion },
	m_Plutoniumposition{ PlutoniumPosition },
	m_HealthPostion{ HealthPosition },
	m_Cash{ 200 },
	m_Size{ 15 },
	m_Speed{ 5 },
	m_IsShot{ false },
	m_timer{ 0 },
	m_seconds{ 0 },
	m_ChangesCash{ false },
	m_Plutonium{ 0 },
	m_CooldownBetweenShot{ 0.5 },
	m_IsCooldownBetweenBullet{false},
	m_bulletId{1},
	m_updateHealth{false}
{
	AmountOfPlutonium = std::to_string(m_Plutonium) + " " + m_PlutoniumWord;
	AmountOfCash = std::to_string(m_Cash) +" "+ m_CashWord;
	AmountOfHealth = std::to_string(m_health) +" "+ m_HealthWord;
	m_PCashDisplay = new Texture(AmountOfCash, m_textpath, m_Size, Color4f{1.0f,1.0f,1.0f,1.0f});
	m_pPlutonium = new Texture(AmountOfPlutonium,m_textpath,m_Size,Color4f{1.0f,1.0f,1.0f,1.0f});
	m_pHealth = new Texture(AmountOfHealth, m_textpath, m_Size, Color4f{ 1.0f,1.0f,1.0f,1.0f });
	m_pBullet.push_back(new Bullet{ PlayerPostion });
	//m_pBullet.push_back(new Bullet{ PlayerPostion });
	//m_pBullet.push_back(new Bullet{ PlayerPostion });
	m_hitbox.width  = 10;
	m_hitbox.height = 10;
	m_Heigth = 10;
	m_Width = 10;
}

Player::~Player()
{
}

void Player::DisplayResources()
{
	m_PCashDisplay->Draw(m_Scoreposition);
	m_pHealth->Draw(m_HealthPostion);
	m_pPlutonium->Draw(m_Plutoniumposition);
}

void Player::DisplayPlayer()
{
	utils::SetColor(Color4f{ 0.0f,1.0f,0.0f,1.0 });
	utils::FillRect(m_PlayerPosition.x, m_PlayerPosition.y, 10.0f, 10.0f);

	for (int i = 0; i < m_pBullet.size(); i++)
	{
		m_pBullet[i]->Display();
	}
}

void Player::Update(float elapsedSec)
{

	const Uint8* pStates{};

	pStates = SDL_GetKeyboardState(nullptr);
	const bool isRight{ bool(pStates[SDL_SCANCODE_D])};
	const bool isLeft { bool(pStates[SDL_SCANCODE_A]) };
	const bool isUp   { bool(pStates[SDL_SCANCODE_W])	 };
	const bool isDown { bool(pStates[SDL_SCANCODE_S]) };


	if (isRight && isUp&&!m_rightBorderCollission|| isRight && isUp && !m_upBorderCollission) {
		if (!m_rightBorderCollission)
		{
			m_PlayerPosition.x += m_Speed;
		}

		if (!m_upBorderCollission)
		{
			m_PlayerPosition.y += m_Speed;
		}
	}
	else if (isRight && isDown && !m_rightBorderCollission|| isRight && isDown && !m_downBorderCollission)
	{
		if (!m_rightBorderCollission)
		{
			m_PlayerPosition.x += m_Speed;
		}
		if (!m_downBorderCollission)
		{
			m_PlayerPosition.y -= m_Speed;
		}
	
		
	}
	else if (isLeft && isUp && !m_leftBorderCollission|| isLeft && isUp && !m_upBorderCollission)
	{
		if (!m_upBorderCollission)
		{
			m_PlayerPosition.y += m_Speed;
		}
		if (!m_leftBorderCollission)
		{
			m_PlayerPosition.x -= m_Speed;
		}


	}
	else if (isLeft && isDown && !m_leftBorderCollission|| isLeft && isDown && !m_downBorderCollission)
	{
		if (!m_leftBorderCollission)
		{
			m_PlayerPosition.x -= m_Speed;
		}

		if (!m_downBorderCollission)
		{
			m_PlayerPosition.y -= m_Speed;
		}

	}
	else if (isRight && !m_rightBorderCollission) {
		m_PlayerPosition.x += m_Speed; 

	}
	else if (isLeft && !m_leftBorderCollission) {
		m_PlayerPosition.x -= m_Speed;

	}
	else if (isDown && !m_downBorderCollission) {
		m_PlayerPosition.y -= m_Speed; 

	}
	else if (isUp && !m_upBorderCollission) {
		m_PlayerPosition.y += m_Speed; 

	}

			//switch (m_PlayerDirection)
			//{
			//case Player::RightUp:
			//	m_yOperator = "+";
			//	m_xOperator = "+";
			//	break;
			//case Player::RightDown:
			//	m_yOperator = "-";
			//	m_xOperator = "+";
			//	break;
			//case Player::LeftUp:
			//	m_yOperator = "+";
			//	m_xOperator = "-";
			//	break;
			//case Player::LeftDown:
			//	m_yOperator = "-";
			//	m_xOperator = "-";
			//	break;
			//case Player::Right:
			//	m_yOperator = "nothing";
			//	m_xOperator = "+";
			//	break;
			//case Player::Left:
			//	m_yOperator = "nothing";
			//	m_xOperator = "-";
			//	break;
			//case Player::Up:
			//	m_yOperator = "+";
			//	m_xOperator = "nothing";
			//	break;
			//case Player::Down:
			//	m_yOperator = "-";
			//	m_xOperator = "nothing";
			//	break;
			//default:
			//	break;
			//}
	if (m_IsShot)
	{

			if (m_timer > 2)
			{
				m_seconds += 1;
				m_timer = 0;
				//	std::cout << "passed thru timer" << std::endl;
			}
			else
			{
				//std::cout << m_timer<< std::endl;
				m_timer += elapsedSec;
			}

	}
	if (m_seconds >= 3)
	{
		m_IsShot = false;
		m_seconds = 0;
	}
	for (int i = 0; i < m_pBullet.size(); i++)
	{
		m_pBullet[i]->Update();
	}

	
	if (m_IsCooldownBetweenBullet)
	{
		if (m_CooldownBetweenShot < 0.5)
		{
		//	std::cout << "goes thru here" << std::endl;
			m_CooldownBetweenShot += elapsedSec;
	
		}
		else if (m_CooldownBetweenShot>=0.5)
		{
			m_IsCooldownBetweenBullet=false;
			m_CooldownBetweenShot = 0;
		}
	}

	if (m_ChangesCash)
	{
		AmountOfCash =  std::to_string(m_Cash)+ m_CashWord;
		delete  m_PCashDisplay;
		m_PCashDisplay = nullptr;
		m_PCashDisplay = new Texture(AmountOfCash, m_textpath, m_Size, Color4f{ 1.0f,1.0f,1.0f,1.0f });
		m_ChangesCash = false;
	}
	if (m_ChangesPlutonium)
	{
		AmountOfPlutonium = std::to_string(m_Plutonium) + m_PlutoniumWord;
		delete  m_pPlutonium;
		m_pPlutonium = nullptr;
		m_pPlutonium = new Texture(AmountOfPlutonium, m_textpath, m_Size, Color4f{ 1.0f,1.0f,1.0f,1.0f });
		m_ChangesPlutonium = false;
	}
	if (m_updateHealth)
	{
		AmountOfHealth = std::to_string(m_health) + " " + m_HealthWord;
		delete m_pHealth;
		m_pHealth = nullptr;
		m_pHealth = new Texture(AmountOfHealth, m_textpath, m_Size, Color4f{ 1.0f,1.0f,1.0f,1.0f });
		m_updateHealth = false;
	}
	UpdateHitboxPostion();	
	//std::cout << m_health << std::endl;
}

int Player::GetCash()
{
	return m_Cash;
}

int Player::GetPlutonium()
{
	return m_Plutonium;
}

void Player::RemoveCash(int m_cash)
{
	m_Cash -= m_cash;
	m_ChangesCash = true;
}

void Player::AddPlutonium(int plutonium)
{
	m_Plutonium += plutonium;
	m_ChangesPlutonium = true;
}

void Player::UpdateHitboxPostion()
{
	m_hitbox.left = m_PlayerPosition.x;
	m_hitbox.bottom = m_PlayerPosition.y;
}

void Player::RayCast(const std::vector< std::vector<Point2f>>& AllVertices)
{
	m_leftBorderCollission = false;
	m_rightBorderCollission = false;
	m_downBorderCollission = false;
	m_upBorderCollission = false;

	for (int index{}; index < AllVertices.size(); ++index)
	{
		if (utils::Raycast(AllVertices[index], Point2f(m_PlayerPosition.x - 8, m_PlayerPosition.y), Point2f(m_PlayerPosition.x + 10 / 2, m_PlayerPosition.y), m_hitInfo))
		{
			m_leftBorderCollission = true;
		}
		if (utils::Raycast(AllVertices[index], Point2f(m_PlayerPosition.x + m_Width / 2, m_PlayerPosition.y), Point2f(m_PlayerPosition.x + m_Width + 8, m_PlayerPosition.y), m_hitInfo))
		{
			m_rightBorderCollission = true;
		}
		if (utils::Raycast(AllVertices[index], Point2f(m_PlayerPosition.x - 8, m_PlayerPosition.y + m_Heigth), Point2f(m_PlayerPosition.x + m_Width / 2, m_PlayerPosition.y + m_Heigth), m_hitInfo))
		{
			m_leftBorderCollission = true;
		}
		if (utils::Raycast(AllVertices[index], Point2f(m_PlayerPosition.x + m_Width / 2, m_PlayerPosition.y + m_Heigth), Point2f(m_PlayerPosition.x + m_Width + 8, m_PlayerPosition.y + m_Heigth), m_hitInfo))
		{
			m_rightBorderCollission = true;
		}
		if (utils::Raycast(AllVertices[index], Point2f(m_PlayerPosition.x, m_PlayerPosition.y - 8), Point2f(m_PlayerPosition.x, m_PlayerPosition.y + m_Heigth / 2), m_hitInfo))
		{
			m_downBorderCollission = true;
		}
		if (utils::Raycast(AllVertices[index], Point2f(m_PlayerPosition.x, m_PlayerPosition.y + m_Heigth / 2), Point2f(m_PlayerPosition.x, m_PlayerPosition.y + m_Heigth + 8), m_hitInfo))
		{
			m_upBorderCollission = true;
		}
		if (utils::Raycast(AllVertices[index], Point2f(m_PlayerPosition.x + m_Width, m_PlayerPosition.y - 8), Point2f(m_PlayerPosition.x + m_Width, m_PlayerPosition.y + m_Heigth / 2), m_hitInfo))
		{
			m_downBorderCollission = true;
		}
		if (utils::Raycast(AllVertices[index], Point2f(m_PlayerPosition.x + m_Width, m_PlayerPosition.y + m_Heigth / 2), Point2f(m_PlayerPosition.x + m_Width, m_PlayerPosition.y + m_Heigth + 8), m_hitInfo))
		{
			m_upBorderCollission = true;
		}
	}
}

void Player::ManageBullets( float xposition,  float yposition,  float width,  float heigth)
{
	for (int i = 0; i < m_pBullet.size(); i++)
	{
		
			if (xposition+width<=m_pBullet[i]->GetPosition().x||xposition>m_pBullet[i]->GetPosition().x||yposition+heigth<m_pBullet[i]->GetPosition().y|| yposition>m_pBullet[i]->GetPosition().y)
			{
				//std::cout << xposition << "/" << xposition + width << std::endl;
				//std::cout << yposition << "/" << yposition +heigth << std::endl;
				//std::cout << m_pBullet[i]->GetPosition().x<<"/"<<m_pBullet[i]->GetPosition().y << std::endl;
				delete m_pBullet[i];
				m_pBullet.erase(m_pBullet.begin() + i);
				--i;
			}
	}
}


bool Player::IsShot()
{
	return m_IsShot;
}

bool Player::GetIsDeath()
{
	return m_isDeath;
}

Point2f Player::GetBulletPosition()
{
	for (int i = 0; i < m_pBullet.size(); i++)
	{
		return m_pBullet[i]->GetPosition();
	}

}

void Player::SetBulletDirection(Point2f BulletDirection)
{
	//for (int i = 0; i < m_pBullet.size(); i++)
	//{
	//	if (m_IsCooldownBetweenBullet=false)
	//	{
	//		
	//	}
	//	//	std::cout << "pressed" << std::endl;
	//	if (m_CooldownBetweenShot>5)
	//	{
	//		m_IsShot = true;
	//	
	//	
	//		m_CooldownBetweenShot = 0;
	//	}

	//}


	if (!m_IsCooldownBetweenBullet) {
		//m_pBullet[m_bulletId]->SetPosition(m_PlayerPosition)
	
		m_pBullet.push_back(new Bullet{ m_PlayerPosition });
		std::cout << m_pBullet.size() << std::endl;
		for (int  i = 0; i < m_pBullet.size(); i++)
		{
			if (!m_pBullet[i]->GetIsTraveling())
			{
				m_pBullet[i]->UpdateBulletVelocity(BulletDirection);
			}
		}

		//m_bulletId = (m_bulletId + 1) % m_pBullet.size();
		m_IsCooldownBetweenBullet = true;
	}
}

void Player::Addcash(int cash)
{
	m_Cash += cash;
	m_ChangesCash=true;

}

Point2f Player::GetPlayerPosition()
{
	return m_PlayerPosition;
}

void Player::Collision()
{
	if (!m_isDeath&&m_health>0)
	{
		m_health -= 1;
		m_updateHealth = true;

	}
	
	if(m_health<=0)
	{
		m_isDeath = true;
	}

}

Rectf Player::GetBulletHitbox()
{
	for (int i = 0; i < m_pBullet.size(); i++)
	{
		return m_pBullet[i]->GetHitbox();
	}
}

Rectf Player::GetPlayerHitbox()
{
	return m_hitbox;
}

std::vector<Bullet*> Player::GetBulletAmount()
{
	return m_pBullet;
}

int Player::getBullets()
{
	return m_pBullet.size();
}
