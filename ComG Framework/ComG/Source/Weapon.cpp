#include "Weapon.h"

Weapon::Weapon(int id, std::string name, std::string source_location, std::string texture_location, WEAPONTYPE type, float atk, float dura) : Item(id, name, source_location, texture_location), kType_(type), kattack_(atk), kdurability_(dura)
{

}

Weapon::~Weapon()
{

}