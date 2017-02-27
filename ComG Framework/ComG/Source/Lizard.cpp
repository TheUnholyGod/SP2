#include "Lizard.h"
#include "Randomizer.h"

Lizard::Lizard() : Enemy(2, "OBJ//Lizard.obj", "Image//LizardUV.tga", "Lizard", NORMAL, "Base", 100, 10, 2)
{
	float temp1 = 250 - Randomizer::generate_range(1, 500) + Player::getplayer()->getRenderer().getPosition().x;
	float temp2 = 0;
	float temp3 = 250 - Randomizer::generate_range(1, 500) + Player::getplayer()->getRenderer().getPosition().z;
	gameobjrenderer_->setPosition(Vector3(temp1, temp2, temp3));
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
	LizardBev = BEHAVIOUR_IDLE;
}

Lizard::~Lizard()
{
}

void Lizard::Update(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	switch (LizardBev)
	{
	case BEHAVIOUR_IDLE:
		Move(dt, Buildings, Enemy);
		break;
	case BEHAVIOUR_ATTACK:
		Attack(dt, Buildings, Enemy);
		break;
	case BEHAVIOUR_RETREAT:
		Retreat(dt, Buildings, Enemy);
		break;
	default:
		break;
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
}

void Lizard::pathfinding()
{

}

void Lizard::Attack(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	if (!checkCollision(Buildings, Enemy))
	{
		if (this->allAABB[0]->AABBtoAABB(*Player::getplayer()->getAABB(0)))
		{
			gameobjrenderer_->setForward(this->gameobjrenderer_->getRight());
			gameobjrenderer_->translate(gameobjrenderer_->getForward(), 50 * dt);
			Player::getplayer()->receivedamage(attack_);
		}
		else if (this->allAABB[1]->AABBtoAABB(*Player::getplayer()->getAABB(0)))
		{
			gameobjrenderer_->setForward((this->gameobjrenderer_->getPosition() - Player::getplayer()->getRenderer().getPosition()).Normalized());
			gameobjrenderer_->translate(this->gameobjrenderer_->getForward(), 50 * dt);
		}
	}
	else if (checkCollision(Buildings, Enemy))
	{
		gameobjrenderer_->setForward(-gameobjrenderer_->getRight());
		gameobjrenderer_->translate(gameobjrenderer_->getForward(), 50 * dt);
	}
	if (health_ < (max_health_ / 2))
	{
		LizardBev = BEHAVIOUR_RETREAT;
	}
}

void Lizard::Move(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	if (this->allAABB[1]->pointtoAABB(Player::getplayer()->getRenderer().getPosition(), Player::getplayer()->getRenderer().getForward()))
	{
		LizardBev = BEHAVIOUR_ATTACK;
	}
}

void Lizard::Retreat(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	if (!checkCollision(Buildings, Enemy))
	{
		if (this->allAABB[1]->pointtoAABB(Player::getplayer()->getRenderer().getPosition(), Player::getplayer()->getRenderer().getForward()))
		{
			gameobjrenderer_->setForward(-(this->gameobjrenderer_->getPosition() - Player::getplayer()->getRenderer().getPosition()).Normalized());
			gameobjrenderer_->translate(this->gameobjrenderer_->getForward(), 50 * dt);
			health_ += 2.5f;
		}
		else
		{
			if (health_ > (max_health_ * (3 / 4)))
			{
				LizardBev = BEHAVIOUR_IDLE;
			}
		}
	}
	else if (checkCollision(Buildings, Enemy))
	{
		gameobjrenderer_->setForward(-gameobjrenderer_->getRight());
		gameobjrenderer_->translate(gameobjrenderer_->getForward(), 50 * dt);
	}
}