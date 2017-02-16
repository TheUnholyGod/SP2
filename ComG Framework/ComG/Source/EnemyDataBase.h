#ifndef _ENEMYDATABASE_H
#define _ENEMYDATABASE_H

#include "Enemy.h"
#include <map>
#include <vector>

class EnemyDataBase
{
public:
	typedef std::map<int, Enemy*> edb;
private:
	edb enemydatabase_;
	EnemyDataBase();
	static EnemyDataBase* enemydb_;
	std::vector<int> IDlist;
public:
	~EnemyDataBase();
	static EnemyDataBase* getEnemyDB();
	Enemy* getEnemy(int key);
	edb& getDataBase();
	void init();
	std::vector<int> getIDList() { return IDlist; }
};

#endif