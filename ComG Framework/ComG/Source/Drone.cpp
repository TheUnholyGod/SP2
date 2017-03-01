#include "Drone.h"
#include "Player.h"

Drone::Drone() : Enemy(3, "OBJ//Drone01.obj", "Image//Drone01UV.tga", "Drone", NORMAL, "City", 100, 5, 4)
{
	float temp1 = 250 - Randomizer::generate_range(1, 500) + Player::getplayer()->getRenderer().getPosition().x;
	float temp2 = 4;
	float temp3 = 250 - Randomizer::generate_range(1, 500) + Player::getplayer()->getRenderer().getPosition().z;
	this->gameobjrenderer_->setPosition(Vector3(temp1, temp2, temp3));

	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());

	newForward = Vector3(1, 0, 0);
	elapsedTime = 0.0f;
}

Drone::~Drone()
{
}

void Drone::Update(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	elapsedTime = (std::clock() - start) / (int)CLOCKS_PER_SEC;

	Move(dt, Buildings, Enemy);
}

void Drone::Pathfind()
{
	float temp = (float)Randomizer::generate_range(1, 360);
	Mtx44 rotation;
	rotation.SetToRotation(temp, 0, 1, 0);

	newForward = rotation * newForward;
	this->gameobjrenderer_->setForward(newForward);
}

void Drone::Move(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	dronePos = this->gameobjrenderer_->getPosition();
	dronePos.y = 2;
	charPos = Player::getplayer()->getRenderer().getPosition();

	if (elapsedTime < 5)
	{
		if (this->checkCollision(Buildings, Enemy))//Check if colliding with building or enemy
		{
			Pathfind();
			this->gameobjrenderer_->translate(gameobjrenderer_->getForward(), 25 * dt);
		}
		else if (!this->checkCollision(Buildings, Enemy))//Put this last
		{
			if ((dronePos - charPos).Length() > 80 && (dronePos - charPos).Length() < 120)//Player within detection range
			{
				newForward = -(dronePos - charPos);
				this->gameobjrenderer_->setForward(newForward);
				this->gameobjrenderer_->translate(gameobjrenderer_->getForward(), dt);
				elapsedTime = 0;
			}
			else if ((dronePos - charPos).Length() > 2 && (dronePos - charPos).Length() < 81)//Player within shooting range
			{
				newForward = -(dronePos - charPos);
				this->gameobjrenderer_->setForward(newForward);
				elapsedTime = 0;
			}
			else
			{
				this->gameobjrenderer_->translate(gameobjrenderer_->getForward(), 25 * dt);
			}
		}
	}
	if (elapsedTime > 5)
	{
		Pathfind();
		start = std::clock();
	}
	
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
}

void Drone::ComeBack()
{
	if (gameobjrenderer_->getPosition().x > 2000 || gameobjrenderer_->getPosition().z > 2000)
	{
		gameobjrenderer_->setPosition((float)Randomizer::generate_range(1, 500));
	}
}