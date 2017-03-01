#include "RogueMech.h"
#include "Randomizer.h"
#include"Player.h"

RogueMech::RogueMech() : Enemy(5, "OBJ//MoleRat.obj", "Image//MoleratUV.tga", "RogueMech", NORMAL, "City", 100, 25, 5)
{
	float temp1 = 200 - Randomizer::generate_range(1, 500) + Player::getplayer()->getRenderer().getPosition().x;
	float temp2 = 0;
	float temp3 = 200 - Randomizer::generate_range(1, 500) + Player::getplayer()->getRenderer().getPosition().z;
	gameobjrenderer_->setPosition(Vector3(temp1, temp2, temp3));

}

RogueMech::~RogueMech()
{
}