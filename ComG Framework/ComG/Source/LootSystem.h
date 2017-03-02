#ifndef LOOTSYSTEM_H
#define LOOTSYSTEM_H

#include "ItemDataBase.h"
#include "Randomizer.h"

namespace Loot
{
	const static int GenerateLoot()
	{
		int key;
		key = Randomizer::generate_range(101, 103);
		std::cout << key << std::endl;
		return key;
	}
}
#endif // !LOOTSYSTEM_H
