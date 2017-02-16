#include "Item.h"
#include "Player.h"

<<<<<<< HEAD
Item::Item(int no,std::string source_location ,std::string name) :GameObject(no,source_location), kname_(name) 
{
	gameobjrenderer_ = new Renderer(Player::getplayer()->getRenderer());
	gameobjrenderer_->translate(Vector3(10, 1, 0),1);
	gameobjrenderer_->rotate(Vector3(0, 1, 0), 1, -90);
}
=======
Item::Item(int no, std::string name, std::string source) :GameObject(no, source), kname_(name) {}
>>>>>>> df0b89ed37dcdc725ae0ed602e193209e647493d

Item::~Item() {}