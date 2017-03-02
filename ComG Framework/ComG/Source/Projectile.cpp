#include "Projectile.h"
#include "Player.h"

Projectile::Projectile():Item(999,"","OBJ//Carrot.obj","Projectile"), proj_speed_(500), attack_dmg_(10), range_(1000)
{
	fired_ = false;
	deletepls_ = false;
	isAcid = false;
}

Projectile::~Projectile()
{

}

void Projectile::FireProjectile(Vector3 pos, Vector3 forward)
{
	fired_ = true;
	isAcid = false;
	defaultpos = gameobjrenderer_->getPosition();
	gameobjrenderer_->setPosition(pos);
	gameobjrenderer_->setForward(forward);
}
void Projectile::FireAcidProjectile(Vector3 pos, Vector3 forward)
{
	fired_ = true;
	isAcid = true;
	defaultpos = gameobjrenderer_->getPosition();
	gameobjrenderer_->setPosition(pos + Vector3(0, 1, 0));
	gameobjrenderer_->setForward(forward);
}

bool Projectile::hit(std::list<Building*>buildings, std::vector<Enemy*>enemies)
{
	bool hit = false;
	if (Player::getplayer()->getAABB(0)->pointtoAABB(this->gameobjrenderer_->getPosition(), this->gameobjrenderer_->getForward()) && isAcid)
	{
		Player::getplayer()->receivedamage(attack_dmg_);
		hit = true;
	}
	for (auto &i : enemies)
	{
		hit = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), gameobjrenderer_->getForward());
		if (hit)
		{
			if (i->getID() == 7)
			{
				if (!isAcid)
				{
					std::cout << i->getHealth() << std::endl;
					i->takeDamage(attack_dmg_);
					//break;
				}
			}
			else
			{
				std::cout << "other hit" << std::endl;
				i->takeDamage(attack_dmg_);
				//break;
			}
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
		if (isAcid)
			gameobjrenderer_->translate(Vector3(gameobjrenderer_->getForward().x, (Player::getplayer()->getRenderer().getPosition().y - gameobjrenderer_->getPosition().y), gameobjrenderer_->getForward().z), proj_speed_*dt);
		else
			gameobjrenderer_->translate(gameobjrenderer_->getForward(), proj_speed_*dt);
		if ((gameobjrenderer_->getPosition() - defaultpos).Length() > range_ || hit(buildings,enemies) || gameobjrenderer_->getPosition().y < 0)
		{
			//std::cout << Projectile::gameobjrenderer_->getPosition() << "Shots Hit!" << Player::getplayer()->getRenderer().getPosition() << std::endl;
			deletepls_ = true;
		}
	}

}