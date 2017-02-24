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
	FastTravelRoom(Vector3 = (0, 0, 5));
	virtual ~FastTravelRoom();

	int get_Health();

	static AABB* fastTravelling;
	virtual void update(double dt);
};

#endif