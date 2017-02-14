#ifndef CRAFTING_H
#define CRAFTING_H

#include "Building.h"
#include <string>

class Crafting : public Building
{
protected:

	const std::string kName_;
	int health_;
	bool enter_;
public:
	Crafting(/*const std::string name, const int id, int health, BUILDINGTYPE, BUILDINGFUNCTION, bool enter*/);
	virtual ~Crafting();

	int get_Health();

};

#endif