#ifndef WATERWELL_H
#define WATERWELL_H

#include "Building.h"
#include <string>

class WaterWell : public Building
{
protected:

	const std::string kName_;
	std::string source_location_;
	int health_;
	bool enter_;
public:
	WaterWell(/*const std::string name, const int id, int health, BUILDINGTYPE, BUILDINGFUNCTION, bool enter*/);
	virtual ~WaterWell();

	int get_Health();

};

#endif