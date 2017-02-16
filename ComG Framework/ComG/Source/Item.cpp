#include "Item.h"
#include "Player.h"

Item::Item(int no, std::string name, std::string source) : GameObject(no, source), kname_(name) 
{
	gameobjrenderer_ = new Renderer(Player::getplayer()->getRenderer());
	gameobjrenderer_->translate(Vector3(10, 1, 0),1);
	gameobjrenderer_->rotate(Vector3(0, 1, 0), 1, -90);
}

Item::~Item() {}