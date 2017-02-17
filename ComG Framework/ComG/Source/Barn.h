#ifndef BARN_H
#define BARN_H

#include "Building.h"
#include "Player.h"
#include <string>

class Barn : public Building
{
protected:
	
	const std::string kName_;
	std::string source_location_;
	int health_;
	bool enter_;
public:
	Barn(/*const std::string name, const int id, int health, BUILDINGTYPE, BUILDINGFUNCTION, bool enter*/);
	virtual ~Barn();
	void update(double dt);
	int get_Health();

};

#endif