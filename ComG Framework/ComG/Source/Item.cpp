#include "Item.h"
#include "Player.h"

Item::Item(int no, std::string name, std::string source_location, std::string texture_location) :GameObject(no, source_location, texture_location), kname_(name), source_location_(source_location), texture_location_(texture_location)
{
	pickedup = false;
	gameobjrenderer_ = new Renderer(Player::getplayer()->getRenderer());
	gameobjrenderer_->setPosition((Player::getplayer()->getRenderer().getPosition() + Vector3((0, 1, 0) * 20) + Player::getplayer()->getRenderer().getForward() * 5 + Player::getplayer()->getRenderer().getRight() * 2));
	gameobjrenderer_->setForward(Player::getplayer()->getRenderer().getForward());
}

void Item::update()
{
	pickedup = true;
	
}

bool Item::getpickedup()
{
	bool pick;
	pick = pickedup;
	return pick;
}

Item::~Item() {}