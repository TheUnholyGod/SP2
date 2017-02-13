#ifndef _ABILITY_H
#define _ABILITY_H

#include "GameObject.h"
#include <string>

class Ability : public GameObject
{
protected:
	const std::string kname_;
public:
	Ability(int, std::string);
	virtual ~Ability();
	const std::string getName() { return kname_; }
};

#endif