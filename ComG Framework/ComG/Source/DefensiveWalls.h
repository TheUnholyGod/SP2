#ifndef DEFENSIVEWALLS_H
#define DEFENSIVEWALLS_H

#include "Building.h"
#include <string>

class DefensiveWalls : public Building
{
protected:

	const std::string kName_;
	int health_;
	bool enter_;
public:
	DefensiveWalls(/*const std::string name, const int id, int health, BUILDINGTYPE, BUILDINGFUNCTION, bool enter*/);
	virtual ~DefensiveWalls();

	int get_Health();

};

#endif