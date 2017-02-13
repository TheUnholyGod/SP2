#include "Weapon.h"

Weapon::Weapon(std::string name, WEAPONTYPE type, float atk, float dura) : Item(1,name), kType_(type), kattack_(atk), kdurability_(dura)
{

}

Weapon::~Weapon()
{

}