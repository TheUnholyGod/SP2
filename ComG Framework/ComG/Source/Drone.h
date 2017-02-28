#pragma once

#include "Enemy.h"
#include "Randomizer.h"

class Drone : public Enemy
{
private:
	Vector3 newForward;
	Vector3 charPos;
	Vector3 dronePos;

	float elapsedTime;
	std::clock_t start;

public:
	Drone();
	~Drone();

	void Update(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
	void Move(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
	void Pathfind();
	void ComeBack();
};