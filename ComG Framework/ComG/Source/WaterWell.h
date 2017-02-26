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
	WaterWell(Vector3 = (0, 0, 5), Vector3 = (1, 0, 0));
	virtual ~WaterWell();

	int get_Health();
};

#endif