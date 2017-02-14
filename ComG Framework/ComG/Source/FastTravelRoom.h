#ifndef FASTTRAVELROOM_H
#define FASTTRAVELROOM_H

#include "Building.h"
#include <string>

class FastTravelRoom : public Building
{
protected:

	const std::string kName_;
	int health_;
	bool enter_;
public:
	FastTravelRoom(/*const std::string name, const int id, int health, BUILDINGTYPE, BUILDINGFUNCTION, bool enter*/);
	virtual ~FastTravelRoom();

	int get_Health();

};

#endif