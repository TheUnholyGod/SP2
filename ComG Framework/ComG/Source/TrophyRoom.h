#ifndef TROPHYROOM_H
#define TROPHYROOM_H

#include "Building.h"
#include <string>

class TrophyRoom : public Building
{
protected:

	const std::string kName_;
	std::string source_location_;
	int health_;
	bool enter_;
public:
	TrophyRoom(Vector3=(0, 0, 5));
	virtual ~TrophyRoom();

	int get_Health();

};

#endif