#include "EnemyDataBase.h"
#include "Source\Acrid_Plant.h"
#include "Source\Ant_Hill.h"
#include "Source\Centipede.h"
#include "Source\CyborgMutt.h"
#include "Source\Deer.h"
#include "Source\Drone.h"
#include "Source\Goat.h"
#include "Source\Lizard.h"
#include "Source\Molerat.h"
#include "Source\PatrolBot.h"
#include "Source\RogueMech.h"
#include "Source\Scarecrow_Mech.h"
#include "Source\Wildboar.h"

EnemyDataBase* EnemyDataBase::enemydb_;

EnemyDataBase::EnemyDataBase()
{
	Enemy* temp = new Acrid_Plant;
	enemydatabase_[temp->getID()] = new Acrid_Plant;
	delete temp;
	temp = new Ant_Hill;
	enemydatabase_[temp->getID()] = new Ant_Hill;
	delete temp;
	temp = new Centipede;
	enemydatabase_[temp->getID()] = new Centipede;
	delete temp;
	temp = new CyborgMutt;
	enemydatabase_[temp->getID()] = new CyborgMutt;
	delete temp;
	temp = new Deer;
	enemydatabase_[temp->getID()] = new Deer;
	delete temp;
	temp = new Drone;
	enemydatabase_[temp->getID()] = new Drone;
	delete temp;
	temp = new Goat;
	enemydatabase_[temp->getID()] = new Goat;
	delete temp;
	temp = new Lizard;
	enemydatabase_[temp->getID()] = new Lizard;
	delete temp;
	temp = new Molerat;
	enemydatabase_[temp->getID()] = new Molerat;
	delete temp;
	temp = new PatrolBot;
	enemydatabase_[temp->getID()] = new PatrolBot;
	delete temp;
	temp = new RogueMech;
	enemydatabase_[temp->getID()] = new RogueMech;
	delete temp;
	temp = new Scarecrow_Mech;
	enemydatabase_[temp->getID()] = new Scarecrow_Mech;
	delete temp;
	temp = new WildBoar;
	enemydatabase_[temp->getID()] = new WildBoar;
	delete temp;
}


EnemyDataBase::~EnemyDataBase()
{
	enemydatabase_.erase(enemydatabase_.begin(), enemydatabase_.end());
}

EnemyDataBase* EnemyDataBase::getEnemyDB()
{
	if (!enemydb_)
	{
		enemydb_ = new EnemyDataBase;
	}
	return enemydb_;
}

Enemy* EnemyDataBase::getEnemy(int key)
{
	return enemydatabase_[key];
}

EnemyDataBase::edb& EnemyDataBase::getDataBase()
{
	return enemydatabase_;
}