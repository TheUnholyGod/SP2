#ifndef _MOLERAT_H
#define _MOLERAT_H

#include "Enemy.h"
#include "Building.h"
#include "Player.h"

class Molerat : public Enemy
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
	BEHAVIOUR MoleratBev;
	Building* targeted;
public:
	Molerat();
	~Molerat();
	void Update(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy) override;
	void pathfinding();
	void Attack(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
	void Move(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
	void PlayerInRange(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
};

#endif