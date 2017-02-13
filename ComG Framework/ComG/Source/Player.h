#ifndef _PLAYER_H
#define _PLAYER_H

#include "GameObject.h"
#include <string>
#include "Vector3.h"

class Player : public GameObject
{
private:
	Player(int);
	static Player* player;
	

public:
	static Player* getplayer(int);
	const int gethealth();
	const int gethunger();
	const int getattack();
	//void setposition(const Vector3& pos);
	//const Vector3 getposition();
	void receivedamage();
	bool isDead();
	~Player();

protected:
	//Vector3 position_;
	float health_;
	float hunger_;
};

#endif