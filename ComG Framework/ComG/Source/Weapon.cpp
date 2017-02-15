#include "Weapon.h"

Weapon::Weapon(int id, std::string name, std::string source, WEAPONTYPE type, float atk, float dura) : Item(id,name,source), kType_(type), kattack_(atk), kdurability_(dura)
{

}

Weapon::~Weapon()
{

}