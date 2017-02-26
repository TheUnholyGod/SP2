#include "DefenceTower.h"
#include "EnemyDataBase.h"
#include "Camera3.h"
#include "ItemFactory.h"

AABB* DefenceTower::aoe;
Vector3 DefenceTower::s_forward;
Vector3 DefenceTower::s_position;
bool DefenceTower::active = false;

DefenceTower::DefenceTower(Vector3 position, Vector3 forward) : Building(107, "Turret", "OBJ//Turret.obj", "Image//Turret_Texture.tga", 100, DEFENCE, false)
{
	gameobjrenderer_ = new Renderer(position, Vector3(1, 0, 0)/*, forward*/);
	gameobjrenderer_->setScaling(1);
	size.push_back(Vector3(10, 10, 10) * gameobjrenderer_->getScaling());
	aoe = new AABB(Vector3(10, 10, 10) * gameobjrenderer_->getScaling() * 10, gameobjrenderer_->getPosition());
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());

	defaultrecipe[ItemFactory::getItemFactory()->generateItem(202)] = 15; //Iron
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(203)] = 10; //Copper
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(204)] = 1; //Gold
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(211)] = 1; //Circuit Board

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
{
	for (auto i : enemies)
	{
		if (aoe->pointtoAABB(i->getRenderer().getPosition(), i->getRenderer().getForward()))
		{
			active = true;
			s_forward = (Vector3((s_position - i->getRenderer().getPosition()).Normalize().x, 0, (s_position - i->getRenderer().getPosition()).Normalize().z));
		}
	}
}