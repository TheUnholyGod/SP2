#ifndef DEFENCETOWER_H
#define DEFENCETOWER_H

#include "Building.h"
#include <string>

class DefenceTower : public Building
{
protected:

	const std::string kName_;
	int health_;
	bool enter_;
public:
	DefenceTower(/*const std::string name, const int id, int health, BUILDINGTYPE, BUILDINGFUNCTION, bool enter*/);
	virtual ~DefenceTower();

	int get_Health();

};

#endif