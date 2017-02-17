#include "GameObject.h"
#include "Player.h"

GameObject::GameObject(int no, std::string location_name, std::string texture_name) :kID_(no), source_location_(location_name), texture_location_(texture_name)
{
	
}


GameObject::~GameObject()
{
}
