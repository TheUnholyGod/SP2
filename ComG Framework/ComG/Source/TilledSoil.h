#ifndef TILLEDSOIL_H
#define TILLEDSOIL_H

#include "Building.h"
#include <string>

class TilledSoil : public Building
{
protected:

	const std::string kName_;
	std::string source_location_;
	int health_;
	bool enter_;
public:
	TilledSoil(/*const std::string name, const int id, int health, BUILDINGTYPE, BUILDINGFUNCTION, bool enter*/);
	virtual ~TilledSoil();

	int get_Health();

};

#endif