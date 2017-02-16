#include "Enemy.h"

Enemy::Enemy(int no,std::string source_location ,std::string name, ENEMYTYPE type, std::string locval, float hpval, float defval, float attval) : GameObject(no, source_location), kname_(name)
{
	gameobjrenderer_ = new Renderer(Vector3(5, 5, 5), Vector3(0, 0, 1));
	AABB* temp = new AABB(Vector3(5, 5, 5), gameobjrenderer_->getPosition());
	allAABB.push_back(temp);
	AABB* temp2 = new AABB(Vector3(20, 20, 20), gameobjrenderer_->getPosition());
	allAABB.push_back(temp2);
}

Enemy::~Enemy()
{
}