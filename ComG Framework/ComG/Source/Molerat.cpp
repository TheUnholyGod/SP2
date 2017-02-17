#include "Molerat.h"

Molerat::Molerat() : Enemy(1,"OBJ//MoleRat.obj" ,"Molerat", NORMAL, "Base", 100, 10, 4)
{
	goalreached = true;
}

Molerat::~Molerat()
{
}

void Molerat::Update(double dt)
{
	if (allAABB[1]->pointtoAABB(Player::getplayer()->getRenderer().getPosition()))
	{
		gameobjrenderer_->rotate((0, 1, 0), 20 * dt, (Player::getplayer()->getRenderer().getPosition() - gameobjrenderer_->getPosition()));
		gameobjrenderer_->translate(gameobjrenderer_->getForward(), 5 * dt);
		goalreached = true;
	}
	else
	{
		if (goalreached)
			pathfinding();
		gameobjrenderer_->translate(gameobjrenderer_->getForward(), 5 * dt);
		if(gameobjrenderer_->getPosition )
			goalreached = true;
	}
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
	std::cout << gameobjrenderer_->getForward() << std::endl;
}

void Molerat::pathfinding()
{
	newDIr = (((float)(rand() % 100)) / 100.f, 0, ((float)(rand() % 100)) / 100.f);
	goal = newDIr * 25;
	goalreached = false;
	gameobjrenderer_->setForward(newDIr);
}