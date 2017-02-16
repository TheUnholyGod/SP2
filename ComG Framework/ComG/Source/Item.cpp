#include "Item.h"
#include "Player.h"

Item::Item(int no, std::string name, std::string source_location) :GameObject(no, source_location), kname_(name)
{
	gameobjrenderer_ = new Renderer(Player::getplayer()->getRenderer());
	gameobjrenderer_->setPosition((Player::getplayer()->getRenderer().getPosition() + ((0, 1, 0) * 2) + Player::getplayer()->getRenderer().getForward() * 5 + Player::getplayer()->getRenderer().getRight() * 2));
	gameobjrenderer_->setForward(Player::getplayer()->getRenderer().getForward());
}

Item::~Item() {}