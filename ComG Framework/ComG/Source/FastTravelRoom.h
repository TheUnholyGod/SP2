#ifndef FASTTRAVELROOM_H
#define FASTTRAVELROOM_H

#include "Building.h"
#include <string>

class FastTravelRoom : public Building
{
protected:

	const std::string kName_;
	std::string source_location_;
	int health_;
	bool enter_;
public:
	FastTravelRoom(/*const int id, const std::string name, std::string source, int health, BUILDINGTYPE, BUILDINGFUNCTION, bool enter*/);
	virtual ~FastTravelRoom();

	int get_Health();

};

#endif