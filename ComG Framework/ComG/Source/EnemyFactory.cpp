#include "EnemyFactory.h"
#include "EnemyDataBase.h"

EnemyFactory* EnemyFactory::EnemyF_;

EnemyFactory::EnemyFactory()
{
}

EnemyFactory::~EnemyFactory()
{
}

EnemyFactory* EnemyFactory::getEnemyFactory()
{
	if (!EnemyF_)
	{
		EnemyF_ = new EnemyFactory();
	}
	return EnemyF_;
}

Enemy* EnemyFactory::generateEnemy(int key)
{
	Enemy* temp = new Enemy(*(EnemyDataBase::getEnemyDB()->getEnemy(key)));
	return temp;
}