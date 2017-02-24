#ifndef _RANDOMIZER_H
#define _RANDOMIZER_H

#include <stdlib.h>
#include <time.h>

namespace Randomizer
{
	static int generate_range(unsigned from, unsigned to)
	{
		int returnno = (rand() % (to - from)) + from;
		if (returnno > (int)to)
		{
			returnno = (int)to;
		}
		else if (returnno < (int)from)
		{
			returnno = (int)from;
		}
		return returnno;
	}
};

#endif