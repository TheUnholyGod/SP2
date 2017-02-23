#include "Lizard.h"

Lizard::Lizard() : Enemy(2, "OBJ//Lizard.obj", "", "Lizard", NORMAL, "Base", 100, 10, 2)
{
}

Lizard::~Lizard()
{
}

void Lizard::Update(double dt)
{
	if (allAABB[1]->AABBtoAABB(*Player::getplayer()->getAABB()))
	{
		gameobjrenderer_->rotate((0, 1, 0), 20 * dt, Player::getplayer()->getRenderer().getPosition().Dot(gameobjrenderer_->getForward()));
		gameobjrenderer_->translate(gameobjrenderer_->getForward(), 25 * dt);
	}
}