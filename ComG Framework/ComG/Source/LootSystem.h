#ifndef LOOTSYSTEM_H
#define LOOTSYSTEM_H

#include "ItemDataBase.h"
#include "Randomizer.h"

int GenerateLoot()
{
	int r = rand() % 2;
	int key;
	if (r == 0)
	{
		key = Randomizer::generate_range(101, 105);
	}
	else
	{
		key = Randomizer::generate_range(201, 211);
	}
	std::cout << key << std::endl;
	return key;
}

#endif // !LOOTSYSTEM_H
