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
		BEHAVIOUR_PLAYER,
		BEHAVIOUR_ATTACK,
	};
	BEHAVIOUR GoatBev;
	Building* targeted;
public:
	Goat();
	~Goat();
	void Update(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy) override;
	void pathfinding();
	void Attack(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
	void Move(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
	void PlayerInRange(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
};

#endif