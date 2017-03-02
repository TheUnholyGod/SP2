#ifndef BUILDING_H
#define BUILDING_H

#include "GameObject.h"
#include "Item.h"
#include <string>
#include <map>

class Building : public GameObject
{
protected:
	enum BUILDINGFUNCTION{
		RESOURCE,
		DEFENCE,
		NORMAL,
	}FUNCTION;
	typedef std::map<Item*, int> recipe;
	const std::string kName_;
	int health_;
	bool enter_;
	bool deletethis_;
	std::string source_location_;
	recipe defaultrecipe;
	float collecttime;
	bool start;
	float Timer;
public:
	
	Building(const int id, const std::string name, std::string source_, std::string texture_, int health, BUILDINGFUNCTION, bool enter);
	virtual ~Building();
	virtual void update(double dt) {}

	int get_Health();
	const std::string getName() { return kName_; }
	virtual recipe getRecipe() { return defaultrecipe; }
	void takeDamage(int dmg) { health_ -= dmg; }
	float getcollecttime() { return collecttime;  };
	void collected() {
		start = true;
		Timer = std::clock();
	};
	void setstart()
	{
		start = true;
	}
	void setinit()
	{
		collecttime = 60;
		Timer = 0;
		start = false;
	}
};

#endif