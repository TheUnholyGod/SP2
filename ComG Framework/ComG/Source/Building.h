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
public:
	
	Building(const std::string name, const int id, int health, BUILDINGFUNCTION, bool enter);
	virtual ~Building();

	int get_Health();

};

#endif