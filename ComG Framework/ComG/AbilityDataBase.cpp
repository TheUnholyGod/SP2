#include "AbilityDataBase.h"
#include "Source\Corrosive.h"
#include "Source\Radioactive.h"
#include "Source\Teleporting.h"
#include "Source\Burrowing.h"

AbilityDataBase* AbilityDataBase::Abilitydb_;

AbilityDataBase::AbilityDataBase()
{
	Ability* temp = new Corrosive();
	Abilitydatabase_[temp->getID()] = new Corrosive;
	delete temp;
	temp = new Burrow();
	Abilitydatabase_[temp->getID()] = new Burrow;
	delete temp;
	temp = new Teleporting();
	Abilitydatabase_[temp->getID()] = new Teleporting;
	delete temp;
	temp = new Radioactive();
	Abilitydatabase_[temp->getID()] = new Radioactive;
	delete temp;
}

AbilityDataBase::~AbilityDataBase()
{

}

AbilityDataBase* AbilityDataBase::getAbilityDB()
{
	if (!Abilitydb_)
	{
		Abilitydb_ = new AbilityDataBase;
	}
	return Abilitydb_;
}

Ability* AbilityDataBase::getAbility(int key)
{
	return Abilitydatabase_[key];
}

AbilityDataBase::adb& AbilityDataBase::getDataBase()
{
	return Abilitydatabase_;
}
