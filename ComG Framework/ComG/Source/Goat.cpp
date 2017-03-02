#include "Goat.h"
#include "Randomizer.h"

Goat::Goat() : Enemy(8, "OBJ//Goat.obj", "Image//GoatUV.tga", "Goat", NORMAL, "Forest", 100, 5, 20)
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
	Iwait = std::clock();
	ITime = 0;
	ignoreothers = false;
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
	case BEHAVIOUR_RUN:
		Run(dt, Buildings, Enemy);
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

void Goat::Run(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{		
	if (!this->checkCollision(Buildings, Enemy) && ignoreothers == false)
	{
		gameobjrenderer_->setForward((this->gameobjrenderer_->getPosition() - Player::getplayer()->getRenderer().getPosition()).Normalized());
		gameobjrenderer_->translate(this->gameobjrenderer_->getForward(), 50 * dt);
	}
	else if (this->checkCollision(Buildings, Enemy) && ignoreothers == false)
	{
		gameobjrenderer_->setForward(-gameobjrenderer_->getRight());
		gameobjrenderer_->translate(this->gameobjrenderer_->getForward(), 50 * dt);
		ignoreothers = true;
	}

	if (ignoreothers == true)
	{
		gameobjrenderer_->setForward((-gameobjrenderer_->getPosition() + Player::getplayer()->getRenderer().getPosition()).Normalized());
		gameobjrenderer_->translate(this->gameobjrenderer_->getForward(), 80 * dt);

		if (this->allAABB[0]->AABBtoAABB(*Player::getplayer()->getAABB(0)))
		{
			Player::getplayer()->receivedamage(attack_);
			this->takeDamage(100);
		}
	}

	if (!this->allAABB[1]->pointtoAABB(Player::getplayer()->getRenderer().getPosition(), Player::getplayer()->getRenderer().getForward()) && ignoreothers == false)
	{
		GoatBev = BEHAVIOUR_IDLE;
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
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
	if (this->allAABB[1]->pointtoAABB(Player::getplayer()->getRenderer().getPosition(), Player::getplayer()->getRenderer().getForward()))
	{
		GoatBev = BEHAVIOUR_RUN;
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
}