#include "Goat.h"
#include "Randomizer.h"

Goat::Goat() : Enemy(8, "OBJ//Goat.obj", "", "Goat", NORMAL, "Forest", 100, 5, 4)
{
	float x = 250 - Randomizer::generate_range(1, 500) + Player::getplayer()->getRenderer().getPosition().x;
	float y = 0;
	float z = 250 - Randomizer::generate_range(1, 500) + Player::getplayer()->getRenderer().getPosition().z;
	gameobjrenderer_->setPosition(Vector3(x, y, z));
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());//Collision
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());//detection range
	goalreached = true;
	newDIr = Vector3(1, 0, 0);
	GoatBev = BEHAVIOUR_IDLE;
}

Goat::~Goat()
{
}

void Goat::Update(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	switch (GoatBev)
	{
	case BEHAVIOUR_IDLE:
		Move(dt, Buildings, Enemy);
		break;
	case BEHAVIOUR_PLAYER:
		PlayerInRange(dt, Buildings, Enemy);
		break;
	case BEHAVIOUR_ATTACK:
		Attack(dt, Buildings, Enemy);
		break;
	default:
		break;
	}
}

void Goat::pathfinding()
{
	float temp = (float)Randomizer::generate_range(1, 360);
	Mtx44 rotation;
	rotation.SetToRotation(temp, 0, 1, 0);
	newDIr = rotation * newDIr;
	goal = newDIr;
	goalreached = false;
	gameobjrenderer_->setForward(newDIr);
}

void Goat::Attack(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	std::list<Building*> temp;
	if (!this->checkCollision(temp, Enemy))
	{
		if (targeted->getAABB(0)->AABBtoAABB(*this->getAABB(0)))
		{
			targeted->takeDamage(attack_);
			allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
			allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
			//std::cout << "I ATTACKED" << std::endl;
		}
		else
		{
			gameobjrenderer_->setForward((this->gameobjrenderer_->getPosition() - targeted->getRenderer().getPosition()).Normalized());
			gameobjrenderer_->translate(gameobjrenderer_->getForward(), 50 * dt);
			allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
			allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
			//std::cout << "I AM ATTACKING" << std::endl;
		}
	}
	else if (this->allAABB[1]->pointtoAABB(Player::getplayer()->getRenderer().getPosition(), Player::getplayer()->getRenderer().getForward()))
	{
		GoatBev = BEHAVIOUR_PLAYER;
	}
}

void Goat::Move(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	if (!this->checkCollision(Buildings, Enemy))
	{
		gameobjrenderer_->rotate((0, 1, 0), 20 * dt, -(Player::getplayer()->getRenderer().getPosition() - gameobjrenderer_->getPosition()));
		gameobjrenderer_->translate(gameobjrenderer_->getForward(), 35 * dt);
		goalreached = true;
	}
	else if (this->checkCollision(Buildings, Enemy))
	{
		gameobjrenderer_->setForward(-gameobjrenderer_->getRight());
		gameobjrenderer_->translate(gameobjrenderer_->getForward(), 35 * dt);
	}
	else if (this->allAABB[1]->pointtoAABB(Player::getplayer()->getRenderer().getPosition(), Player::getplayer()->getRenderer().getForward()))
	{
		GoatBev = BEHAVIOUR_PLAYER;
	}
	for (auto &i : Buildings)
	{
		if (this->allAABB[0]->AABBtoAABB(*i->getAABB(0)))
		{
			std::cout << i->getName() << std::endl;
			targeted = i;
			GoatBev = BEHAVIOUR_ATTACK;
			break;
		}
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
}

void Goat::PlayerInRange(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	if (!this->checkCollision(Buildings, Enemy))
	{
		if (goalreached)
			pathfinding();
		gameobjrenderer_->translate(gameobjrenderer_->getForward(), 35 * dt);
		if (gameobjrenderer_->getPosition() == goal)
			goalreached = true;

	}
	else if (this->checkCollision(Buildings, Enemy))
	{
		gameobjrenderer_->setForward(-gameobjrenderer_->getRight());
		gameobjrenderer_->translate(gameobjrenderer_->getForward(), 35 * dt);
	}
	else if (!this->allAABB[1]->pointtoAABB(Player::getplayer()->getRenderer().getPosition(), Player::getplayer()->getRenderer().getForward()))
	{
		GoatBev = BEHAVIOUR_IDLE;
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
}