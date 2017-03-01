#ifndef _WILDBOAR_H
#define _WILDBOAR_H

#include "Enemy.h"
#include "Building.h"

class WildBoar : public Enemy
{
private:
	enum BEHAVIOUR
	{
		BEHAVIOUR_IDLE,
		BEHAVIOUR_ATTACK,
		BEHAVIOUR_STUCK,
		BEHAVIOUR_RUN,
	};
	BEHAVIOUR BoarBev;
public:
	WildBoar();
	~WildBoar();
	void Update(double dt,std::list<Building*> Buildings, std::vector<Enemy*> Enemy) override;
	void Idle(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
	void Attack(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
	void Stuck(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
	void Run(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);
};

#endif