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
public:
	OreMines(Vector3 = (0, 0, 5));
	virtual ~OreMines();

	int get_Health();

};

#endif