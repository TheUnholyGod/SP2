#include "GameObject.h"
#include "Player.h"

GameObject::GameObject(int no, std::string location_name) :kID_(no), source_location_(location_name)
{
	
}


GameObject::~GameObject()
{
}
