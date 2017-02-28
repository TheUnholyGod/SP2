#include "WildBoar.h"

WildBoar::WildBoar() : Enemy(9, "OBJ//Boar.obj", "Image//boarUV.tga", "WildBoar", NORMAL, "Forest", 100, 10, 5)
{
	BoarBev = BEHAVIOUR_IDLE;
}

WildBoar::~WildBoar()
{
}

void WildBoar::Update(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	switch (BoarBev)
	{
	case BEHAVIOUR_IDLE:
		Idle(dt, Buildings, Enemy);
		break;
	case BEHAVIOUR_ATTACK:
		Attack(dt, Buildings, Enemy);
		break;
	case BEHAVIOUR_STUCK:
		Stuck(dt, Buildings, Enemy);
		break;
	case BEHAVIOUR_RUN:
		Run(dt, Buildings, Enemy);
		break;
	default:
		break;
	}
}

void WildBoar::Idle(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{

}

void WildBoar::Attack(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{

}

void WildBoar::Stuck(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{

}

void WildBoar::Run(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{

}