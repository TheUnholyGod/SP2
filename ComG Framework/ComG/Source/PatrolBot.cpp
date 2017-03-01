#include "PatrolBot.h"
#include "Randomizer.h"
#include"Player.h"

PatrolBot::PatrolBot() : Enemy(6, "OBJ//MoleRat.obj", "Image//MoleratUV.tga", "PatrolBot", NORMAL, "City", 100, 10, 6)
{
	float temp1 = 200 - Randomizer::generate_range(1, 500) + Player::getplayer()->getRenderer().getPosition().x;
	float temp2 = 0;
	float temp3 = 200 - Randomizer::generate_range(1, 500) + Player::getplayer()->getRenderer().getPosition().z;
	gameobjrenderer_->setPosition(Vector3(temp1, temp2, temp3));

}

PatrolBot::~PatrolBot()
{
}