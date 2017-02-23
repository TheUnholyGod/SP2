#ifndef _RANDOMIZER_H
#define _RANDOMIZER_H

#include <stdlib.h>
#include <time.h>

namespace Randomizer
{
	int generate_range(unsigned from, unsigned to)
	{
		int returnno = (rand() % (to - from)) + from;
		if (returnno > to)
		{
			returnno = to;
		}
		else if (returnno < from)
		{
			returnno = from;
		}
		return returnno;
	}
};

#endif