#include "Enemy.h"

Enemy::Enemy(int no, std::string source_location, std::string texture_location, std::string name, ENEMYTYPE type, std::string locval, float hpval, float defval, float attval) : GameObject(no, source_location, texture_location), kname_(name)
{
	max_health_ = health_;
	gameobjrenderer_ = new Renderer(Vector3(5, 0, 5), Vector3(0, 0, 1));
	AABB* temp = new AABB(Vector3(20,5,20), gameobjrenderer_->getPosition());
	allAABB.push_back(temp);
	AABB* temp2 = new AABB(Vector3(150, 150, 150), gameobjrenderer_->getPosition());
	allAABB.push_back(temp2);
}

Enemy::~Enemy()
{
}

bool Enemy::checkCollision(std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	bool move = false;
	bool move1 = false;
	bool move2 = false;
	for (auto &i : Buildings)
	{
		move1 = i->getAABB(0)->pointtoAABB(this->getRenderer().getPosition(), this->getRenderer().getForward());
		if (move1)
		{
			break;
		}
	}

	for (auto &i : Enemy)
	{
		if (i == this)
		{
			continue;
		}
		else
		{
			move2 = i->getAABB(0)->pointtoAABB(this->getRenderer().getPosition(),this->getRenderer().getForward());
			if (move2)
			{
				break;
			}
		}
	}

	if (move1 || move2)
		move = true;
	else
		move = false;

	return move;
}