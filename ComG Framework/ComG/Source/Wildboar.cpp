#include "WildBoar.h"
#include "Randomizer.h"
#include "Player.h"

WildBoar::WildBoar() : Enemy(9, "OBJ//Boar.obj", "Image//boarUV.tga", "WildBoar", NORMAL, "Forest", 100, 10, 5)
{
	float temp1 = 2000 - Randomizer::generate_range(500, 1000) + Player::getplayer()->getRenderer().getPosition().x;
	float temp2 = 0;
	float temp3 = 2000 - Randomizer::generate_range(500, 1000) + Player::getplayer()->getRenderer().getPosition().z;
	gameobjrenderer_->setPosition(Vector3(temp1, temp2, temp3));
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
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
	if (health_ < max_health_*(3 / 4))
		BoarBev = BEHAVIOUR_RUN;
	else if (allAABB[1]->AABBtoAABB(*(Player::getplayer()->getAABB(0))))
		BoarBev = BEHAVIOUR_ATTACK;
}

void WildBoar::Attack(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	if (this->checkCollision(Buildings, Enemy))
		BoarBev = BEHAVIOUR_STUCK;
}

void WildBoar::Stuck(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{

}

void WildBoar::Run(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{

}