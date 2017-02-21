#ifndef _PLAYER_H
#define _PLAYER_H

#include "GameObject.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Collision.h"
#include "Building.h"
<<<<<<< HEAD
#include "Item.h"
=======
#include "Enemy.h"
>>>>>>> 5f6cb77a594889dde0f6e7b845a621cdb74db793
#include <string>
#include <vector>

class Player : public GameObject
{
private:
	Player();
	static Player* player;
	Weapon* playerweapon_;

public:
	static Player* getplayer();
	const int gethealth();
	const int gethunger();
	const int getattack();
	void receivedamage();
	bool isDead();
<<<<<<< HEAD
	void Update(Vector3, Vector3, double,std::list<Building*>, std::vector<Item*>);
=======
	void Update(Vector3, Vector3, double, std::list<Building*>, std::list<Enemy*> enemies);
>>>>>>> 5f6cb77a594889dde0f6e7b845a621cdb74db793
	Weapon* getWeapon() { return playerweapon_; }
	void setWeapon(int);
	AABB* getAABB();
	
	~Player();

protected:
	//Vector3 position_;
	float health_;
	float hunger_;
	float movement_speed_;
};

#endif