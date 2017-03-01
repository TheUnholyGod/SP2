#include "Lizard.h"
#include "Randomizer.h"

Lizard::Lizard() : Enemy(2, "OBJ//Lizard.obj", "Image//LizardUV.tga", "Lizard", NORMAL, "Base", 100, 10, 150)
{
	float temp1 = 1000 - Randomizer::generate_range(1, 2000) + Player::getplayer()->getRenderer().getPosition().x;
	float temp2 = 0;
	float temp3 = 1000 - Randomizer::generate_range(1, 2000) + Player::getplayer()->getRenderer().getPosition().z;
	gameobjrenderer_->setPosition(Vector3(temp1, temp2, temp3));
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
	LizardBev = BEHAVIOUR_IDLE;
	isAttaacked = false;
	max_size_ = Randomizer::generate_range(1, 10);
	cooldown = 0;
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
	attacktime = (std::clock() - cooldown) / (int)CLOCKS_PER_SEC;
	if (!isAttaacked && attacktime > 1.5f)
	{
		if (!checkCollision(Buildings, Enemy))
		{
			if (this->allAABB[0]->AABBtoAABB(*Player::getplayer()->getAABB(0)))
			{
				Player::getplayer()->receivedamage(attack_);
				isAttaacked = true;
				cooldown = std::clock();
			}
			else if (!this->allAABB[0]->AABBtoAABB(*Player::getplayer()->getAABB(0)))
			{
				gameobjrenderer_->setForward((Player::getplayer()->getRenderer().getPosition() - this->gameobjrenderer_->getPosition()).Normalized());
				gameobjrenderer_->translate(this->gameobjrenderer_->getForward(), 25 * dt);
			}
		}
		else if (checkCollision(Buildings, Enemy))
		{
			gameobjrenderer_->setForward(-gameobjrenderer_->getRight());
			gameobjrenderer_->translate(gameobjrenderer_->getForward(), 25 * dt);
		}
	}
	else if(isAttaacked && attacktime < 1.5f)
	{
		gameobjrenderer_->translate(this->gameobjrenderer_->getForward(), 25 * dt);
		isAttaacked = false;
	}
	if (health_ < (max_health_ / 2))
	{
		LizardBev = BEHAVIOUR_RETREAT;
	}
}

void Lizard::Move(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	if (health_ / 100 < max_size_)
		health_ += (5 / 1.f) * dt;
	float scalar = health_ / 100.f;
	if (scalar < 1)
	{
		scalar = 1;
	}
	gameobjrenderer_->setScaling(scalar);
	allAABB[0]->resizeAABB(size[0] * scalar);
	allAABB[1]->resizeAABB(size[1] * scalar);
	if (this->allAABB[1]->AABBtoAABB(*Player::getplayer()->getAABB(0)))
	{
		isAttaacked = false;
		LizardBev = BEHAVIOUR_ATTACK;
	}
}

void Lizard::Retreat(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	if (!checkCollision(Buildings, Enemy))
	{
		if (this->allAABB[1]->pointtoAABB(Player::getplayer()->getRenderer().getPosition(), Player::getplayer()->getRenderer().getForward()))
		{
			try
			{
				gameobjrenderer_->setForward((this->gameobjrenderer_->getPosition() - Player::getplayer()->getRenderer().getPosition()).Normalized());
			}
			catch(DivideByZero)
			{
				gameobjrenderer_->translate(this->gameobjrenderer_->getForward(), 50 * dt);
			}
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