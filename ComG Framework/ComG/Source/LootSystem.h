#ifndef LOOTSYSTEM_H
#define LOOTSYSTEM_H

#include "ItemDataBase.h"
#include "Randomizer.h"

int GenerateLoot()
{
	int key = Randomizer::generate_range(101, 103);
	std::cout << key << std::endl;
	return key;
}

#endif // !LOOTSYSTEM_H
