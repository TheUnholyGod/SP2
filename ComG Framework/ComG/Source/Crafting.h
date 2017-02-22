#ifndef CRAFTING_H
#define CRAFTING_H

#include "Building.h"
#include <string>

class Crafting : public Building
{
protected:

	const std::string kName_;
	std::string source_location_;
	int health_;
	bool enter_;
public:
	Crafting(Vector3 = (0, 0, 5));
	virtual ~Crafting();

	int get_Health();

};

#endif