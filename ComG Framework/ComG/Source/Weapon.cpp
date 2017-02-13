#include "Weapon.h"

Weapon::Weapon(std::string name, WEAPONTYPE type, float atk, float dura) : Item(name), kType_(type), kattack_(atk), kdurability_(dura)
{

}

Weapon::~Weapon()
{

}