#ifndef OREMINES_H
#define OREMINES_H

#include "Building.h"
#include <string>

class OreMines : public Building
{
protected:

	const std::string kName_;
	std::string source_location_;
	int health_;
	bool enter_;
	bool cancollect;
	bool collected;

	std::clock_t collecttime;
	float Timer;

public:
	OreMines(Vector3 = (0, 0, 5), Vector3 = (1, 0, 0));
	virtual ~OreMines();

	int get_Health();
	virtual void update(double dt);
};

#endif