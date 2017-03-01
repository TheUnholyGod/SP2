#include "Molerat.h"
#include "Player.h"
#include "Randomizer.h"

Molerat::Molerat() : Enemy(1, "OBJ//MoleRat.obj","Image//MoleratUV.tga" ,"Molerat", NORMAL, "Base", 100, 10, 4)
{
	float temp1 = 250 - Randomizer::generate_range(1,500) + Player::getplayer()->getRenderer().getPosition().x;
	float temp2 = 0;
	float temp3 = 250 - Randomizer::generate_range(1, 500) + Player::getplayer()->getRenderer().getPosition().z;
	gameobjrenderer_->setPosition(Vector3(temp1, temp2, temp3));
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
	goalreached = true;
	newDIr = Vector3(1, 0, 0);
	MoleratBev = BEHAVIOUR_IDLE;
}

Molerat::~Molerat()
{
}

void Molerat::Update(double dt,std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	switch (MoleratBev)
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
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
}

void Molerat::pathfinding()
{
	float temp = (float)Randomizer::generate_range(1, 360);
	Mtx44 rotation;
	rotation.SetToRotation(temp, 0, 1, 0);
	newDIr = rotation * newDIr;
	goal = newDIr;
	goalreached = false;
	gameobjrenderer_->setForward(newDIr);
}

void Molerat::Attack(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	std::list<Building*> temp;
	if (!this->checkCollision(temp, Enemy))
	{
		if (targeted->getAABB(0)->AABBtoAABB(*this->getAABB(0)))
		{
			targeted->takeDamage(attack_);
			allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
			allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
		}
		else
		{
			gameobjrenderer_->setForward((this->gameobjrenderer_->getPosition() - targeted->getRenderer().getPosition()).Normalized());
			gameobjrenderer_->translate(gameobjrenderer_->getForward(), 50 * dt);

			allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
			allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
		}
	}
	else if (this->allAABB[1]->pointtoAABB(Player::getplayer()->getRenderer().getPosition(), Player::getplayer()->getRenderer().getForward()))
	{
		MoleratBev = BEHAVIOUR_PLAYER;
	}
}

void Molerat::Move(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
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
		MoleratBev = BEHAVIOUR_PLAYER;
	}
	for (auto &i : Buildings)
	{
		if (this->allAABB[0]->AABBtoAABB(*i->getAABB(0)))
		{
			targeted = i;
			MoleratBev = BEHAVIOUR_ATTACK;
			break;
		}
	}
}

void Molerat::PlayerInRange(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
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
		MoleratBev = BEHAVIOUR_IDLE;
	}
}