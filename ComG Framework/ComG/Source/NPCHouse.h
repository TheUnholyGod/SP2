#ifndef NPCHouse_H
#define NPCHouse_H

#include "Building.h"
#include <string>

class NPCHouse : public Building
{
protected:

	const std::string kName_;
	int health_;
	bool enter_;
public:
	NPCHouse(/*const std::string name, const int id, int health, BUILDINGTYPE, BUILDINGFUNCTION, bool enter*/);
	virtual ~NPCHouse();

	int get_Health();

};

#endif