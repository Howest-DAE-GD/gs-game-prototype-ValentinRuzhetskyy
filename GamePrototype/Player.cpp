#include "pch.h"
#include "Player.h"
#include "Bullet.h"

Player::Player(Point2f ScorePosition, Point2f PlayerPostion, Point2f PlutoniumPosition) :
	m_Scoreposition{ ScorePosition },
	m_PlayerPosition{ PlayerPostion },
	m_Plutoniumposition{ PlutoniumPosition },
	m_Cash{ 200 },
	m_Size{ 15 },
	m_Speed{ 5 },
	m_IsShot{ false },
	m_timer{ 0 },
	m_seconds{ 0 },
	m_ChangesCash{ false },
	m_Plutonium{ 0 },
	m_CooldownBetweenShot{ 0 },
	m_IsCooldownBetweenBullet{false},
	m_bulletId{1}
{
	AmountOfPlutonium = std::to_string(m_Plutonium) + " " + m_PlutoniumWord;
	AmountOfCash = std::to_string(m_Cash) +" "+ m_CashWord;
	m_PCashDisplay = new Texture(AmountOfCash, m_textpath, m_Size, Color4f{1.0f,1.0f,1.0f,1.0f});
	m_pPlutonium = new Texture(AmountOfPlutonium,m_textpath,m_Size,Color4f{1.0f,1.0f,1.0f,1.0f});
	m_pBullet.push_back(new Bullet{ PlayerPostion });
	m_pBullet.push_back(new Bullet{ PlayerPostion });
	m_pBullet.push_back(new Bullet{ PlayerPostion });


}

Player::~Player()
{
}

void Player::DisplayResources()
{

	m_PCashDisplay->Draw(m_Scoreposition);
	

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
	const bool isRight{ bool(pStates[SDL_SCANCODE_RIGHT])};
	const bool isLeft { bool(pStates[SDL_SCANCODE_LEFT]) };
	const bool isUp   { bool(pStates[SDL_SCANCODE_UP])	 };
	const bool isDown { bool(pStates[SDL_SCANCODE_DOWN]) };


	if (isRight && isUp) {
		m_PlayerPosition.x += m_Speed;
		m_PlayerPosition.y += m_Speed;
	}
	else if (isRight && isDown)
	{
		m_PlayerPosition.x += m_Speed;
		m_PlayerPosition.y -= m_Speed;
		
	}
	else if (isLeft && isUp)
	{
		m_PlayerPosition.x -= m_Speed;
		m_PlayerPosition.y += m_Speed;

	}
	else if (isLeft && isDown)
	{
		m_PlayerPosition.x -= m_Speed;
		m_PlayerPosition.y -= m_Speed;

	}
	else if (isRight) { 
		m_PlayerPosition.x += m_Speed; 

	}
	else if (isLeft) { 
		m_PlayerPosition.x -= m_Speed;

	}
	else if (isDown) { 
		m_PlayerPosition.y -= m_Speed; 

	}
	else if (isUp) { 
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

	
	if (m_IsCooldownBetweenBullet==true)
	{
		if (m_CooldownBetweenShot < 1)
		{
			std::cout << "goes thru here" << std::endl;
			m_CooldownBetweenShot += elapsedSec;
	
		}
		else if (m_CooldownBetweenShot>1)
		{
			m_IsCooldownBetweenBullet=false;
		}
	}

	std::cout << m_bulletId << std::endl;

	//switch (m_ScanCode)
	//{
	//default:
	//	break;
	//case SDL_SCANCODE_RIGHT:
	//	m_PlayerPosition.x += m_Speed;
	//	break;
	//case SDL_SCANCODE_LEFT:
	//	m_PlayerPosition.x -= m_Speed;
	//	break;
	//case SDL_SCANCODE_UP:
	//	m_PlayerPosition.y += m_Speed;
	//	break;
	//case SDL_SCANCODE_DOWN:
	//	m_PlayerPosition.y -= m_Speed;
	//	break;
	//}
	//std::cout << m_IsShot << std::endl;


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
}

int Player::GetCash()
{
	return m_Cash;
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

bool Player::IsShot()
{
	return m_IsShot;
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


	if (m_IsCooldownBetweenBullet == false) {
		m_pBullet[m_bulletId]->SetPosition(m_PlayerPosition);
		m_pBullet[m_bulletId]->UpdateBulletVelocity(BulletDirection);
		m_bulletId = (m_bulletId + 1) % m_pBullet.size();
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

std::vector<Bullet*> Player::GetBulletAmount()
{
	return m_pBullet;
}
