#ifndef _ENEMYFACTORY_H
#define _ENEMYFACTORY_H

#include "Source\Enemy.h"

class EnemyFactory
{
private:
	static EnemyFactory* EnemyF_;
	EnemyFactory();
public:
	~EnemyFactory();
	static EnemyFactory* getEnemyFactory();
	static Enemy* generateEnemy(int key);
};

#endif