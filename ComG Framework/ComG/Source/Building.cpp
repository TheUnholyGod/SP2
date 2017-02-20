#include "Building.h"

Building::Building(int id, const std::string name, std::string source_, std::string texture_, int health, BUILDINGFUNCTION function, bool enter) :
								GameObject(id,source_,texture_), kName_(name), health_(health), FUNCTION(function), enter_(enter)
{
	//gameobjrenderer_ = new Renderer(Vector3(5, 5, 5), Vector3(1, 0, 0));
	//gameobjrenderer_->setPosition(Vector3(Player::getplayer()->getRenderer().getPosition().x, 0, Player::getplayer()->getRenderer().getPosition().z));
	/*AABB* temp = new AABB(Vector3(Player::getplayer()->getRenderer().getPosition()), gameobjrenderer_->getPosition());
	allAABB.push_back(temp);*/
}
Building::~Building(){}
int Building::get_Health(){ return health_; }