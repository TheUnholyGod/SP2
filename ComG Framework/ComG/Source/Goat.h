#ifndef _GOAT_H
#define _GOAT_H

#include "Enemy.h"
#include "Building.h"
#include "Player.h"

class Goat : public Enemy
{
private:
	Vector3 goal, newDIr;
	bool goalreached;
	enum BEHAVIOUR
	{
		BEHAVIOUR_IDLE,
		BEHAVIOUR_RUN,
	};
	BEHAVIOUR GoatBev;
	std::clock_t Iwait;
	float ITime;
	bool ignoreothers;

public:
	Goat();
	~Goat();
	void Update(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy) override;
	void pathfinding();
	void Run(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
	void Move(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
};

#endif