#ifndef _PLAYER_H
#define _PLAYER_H

#include "GameObject.h"
#include "Renderer.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Collision.h"
#include "Building.h"
#include <string>

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
	void Update(Vector3, Vector3, double,std::list<Building*>);
	Weapon* getWeapon() { return playerweapon_; }
	void setWeapon(int);
	AABB* getAABB();
	
	~Player();

protected:
	//Vector3 position_;
	float health_;
	float hunger_;
};

#endif