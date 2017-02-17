#ifndef BUILDING_H
#define BUILDING_H

#include "GameObject.h"
#include <string>

class Building : public GameObject
{
protected:
	enum BUILDINGFUNCTION{
		RESOURCE,
		DEFENCE,
		NORMAL,
	}FUNCTION;

	const std::string kName_;
	int health_;
	bool enter_;
	std::string source_location_;
public:
	
	Building(const int id, const std::string name, std::string source_, int health, BUILDINGFUNCTION, bool enter);
	virtual ~Building();

	virtual void update(double dt){}
	int get_Health();
	std::string getName(){ return kName_; }
};

#endif