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
	static recipe Barnrecipe;
public:
	Barn(Vector3 pos = (0, 0, 6), Vector3 forward = (10, 0, 0));
	virtual ~Barn();
	void update(double dt) override;
	int get_Health();
	std::string get_Resources();

	static recipe getRecipe() { return Barnrecipe; }
};

#endif