#ifndef DEFENCETOWER_H
#define DEFENCETOWER_H

#include "Building.h"
#include <string>

class DefenceTower : public Building
{
protected:
	const std::string kName_;
	std::string source_location_;
	int health_;
	bool enter_;
public:
	DefenceTower(Vector3=(0,0,5));
	virtual ~DefenceTower();

	int get_Health();

	virtual void update(double dt);
};

#endif