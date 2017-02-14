#ifndef TROPHYROOM_H
#define TROPHYROOM_H

#include "Building.h"
#include <string>

class TrophyRoom : public Building
{
protected:

	const std::string kName_;
	int health_;
	bool enter_;
public:
	TrophyRoom(/*const std::string name, const int id, int health, BUILDINGTYPE, BUILDINGFUNCTION, bool enter*/);
	virtual ~TrophyRoom();

	int get_Health();

};

#endif