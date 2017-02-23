#include "DefenceTower.h"
#include "EnemyDataBase.h"
#include "Camera3.h"

AABB* DefenceTower::aoe;
std::list<Vector3> DefenceTower::enemiesInRange;
Vector3 DefenceTower::s_forward;
Vector3 DefenceTower::s_position;

DefenceTower::DefenceTower(Vector3 position) : Building(107, "Turret", "OBJ//Turret.obj", "Image//Turret_Texture.tga", 100, DEFENCE, false) 
{
	gameobjrenderer_ = new Renderer(position, Vector3(1, 0, 0));
	gameobjrenderer_->setScaling(1);
	size.push_back(Vector3(10, 10, 10) * gameobjrenderer_->getScaling());
	aoe = new AABB(Vector3(10, 10, 10) * gameobjrenderer_->getScaling() * 3, gameobjrenderer_->getPosition());
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	s_position = GameObject::gameobjrenderer_->getPosition();
	s_forward = GameObject::gameobjrenderer_->getForward();
}

DefenceTower::~DefenceTower()
{

}

int DefenceTower::get_Health(){ return health_; }

void DefenceTower::update(double dt)
{
	GameObject::gameobjrenderer_->setForward(s_forward);
}

void DefenceTower::turretTargetUpdate(std::vector<Enemy*> enemies)
{/*
	for (auto i : enemies)
	{
		if (aoe->AABBtoAABB(i->getAABB))
		{
			enemiesInRange.push_back(i->getRenderer().getPosition());
		}
		for (auto u : enemiesInRange)
		{
			if (u == i->getRenderer().getPosition())
			{
				if (!(aoe->AABBtoAABB(i->getAABB)))
				{
					enemiesInRange.pop_front();
				}
			}
		}
		std::cout << "enemies[i]: " << i->getRenderer().getPosition() << std::endl;
	}
	s_forward = (Vector3((s_position - enemiesInRange.front()).Normalize().x, 0, (s_position - enemiesInRange.front()).Normalize().z));*/
}