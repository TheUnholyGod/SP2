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
	TilledSoil(Vector3 = (0, 0, 5));
	virtual ~TilledSoil();

	int get_Health();

};

#endif