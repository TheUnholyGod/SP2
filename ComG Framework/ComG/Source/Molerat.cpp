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
		gameobjrenderer_->rotate((0, 1, 0), 20 * dt, Player::getplayer()->getRenderer().getPosition().Dot(-gameobjrenderer_->getPosition()));
		gameobjrenderer_->translate(gameobjrenderer_->getForward(), 5 * dt);
		goalreached = true;
	}
	else
	{
		if (goalreached)
			pathfinding();
		if (gameobjrenderer_->getPosition() != goal)
			gameobjrenderer_->translate(gameobjrenderer_->getForward(), 25 * dt);
		else
			goalreached = true;
	}
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
	std::cout << gameobjrenderer_->getPosition() << std::endl;
}

void Molerat::pathfinding()
{
	newDIr = ((float)(rand() % 100) / 100.f, (float)(rand() % 100) / 100.f, (float)(rand() % 100) / 100.f);
	goal = newDIr * 25;
	goalreached = false;
	gameobjrenderer_->setForward(newDIr);
}