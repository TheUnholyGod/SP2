#ifndef _PLAYER_H
#define _PLAYER_H

#include "GameObject.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Collision.h"
#include "Building.h"
#include "Item.h"
#include "Enemy.h"
#include <string>
#include <vector>

class Player : public GameObject
{
private:
	Player();
	static Player* player;
	Weapon* playerweapon_;
	float health_;
	float hunger_;
	float movement_speed_;
	bool Interact;

	std::clock_t Pstart;
	float PTime;

	//mines
	std::clock_t collecttime;
	float Timer;
	bool start;

public:
	static Player* getplayer();
	const int gethealth();
	const int gethunger();
	const int getattack();
	void receivedamage(int dmg);
	bool isDead();
	void Update(Vector3, Vector3, double, std::list<Building*>, std::vector<Enemy*> enemies, std::vector<Item*> Items, std::vector<Item*> Loots);
	Weapon* getWeapon() { return playerweapon_; }
	void setWeapon(int);
	bool getInteract();
	
	~Player();
};

#endif