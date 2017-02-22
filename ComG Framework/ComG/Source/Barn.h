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
	Barn(Vector3=(0,0,5));
	virtual ~Barn();
	void update(double dt) override;
	int get_Health();

};

#endif