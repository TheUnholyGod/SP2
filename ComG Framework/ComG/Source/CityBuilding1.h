#ifndef _CITYBUILDING1_H
#define _CITYBUILDING1_H

#include "Building.h"
#include <string>

class CityBuilding1 : public Building
{
protected:

	const std::string kName_;
	std::string source_location_;
	int health_;
	bool enter_;
	bool moved;
public:
	CityBuilding1(Vector3 = (0, 0, 5), Vector3 = (1, 0, 0));
	virtual ~CityBuilding1();
	void update(double dt);
	int get_Health();
};

#endif