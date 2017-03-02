#include "Player.h"
#include "Application.h"
#include "Compound_Bow.h"
#include "Collision.h"
#include "Item.h"
#include "Randomizer.h"

Player* Player::player;

Player::Player() : GameObject(0, "", "") , movement_speed_(50) , health_(100)
{
	gameobjrenderer_ = new Renderer(Vector3(0, 0, 0), Vector3(1, 0, 0));
	Inventory::getinventory();
	AABB* temp = new AABB(Vector3(5, 5, 5), gameobjrenderer_->getPosition());
	allAABB.push_back(temp);
	Interact = false;

	PTime = 0;
	Pstart = 0;
	dead = false;
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

void Player::receivedamage(int dmg)
{
	health_ -= dmg;
}

bool Player::isDead()
{
	if (health_ > 0)
		return false;
	else if (health_ <= 0)
	{
		health_ = 0;
		this->reset();
	}
	return true;
}

Player::~Player()
{

}

void  Player::setWeapon(int key)
{
	playerweapon_ = (Weapon*)ItemFactory::getItemFactory()->generateItem(key);
	playerweapon_->getRenderer().setForward(player->getRenderer().getForward());
}

bool Player::getInteract()
{
	return Interact;
}

void Player::Update(Vector3 camForward, Vector3 camRight, double dt,std::list<Building*> buildings,std::vector<Enemy*> enemies, std::vector<Item*> items, std::vector<Item*> Loots)
{
	bool move = false;
	bool move2 = false;
	PTime = std::clock();

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
			if (move)
			{
				std::cout << "Collision" << std::endl;
				break;
			}
		}
		for (auto &i : enemies)
		{
			move2 = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), -camRight);
			if (move2)
				break;
		}
		if (!move && !move2)
		{
			gameobjrenderer_->translate(-camRight, movement_speed_ * dt);
			playerweapon_->getRenderer().translate(-camRight, movement_speed_ * dt);
			playerweapon_->getRenderer().setPosition(gameobjrenderer_->getPosition() + ((0, 1, 0) * 12) + (camForward * 5) + (camRight));
		}
	}
	if (Application::IsKeyPressed('D'))
	{
		for (auto &i : buildings)
		{
			move = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), camRight);
			if (move)
			{
				std::cout << "Collision" << std::endl;
				break;
			}
		}
		for (auto &i : enemies)
		{
			move2 = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), camRight);
			if (move2)
				break;
		}
		if (!move && !move2)
		{
			gameobjrenderer_->translate(camRight, movement_speed_ * dt);
			playerweapon_->getRenderer().translate(camRight, movement_speed_ * dt);
			playerweapon_->getRenderer().setPosition(gameobjrenderer_->getPosition() + ((0, 1, 0) * 12) + (camForward * 5) + (camRight));
		}
	}
	if (Application::IsKeyPressed('S'))
	{
		for (auto &i : buildings)
		{
			move = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), -camForwardTemp);
			if (move)
			{
				std::cout << "Collision" << std::endl;
				break;
			}
		}
		for (auto &i : enemies)
		{
			move2 = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), -camForwardTemp);
			if (move2)
				break;
		}
		if (!move && !move2)
		{
			gameobjrenderer_->translate(-camForwardTemp, movement_speed_ * dt);
			playerweapon_->getRenderer().translate(-camForwardTemp, movement_speed_ * dt);
			playerweapon_->getRenderer().setPosition(gameobjrenderer_->getPosition() + ((0, 1, 0) * 12) + (camForward * 5) + (camRight));
		}
	}
	if (Application::IsKeyPressed('W'))
	{
		for (auto &i : buildings)
		{
			move = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), camForwardTemp);
			if (move)
			{
				std::cout << "Collision" << std::endl;
				break;
			}
		}
		for (auto &i : enemies)
		{
			move2 = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), camForwardTemp);
			if (move2)
				break;
		}
		if (!move && !move2)
		{
			gameobjrenderer_->translate(camForwardTemp, movement_speed_ * dt);
			playerweapon_->getRenderer().translate(camForwardTemp, movement_speed_ * dt);
			playerweapon_->getRenderer().setPosition(gameobjrenderer_->getPosition() + ((0, 1, 0) * 12) + (camForward * 5) + (camRight));
		}
	}
	if (Application::IsKeyPressed('Q'))
	{
		for (int i = 0; i < 99; i++)
		{
			Inventory::getinventory()->Additem(101);
			Inventory::getinventory()->Additem(102);
			Inventory::getinventory()->Additem(103);
			Inventory::getinventory()->Additem(104);
			Inventory::getinventory()->Additem(105);
			Inventory::getinventory()->Additem(106);
			Inventory::getinventory()->Additem(107);
			Inventory::getinventory()->Additem(108);
			Inventory::getinventory()->Additem(201);
			Inventory::getinventory()->Additem(202);
			Inventory::getinventory()->Additem(203);
			Inventory::getinventory()->Additem(204);
			Inventory::getinventory()->Additem(205);
			Inventory::getinventory()->Additem(206);
			Inventory::getinventory()->Additem(207);
			Inventory::getinventory()->Additem(208);
			Inventory::getinventory()->Additem(209);
			Inventory::getinventory()->Additem(210);
			Inventory::getinventory()->Additem(211);
		}
	}

	//Interaction
	bool checkI = false;
	std::vector <bool> a;

	for (auto &i : items)
	{
		checkI = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), camForwardTemp);
		a.push_back(checkI);
	}
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] == true)
		{
			Interact = true;
			break;
		}
		else
			Interact = false;
	}

	if (Interact == false) {
		for (auto &i : Loots)
		{
			checkI = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), camForwardTemp);
			a.push_back(checkI);
		}
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] == true)
			{
				Interact = true;
				break;
			}
			else
				Interact = false;
		}
	}

	if (Interact == false) {
		for (auto &i : buildings)
		{
			if (i->getID() == 110)
			{
				i->setinit();
				std::cout << "collecttime: " << i->getcollecttime() << std::endl;
				checkI = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), camForwardTemp);
				i->update(dt);
				if (checkI && i->getcollecttime() >= 60)
				{
					Interact = true;
				}
				else
				{
					Interact = false;
				}
			}
		}
	}

	if (Application::IsKeyPressed('E') && (PTime - Pstart > 180))
	{
		Pstart = std::clock();
		std::vector<int> pos;
		int counter = 0;
		int eraser = 0;
		for (auto &i : items)
		{
			bool pickup = false;
			pickup = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), camForwardTemp);
			if (pickup)
			{
				std::cout << "picked up" << std::endl;
				i->update();
				Item* temp = i;
				Inventory::getinventory()->Additem(temp->getID());
				//pos.push_back(counter);
				Inventory::getinventory()->Update(dt);
				delete i->getAABB(0);
			}
			//counter++;
		}
		for (auto &i : Loots)
		{
			bool pickup1 = false;
			pickup1 = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), camForwardTemp);
			if (pickup1 && !i->getpickedup())
			{
				std::cout << i->getID() <<"picked up" << std::endl;
				i->update();
				Inventory::getinventory()->Additem(i->getID());
				Inventory::getinventory()->Update(dt);
				delete i->getAABB(0);
			}
		}
		for (auto &i : buildings)
		{
			if (i->getID() == 110)
			{
				i->setstart();

				bool collect = false;
				collect = i->getAABB(0)->pointtoAABB(gameobjrenderer_->getPosition(), camForwardTemp);
				if (collect && i->getcollecttime() >= 60)
				{
					i->collected();
					int ID = Randomizer::generate_range(201, 205);
					Inventory::getinventory()->Additem(ID);
					std::cout << "Added" << std::endl;
				}
			}
		}
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
}

void Player::reset()
{
	gameobjrenderer_->setPosition(Vector3(0, 0, 0));
	gameobjrenderer_->setForward(Vector3(1, 0, 0));
	health_ = 100;
}