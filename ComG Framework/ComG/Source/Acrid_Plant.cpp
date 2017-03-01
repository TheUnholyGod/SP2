#include "Acrid_Plant.h"
#include "Randomizer.h"

std::vector<Projectile*>Acrid_Plant::acidProjectile;

Acrid_Plant::Acrid_Plant() : Enemy(7, "OBJ//AcidPlant.obj", "Image//AcidPlant_Texture.tga", "AcridPlant",  BOSS, "Base", 150, 15, 20)
{
	float randX = 250 - Randomizer::generate_range(1, 500) + Player::getplayer()->getRenderer().getPosition().x;
	float randZ = 250 - Randomizer::generate_range(1, 500) + Player::getplayer()->getRenderer().getPosition().z;
	gameobjrenderer_->setPosition(Vector3(randX, 0, randZ));
	gameobjrenderer_->setScaling(2);
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
	shootStart = std::clock();
}

void Acrid_Plant::Update(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy)
{
	elapsed = (std::clock() - shootStart) / (int)CLOCKS_PER_SEC;
	GameObject::getRenderer().setForward(GameObject::getRenderer().getPosition() - Player::getplayer()->getRenderer().getPosition());
	if (elapsed > 1)
	{
		if ((GameObject::getRenderer().getPosition().x - Player::getplayer()->getRenderer().getPosition().x) < 50 &&
			((GameObject::getRenderer().getPosition().y - Player::getplayer()->getRenderer().getPosition().y) < 50) &&
			((GameObject::getRenderer().getPosition().z - Player::getplayer()->getRenderer().getPosition().z) < 50))
		{
			shootStart = std::clock();
			Projectile* temp = dynamic_cast<Projectile*>(ItemFactory::getItemFactory()->generateItem(999));
			//Vector3 pos = (this->getRenderer().getPosition().x + 2.f, 0, this->getRenderer().getPosition().z+2.f);
			temp->Projectile::FireAcidProjectile(GameObject::getRenderer().getPosition(), -GameObject::getRenderer().getForward().Normalize());
			temp->Projectile::setProjectilespeed(10);
			//std::cout << GameObject::getRenderer().getPosition() << "SHOTS FIRED!!" << Player::getplayer()->getRenderer().getPosition() << std::endl;
			acidProjectile.push_back(temp);
		}
	}

	if (acidProjectile.size())
	{
		std::vector<int> pos;
		int counter = 0;
		for (auto &i : acidProjectile)
		{
			i->update(dt, Buildings, Enemy);
			if (i->toDelete())
			{
				pos.push_back(counter);
			}
			counter++;
		}
		if (pos.size())
		{
			int deleted = 0;
			for (auto i : pos)
			{
				Projectile* temp = *(acidProjectile.begin() + (i - deleted));
				acidProjectile.erase(acidProjectile.begin() + (i - deleted));
				deleted++;
				delete temp;
				temp = nullptr;
			}
		}
	}


	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
}

Acrid_Plant::~Acrid_Plant()
{
}