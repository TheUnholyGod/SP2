#ifndef _ANT_HILL_H
#define _ANT_HILL_H

#include "Enemy.h"

class Ant_Hill : public Enemy
{
	std::vector<Enemy*> hills;
public:
<<<<<<< HEAD
	std::vector<Enemy*> hills;
=======
>>>>>>> 9cc91eaf00a66be98b1e65622275e8541082eee7
	Ant_Hill();
	~Ant_Hill();
	void Update(double dt) {}
	std::vector<Enemy*> getHills() { return hills; }
};

#endif