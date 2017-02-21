#include "Projectile.h"
#include "Player.h"

Projectile::Projectile():Item(999,"","OBJ//Carrot.obj","Projectile"), proj_speed_(100), attack_dmg_(100), range_(1000)
{
	fired_ = false;
	deletepls_ = false;
}

Projectile::~Projectile()
{

}

void Projectile::FireProjectile()
{
	fired_ = true;
	size.push_back(Vector3(10, 10, 10));
	defaultpos = gameobjrenderer_->getPosition();
	gameobjrenderer_->setPosition(Player::getplayer()->getWeapon()->getRenderer().getPosition());
	gameobjrenderer_->setForward(Player::getplayer()->getWeapon()->getRenderer().getForward());
}

bool Projectile::hit()
{

	return true;
}

void Projectile::update(double dt) 
{	
	if (!fired_)
	{
		gameobjrenderer_->setPosition(Player::getplayer()->getWeapon()->getRenderer().getPosition());
		gameobjrenderer_->setUp(Player::getplayer()->getWeapon()->getRenderer().getForward().Cross(Player::getplayer()->getWeapon()->getRenderer().getRight()).Normalized());
		gameobjrenderer_->setForward(Player::getplayer()->getWeapon()->getRenderer().getForward());
	}

	else
	{
		gameobjrenderer_->translate(gameobjrenderer_->getForward(), proj_speed_);
		if ((gameobjrenderer_->getPosition() - defaultpos).Length() > range_)
		{
			deletepls_ = true;
		}
	}
	
}

/*get player pos(weapon)
defaultpos in weapon pos
translate projectile
hit(AABB check)
delete projectile*/