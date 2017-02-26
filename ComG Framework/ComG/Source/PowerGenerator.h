#ifndef POWERGENERATOR_H
#define POWERGENERATOR_H

#include "Building.h"
#include <string>

class PowerGenerator : public Building
{
protected:

	const std::string kName_;
	std::string source_location_;
	int health_;
	bool enter_;
public:
	PowerGenerator(Vector3 = (0, 0, 5), Vector3 = (1, 0, 0));
	virtual ~PowerGenerator();

	int get_Health();
};

#endif