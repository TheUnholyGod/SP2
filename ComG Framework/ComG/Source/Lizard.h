#ifndef _LIZARD_H
#define _LIZARD_H

#include "Enemy.h"
#include "Player.h"

class Lizard : public Enemy
{
private:
	bool isAttaacked;
	enum BEHAVIOUR
	{
		BEHAVIOUR_IDLE,
		BEHAVIOUR_ATTACK,
		BEHAVIOUR_RETREAT,
	};
	BEHAVIOUR LizardBev;
public:
	Lizard();
	~Lizard();
	void Update(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy) override;
	void pathfinding();
	void Attack(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
	void Move(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
	void Retreat(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
};

#endif