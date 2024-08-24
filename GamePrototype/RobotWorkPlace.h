#pragma once
#include <utils.h>
#include <vector>
#include <iostream>


class enemies;
class RobotWorkPlace
{
public:
	RobotWorkPlace(Point2f pos);
	void CreateRobotWorkPlace(float left, float bottom, float width, float height,int rows, int collumns,const Point2f& pos,RobotWorkPlace* RobotWorkplaces[]);

	void Update(const std::vector< std::vector<Point2f>>& AllVertices);
	void SetEnemyCollision( std::vector<enemies*> AmountofEnemies);
	void SetOuterWalls(float left, float bottom, float width, float height);
	void Display();
	bool IsPlutoniumReady();
	int		GetReadyPlutonium();
	virtual ~RobotWorkPlace();


	static const int m_BuildPrice{ 200 };

protected:
	Point2f m_Position;
	
private:
	int m_Plutonium;
	int m_plutoniumLimit;
	

	float m_widthFrameProgressBar;
	float m_heightFrameProgressBar;
	float m_widthProgressBar;
	float m_heightProgressBar;
	float m_BuildTimer;

	bool m_IsCreated;
	bool m_cycle;
	bool m_IsPlutoniumReady;
	
};

