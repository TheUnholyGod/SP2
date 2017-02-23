#include "DefenceTower.h"
#include "EnemyDataBase.h"
#include "Camera3.h"

AABB* DefenceTower::aoe;
std::list<Enemy*> DefenceTower::enemiesInRange;
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
int ahhhhhh = 0;
void DefenceTower::turretTargetUpdate(std::vector<Enemy*> enemies)
{/*

	for (auto i : enemies)
	{
		if (aoe->pointtoAABB(i->getRenderer().getPosition(), i->getRenderer().getForward()))
		{
			std::cout << "ENEMIMES SPOOTTTED!!!!!!!"<< ++ahhhhhh << std::endl;
			enemiesInRange.push_back(i);
		}
		if (enemiesInRange.size() > 0){
			for (auto &u : enemiesInRange)
			{
				if (u == i)
				{
					if (!(aoe->pointtoAABB(i->getRenderer().getPosition(), i->getRenderer().getForward())))
					{
						enemiesInRange.pop_front();
					}
					else{
						break;
					}
				}
				else{
					break;
				}
			}
		}
	}
	if (enemiesInRange.size() > 0)
		s_forward = (Vector3((s_position - enemiesInRange.front()->getRenderer().getPosition()).Normalize().x, 0, (s_position - enemiesInRange.front()->getRenderer().getPosition()).Normalize().z));
	else
		s_forward = (1, 0, 0);*/
}