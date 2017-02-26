#ifndef NPCHouse_H
#define NPCHouse_H

#include "Building.h"
#include <string>

class NPCHouse : public Building
{
protected:

	const std::string kName_;
	std::string source_location_;
	int health_;
	bool enter_;
public:
	NPCHouse(Vector3 = (0, 0, 5), Vector3 = (1, 0, 0));
	virtual ~NPCHouse();

	int get_Health();
};

#endif