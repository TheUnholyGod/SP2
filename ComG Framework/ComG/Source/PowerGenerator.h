#ifndef POWERGENERATOR_H
#define POWERGENERATOR_H

#include "Building.h"
#include <string>

class PowerGenerator : public Building
{
protected:

	const std::string kName_;
	int health_;
	bool enter_;
public:
	PowerGenerator(/*const std::string name, const int id, int health, BUILDINGTYPE, BUILDINGFUNCTION, bool enter*/);
	virtual ~PowerGenerator();

	int get_Health();

};

#endif