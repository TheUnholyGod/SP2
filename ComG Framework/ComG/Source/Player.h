#ifndef _PLAYER_H
#define _PLAYER_H

#include "GameObject.h"
#include "Renderer.h"
#include <string>

class Player : public GameObject
{
private:
	Player();
	static Player* player;
	Renderer* playerRender;

public:
	static Player* getplayer();
	const int gethealth();
	const int gethunger();
	const int getattack();
	Renderer getRenderer() { return *playerRender; }
	void receivedamage();
	bool isDead();
	void Update(Vector3, Vector3, double);
	~Player();

protected:
	//Vector3 position_;
	float health_;
	float hunger_;
};

#endif