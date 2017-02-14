#ifndef BARN_H
#define BARN_H

#include "Building.h"
#include <string>

class Barn : public Building
{
protected:
	
	const std::string kName_;
	int health_;
	bool enter_;
public:
	Barn(/*const std::string name, const int id, int health, BUILDINGTYPE, BUILDINGFUNCTION, bool enter*/);
	virtual ~Barn();

	int get_Health();

};

#endif