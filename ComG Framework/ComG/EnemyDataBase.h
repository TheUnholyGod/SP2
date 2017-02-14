#ifndef _ENEMYDATABASE_H
#define _ENEMYDATABASE_H

#include "Source\Enemy.h"
#include <map>

class EnemyDataBase
{
public:
	typedef std::map<int, Enemy*> edb;
private:
	edb enemydatabase_;
	EnemyDataBase();
	static EnemyDataBase* enemydb_;
public:
	~EnemyDataBase();
	static EnemyDataBase* getEnemyDB();
	Enemy* getEnemy(int key);
	edb& getDataBase();
};

#endif