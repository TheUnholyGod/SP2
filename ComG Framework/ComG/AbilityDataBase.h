#ifndef _ABILITYDATABASE_H
#define _ABILITYDATABASE_H

#include <map>
#include "Source\Ability.h"

class AbilityDataBase
{
public:
	typedef std::map<int, Ability*> adb;
private:
	adb Abilitydatabase_;
	AbilityDataBase();
	static AbilityDataBase* Abilitydb_;
public:
	~AbilityDataBase();
	static AbilityDataBase* getAbilityDB();
	Ability* getAbility(int key);
	adb& getDataBase();
};

#endif