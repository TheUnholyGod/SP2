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
	gameobjrenderer_->setForward(Player::getplayer()->getWeapon()->getRenderer().getForward());
}

bool Projectile::hit(std::list<Building*>buildings, std::vector<Enemy*>enemies)
{
	bool hit = false;
	for (auto &i : enemies)
	{
		hit = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), gameobjrenderer_->getForward());
		if (hit)
		{
			std::cout << "HIT MOFO!!" << std::endl;
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
				std::cout << "HIT NOT MOFO!!" << std::endl;
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
		if (gameobjrenderer_->getForward().y < 0)
		{
			gameobjrenderer_->translate((0, 1, 0), gameobjrenderer_->getForward().y);
		}
	}

	else
	{
		gameobjrenderer_->translate(gameobjrenderer_->getForward(), proj_speed_*dt);
		if ((gameobjrenderer_->getPosition() - defaultpos).Length() > range_ || hit(buildings,enemies))
		{
			deletepls_ = true;
		}
	}

}