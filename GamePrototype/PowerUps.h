#pragma once
class Player;

class PowerUps
{
public:
	static void PowerupSpeed(Player& Player);
	static void PowerupMagazine(Player& Player);

private:
	const int m_PowerUpSpeed{ 1 };

	
};

