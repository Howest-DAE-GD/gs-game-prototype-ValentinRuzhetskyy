#pragma once
#include <utils.h>
#include <vector>
#include <iostream>

class Robot;//class forwarding 

class RobotWorkPlace
{
public:
	RobotWorkPlace(Point2f pos);
	void CreateRobotWorkPlace(float left, float bottom, float width, float height,int rows, int collumns,const Point2f& pos,RobotWorkPlace* RobotWorkplaces[]);
	void CreateRobot();
	void Update(const std::vector< std::vector<Point2f>>& AllVertices);
	void SetEnemyPosition(Point2f enemyPos);
	int GetAmountOfRobots();
	~RobotWorkPlace();
	void Display();


protected:
	Point2f m_Position;
	int m_cash;
private:
	std::vector<Robot*>Robots;
	Robot* Robot1;
	int	  AmountOfRobots;
	float m_widthFrameProgressBar;
	float m_heightFrameProgressBar;

	float m_widthProgressBar;
	float m_heightProgressBar;
	float m_BuildTimer;
	bool m_IsCreated;
	bool m_cycle;

	
};

