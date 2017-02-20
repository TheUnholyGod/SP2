#include "Projectile.h"

Projectile::Projectile():Item(999,"","OBJ//Carrot.obj","Projectile"), proj_speed_(100), attack_dmg_(100), range_(100)
{
	fired = false;
}

Projectile::~Projectile()
{

}

void Projectile::FireProjectile(Vector3 forward, double dt)
{
	gameobjrenderer_->setForward(forward);
}

bool Projectile::hit()
{
	//AABB
//	if (allAABB[0]->pointtoAABB(getRenderer().getPosition()))
//		return true;
//	else
//		return false;
	return true;
}

void Projectile::update(Vector3 pos, Vector3 forward, double dt) 
{
	fired = true;
	
	if(!fired)
	defaultposition_ = pos;
	
	else //(fired)
	{
		FireProjectile(forward, dt);
		gameobjrenderer_->translate(gameobjrenderer_->getForward(), proj_speed_);

		/*if (hit() == true)
		{

		}*/

		if (position_.x > range_ || position_.y > range_ || position_.z > range_)
		{
			position_ = defaultposition_;
			fired = false;
		}
	}
	std::cout << "position_: " << position_ << std::endl;
}

/*get player pos(weapon)
defaultpos in weapon pos
translate projectile
hit(AABB check)
delete projectile*/