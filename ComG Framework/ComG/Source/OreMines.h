#ifndef OREMINES_H
#define OREMINES_H

#include "Building.h"
#include <string>

class OreMines : public Building
{
protected:

	const std::string kName_;
	int health_;
	bool enter_;
public:
	OreMines(/*const std::string name, const int id, int health, BUILDINGTYPE, BUILDINGFUNCTION, bool enter*/);
	virtual ~OreMines();

	int get_Health();

};

#endif