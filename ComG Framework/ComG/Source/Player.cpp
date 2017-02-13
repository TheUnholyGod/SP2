#include "Player.h"

Player* Player::player;

Player::Player(int no) : GameObject(no)
{

}

Player* Player::getplayer(int no) 
{
	if (!player) {
		player = new Player(no);
	}

	return player;
}

const int Player::gethealth()
{

}

const int Player::gethunger()
{

}

const int Player::getattack()
{

}

void Player::receivedamage()
{

}

bool Player::isDead()
{

}

Player::~Player()
{

}

