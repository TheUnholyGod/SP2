#ifndef _PLAYER_H
#define _PLAYER_H

#include "GameObject.h"
#include "Renderer.h"
#include "Inventory.h"
#include "Weapon.h"
#include <string>

class Player : public GameObject
{
private:
	Player();
	static Player* player;
	Renderer* playerRender;
	Weapon* playerweapon_;

public:
	static Player* getplayer();
	const int gethealth();
	const int gethunger();
	const int getattack();
	Renderer getRenderer() { return *playerRender; }
	void receivedamage();
	bool isDead();
	void Update(Vector3, Vector3, double);
	Weapon* getWeapon() { return playerweapon_; }
	void setWeapon(int);
	
	~Player();

protected:
	//Vector3 position_;
	float health_;
	float hunger_;
};

#endif