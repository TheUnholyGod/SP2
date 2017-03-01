#include "Ant.h"
#include "Randomizer.h"

Ant::Ant() : Enemy(13, "OBJ//Ant.obj", "Image//Ant_Texture.tga", "AntHill", BOSS, "Base", 150, 20, 10)
{
	//my_hill = Ant_Hill::hills[Randomizer::generate_range(0,sizeof(Ant_Hill::hills))];
<<<<<<< HEAD
	float a_X = (my_hill->getRenderer().getPosition().x * my_hill->getRenderer().getScaling()) - Randomizer::generate_range((my_hill->getRenderer().getPosition().x),
=======
	/*float a_X = (my_hill->getRenderer().getPosition().x * my_hill->getRenderer().getScaling()) - Randomizer::generate_range((my_hill->getRenderer().getPosition().x),
>>>>>>> 9cc91eaf00a66be98b1e65622275e8541082eee7
		                                    (my_hill->getRenderer().getPosition().x * my_hill->getRenderer().getScaling()));
	float a_Z = (my_hill->getRenderer().getPosition().z * my_hill->getRenderer().getScaling()) - Randomizer::generate_range((my_hill->getRenderer().getPosition().z),
		(my_hill->getRenderer().getPosition().z * my_hill->getRenderer().getScaling()));*/
	gameobjrenderer_->setPosition(Vector3(10, 0, 10));
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
}
Ant::Ant(Ant_Hill* the_hills) : Enemy(13, "OBJ//Ant.obj", "Image//Ant_Texture.tga", "AntHill", BOSS, "Base", 150, 20, 10)
{
	my_hill = the_hills;
	my_hill->getHills().push_back(this);
	float a_X = (my_hill->getRenderer().getPosition().x * my_hill->getRenderer().getScaling()) - Randomizer::generate_range((my_hill->getRenderer().getPosition().x),
		(my_hill->getRenderer().getPosition().x * my_hill->getRenderer().getScaling()));
	float a_Z = (my_hill->getRenderer().getPosition().z * my_hill->getRenderer().getScaling()) - Randomizer::generate_range((my_hill->getRenderer().getPosition().z),
		(my_hill->getRenderer().getPosition().z * my_hill->getRenderer().getScaling()));
	gameobjrenderer_->setPosition(Vector3(a_X, 0, a_Z));
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
}

Ant::~Ant()
{
}

void Ant::Update(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	switch (AntBev)
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

void Ant::pathfinding()
{
	float temp = (float)Randomizer::generate_range(1, 360);
	Mtx44 rotation;
	rotation.SetToRotation(temp, 0, 1, 0);
	newDIr = rotation * newDIr;
	goal = newDIr;
	goalreached = false;
	gameobjrenderer_->setForward(newDIr);
}

void Ant::Attack(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	std::list<Building*> temp;
	if (!this->checkCollision(temp, Enemy))
	{
		if (targeted->getAABB(0)->AABBtoAABB(*this->getAABB(0)))
		{
			targeted->takeDamage(attack_);
		}
		else
		{
			gameobjrenderer_->setForward((this->gameobjrenderer_->getPosition() - targeted->getRenderer().getPosition()).Normalized());
			gameobjrenderer_->translate(gameobjrenderer_->getForward(), 50 * dt);
		}
	}
	else if (this->allAABB[1]->pointtoAABB(Player::getplayer()->getRenderer().getPosition(), Player::getplayer()->getRenderer().getForward()))
	{
		AntBev = BEHAVIOUR_PLAYER;
	}
}

void Ant::Move(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
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
		AntBev = BEHAVIOUR_PLAYER;
	}
	for (auto &i : Buildings)
	{
		if (this->allAABB[0]->AABBtoAABB(*i->getAABB(0)))
		{
			targeted = i;
			AntBev = BEHAVIOUR_ATTACK;
			break;
		}
	}
}

void Ant::PlayerInRange(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
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
		AntBev = BEHAVIOUR_IDLE;
	}
}