#include "Enemy.h"

Enemy::Enemy(int no,std::string source_location ,std::string name, ENEMYTYPE type, std::string locval, float hpval, float defval, float attval) : GameObject(no, source_location), kname_(name)
{
}

Enemy::~Enemy()
{
}