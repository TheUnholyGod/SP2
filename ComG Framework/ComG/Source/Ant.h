#ifndef ANT_H
#define ANT_H

#include "Enemy.h"
#include "Ant_Hill.h"
#include "Player.h"
class Ant : public Enemy
{
	Vector3 goal, newDIr;
	bool goalreached;
	enum BEHAVIOUR
	{
		BEHAVIOUR_IDLE,
		BEHAVIOUR_PLAYER,
		BEHAVIOUR_ATTACK,
	};
	BEHAVIOUR AntBev;
	Ant_Hill* my_hill;
	Building* targeted;
public:
	Ant();
	~Ant();
	void Update(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy) override;
	void pathfinding();
	void Attack(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
	void Move(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
	void PlayerInRange(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
};

#endif