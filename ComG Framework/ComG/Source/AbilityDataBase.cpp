#include "AbilityDataBase.h"
#include "Corrosive.h"
#include "Radioactive.h"
#include "Teleporting.h"
#include "Burrowing.h"

AbilityDataBase* AbilityDataBase::Abilitydb_;

AbilityDataBase::AbilityDataBase()
{
	Ability* temp = new Corrosive();
	Abilitydatabase_[temp->getID()] = new Corrosive;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Burrow();
	Abilitydatabase_[temp->getID()] = new Burrow;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Teleporting();
	Abilitydatabase_[temp->getID()] = new Teleporting;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Radioactive();
	Abilitydatabase_[temp->getID()] = new Radioactive;
	IDlist.push_back(temp->getID());
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
