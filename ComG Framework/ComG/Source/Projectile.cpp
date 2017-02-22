#include "Projectile.h"
#include "Player.h"

Projectile::Projectile():Item(999,"","OBJ//Carrot.obj","Projectile"), proj_speed_(500), attack_dmg_(100), range_(1000)
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
	defaultpos = gameobjrenderer_->getPosition();
	gameobjrenderer_->setPosition(Player::getplayer()->getWeapon()->getRenderer().getPosition());
	gameobjrenderer_->setForward(Player::getplayer()->getRenderer().getForward());
}

bool Projectile::hit(std::list<Building*>buildings, std::vector<Enemy*>enemies)
{
	bool hit = false;
	for (auto &i : enemies)
	{
		hit = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), gameobjrenderer_->getForward());
		if (hit)
		{
			i->takeDamage(attack_dmg_);
			break;
		}
	}
	if (!hit)
	{
		for (auto &i : buildings)
		{
			hit = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), gameobjrenderer_->getForward());
			if (hit)
				break;
		}
	}
	return hit;
}

void Projectile::update(double dt, std::list<Building*>buildings, std::vector<Enemy*>enemies)
{
	if (!fired_)
	{
		gameobjrenderer_->setPosition(Player::getplayer()->getWeapon()->getRenderer().getPosition());
		gameobjrenderer_->setUp(Player::getplayer()->getWeapon()->getRenderer().getForward().Cross(Player::getplayer()->getWeapon()->getRenderer().getRight()).Normalized());
		gameobjrenderer_->setForward(Player::getplayer()->getWeapon()->getRenderer().getForward());
	}

	else
	{
		gameobjrenderer_->translate(gameobjrenderer_->getForward(), proj_speed_*dt);
		if ((gameobjrenderer_->getPosition() - defaultpos).Length() > range_ || hit(buildings,enemies) || gameobjrenderer_->getPosition().y < 0)
		{
			deletepls_ = true;
		}
	}

}