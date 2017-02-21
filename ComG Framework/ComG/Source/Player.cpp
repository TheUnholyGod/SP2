#include "Player.h"
#include "Application.h"
#include "Compound_Bow.h"
#include "Collision.h"
#include "Item.h"

Player* Player::player;

Player::Player() : GameObject(0,"", "")
{
	gameobjrenderer_ = new Renderer(Vector3(0,0,0),Vector3(1,0,0));
	Inventory::getinventory();
	AABB* temp = new AABB(Vector3(5, 5, 5), gameobjrenderer_->getPosition());
	allAABB.push_back(temp);
}

Player* Player::getplayer() 
{
	if (!player) {
		player = new Player;
	}

	return player;
}

const int Player::gethealth()
{
	return health_;
}

const int Player::gethunger()
{
	return 0;
}

const int Player::getattack()
{
	return 0;
}

void Player::receivedamage()
{

}

bool Player::isDead()
{
	return 0;
}

Player::~Player()
{

}

void  Player::setWeapon(int key)
{
	playerweapon_ = (Weapon*)ItemFactory::getItemFactory()->generateItem(key);
	playerweapon_->getRenderer().setForward(player->getRenderer().getForward());
}

void Player::Update(Vector3 camForward, Vector3 camRight, double dt, std::list<Building*> buildings, std::vector<Item*> items)
{
	bool move = false;
	bool pickup = false;

	Vector3 camForwardTemp = camForward;
	camForwardTemp.y = 0;
	if (gameobjrenderer_->getForward() != camForwardTemp)
	{
		gameobjrenderer_->setForward(camForwardTemp);
		playerweapon_->getRenderer().setPosition(gameobjrenderer_->getPosition() + ((0,1,0) * 12) + (camForward * 5) + (camRight));
		playerweapon_->getRenderer().setUp((camForward.Cross(camRight)).Normalized());
		playerweapon_->getRenderer().setForward(camForward);
	}
	if (Application::IsKeyPressed('A'))
	{
		for (auto &i : buildings)
		{
			move = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), -camRight);
		}
		if (!move)
		{
			gameobjrenderer_->translate(-camRight, 25 * dt);
			playerweapon_->getRenderer().translate(-camRight, 25 * dt);
			playerweapon_->getRenderer().setPosition(gameobjrenderer_->getPosition() + ((0, 1, 0) * 12) + (camForward * 5) + (camRight));
		}
	}
	if (Application::IsKeyPressed('D'))
	{
		for (auto &i : buildings)
		{
			move = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), camRight);
		}
		if (!move)
		{
			gameobjrenderer_->translate(camRight, 25 * dt);
			playerweapon_->getRenderer().translate(camRight, 25 * dt);
			playerweapon_->getRenderer().setPosition(gameobjrenderer_->getPosition() + ((0, 1, 0) * 12) + (camForward * 5) + (camRight));
		}
	}
	if (Application::IsKeyPressed('S'))
	{
		for (auto &i : buildings)
		{
			move = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), -camForwardTemp);
		}
		if (!move)
		{
			gameobjrenderer_->translate(-camForwardTemp, 25 * dt);
			playerweapon_->getRenderer().translate(-camForwardTemp, 25 * dt);
			playerweapon_->getRenderer().setPosition(gameobjrenderer_->getPosition() + ((0, 1, 0) * 12) + (camForward * 5) + (camRight));
		}
	}
	if (Application::IsKeyPressed('W'))
	{
		for (auto &i : buildings)
		{
			move = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), camForwardTemp);
		}
		if (!move)
		{
			gameobjrenderer_->translate(camForwardTemp, 25 * dt);
			playerweapon_->getRenderer().translate(camForwardTemp, 25 * dt);
			playerweapon_->getRenderer().setPosition(gameobjrenderer_->getPosition() + ((0, 1, 0) * 12) + (camForward * 5) + (camRight));
		}
	}
	if (Application::IsKeyPressed('E'))
	{
		std::vector<int> pos;
		int counter = 0;
		int eraser = 0;
		for (auto &i : items)
		{
			pickup = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), camForwardTemp);
			if (pickup)
			{
				std::cout << "picked up" << std::endl;
				Item* temp = i;
				Inventory::getinventory()->Additem(temp->getID());
				pos.push_back(counter);
			}
			counter++;
		}
		for (auto &i : pos)
		{
			items.erase(items.begin() + i - eraser);
			eraser++;
		}
		
	}
}

AABB* Player::getAABB()
{
	return allAABB[0];
}