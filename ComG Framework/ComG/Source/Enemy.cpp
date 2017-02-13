#include "Enemy.h"

Enemy::Enemy(int no, std::string name, ENEMYTYPE type, std::string locval, float hpval, float defval, float attval) : GameObject(no), kname_(name) 
{
}

Enemy::~Enemy()
{
}