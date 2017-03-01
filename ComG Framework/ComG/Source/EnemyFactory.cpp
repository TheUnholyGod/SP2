#include "EnemyFactory.h"
#include "EnemyDataBase.h"
#include "Acrid_Plant.h"
#include "Ant_Hill.h"
#include "Ant.h"
#include "Centipede.h"
#include "CyborgMutt.h"
#include "Deer.h"
#include "Drone.h"
#include "Goat.h"
#include "Lizard.h"
#include "Molerat.h"
#include "PatrolBot.h"
#include "RogueMech.h"
#include "Scarecrow_Mech.h"
#include "Wildboar.h"

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
	Enemy* temp = nullptr;
	std::vector<int> tempID(EnemyDataBase::getEnemyDB()->getIDList());
	if (key == tempID[0])
		temp = new Acrid_Plant;
	else if (key == tempID[1])
		temp = new Ant_Hill;
	else if (key == tempID[2])
		temp = new Centipede;
	else if (key == tempID[3])
		temp = new CyborgMutt;
	else if (key == tempID[4])
		temp = new Deer;
	else if (key == tempID[5])
		temp = new Drone;
	else if (key == tempID[6])
		temp = new Goat;
	else if (key == tempID[7])
		temp = new Lizard;
	else if (key == tempID[8])
		temp = new Molerat;
	else if (key == tempID[9])
		temp = new PatrolBot;
	else if (key == tempID[10])
		temp = new RogueMech;
	else if (key == tempID[11])
		temp = new Scarecrow_Mech;
	else if (key == tempID[12])
		temp = new WildBoar;
	else if (key == tempID[13])
		temp = new Ant;

	return temp;
}