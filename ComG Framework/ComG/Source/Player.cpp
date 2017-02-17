#include "Player.h"
#include "Application.h"
#include "Compound_Bow.h"

Player* Player::player;

Player::Player() : GameObject(0,"", "")
{
	playerRender = new Renderer(Vector3(0,10,0),Vector3(1,0,0));
	Inventory::getinventory();
	AABB* temp = new AABB(Vector3(5, 5, 5), playerRender->getPosition());
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

void  Player::setWeapon(int key)
{
	playerweapon_ = (Weapon*)ItemFactory::getItemFactory()->generateItem(key);
	playerweapon_->getRenderer().setForward(player->getRenderer().getForward());
}

void Player::Update(Vector3 camForward, Vector3 camRight, double dt)
{
	Vector3 camForwardTemp = camForward;
	camForwardTemp.y = 0;
	if (playerRender->getForward() != camForwardTemp)
	{
		playerRender->setForward(camForwardTemp);
		playerweapon_->getRenderer().setPosition(playerRender->getPosition() + ((0,1,0) * 20) + (camForward * 5) + (camRight));
		playerweapon_->getRenderer().setUp((camForward.Cross(camRight)).Normalized());
		playerweapon_->getRenderer().setForward(camForward);
	}
	if (Application::IsKeyPressed('A'))
	{

		playerRender->translate(-camRight, 25 * dt);
		playerweapon_->getRenderer().translate(-camRight, 25 * dt);
		playerweapon_->getRenderer().setPosition(playerRender->getPosition() + ((0, 1, 0) * 2) + (camForward * 5) + (camRight));
	}
	else if (Application::IsKeyPressed('D'))
	{
		playerRender->translate(camRight, 25 * dt);
		playerweapon_->getRenderer().translate(camRight, 25 * dt);
		playerweapon_->getRenderer().setPosition(playerRender->getPosition() + ((0, 1, 0) * 2) + (camForward * 5) + (camRight));
	}
	else if (Application::IsKeyPressed('S'))
	{
		playerRender->translate(-camForwardTemp, 25 * dt);
		playerweapon_->getRenderer().translate(-camForwardTemp, 25 * dt);
		playerweapon_->getRenderer().setPosition(playerRender->getPosition() + ((0, 1, 0) * 2) + (camForward * 5) + (camRight));
	}
	else if (Application::IsKeyPressed('W'))
	{
		playerRender->translate(camForwardTemp, 25 * dt);
		playerweapon_->getRenderer().translate(camForwardTemp, 25 * dt);
		playerweapon_->getRenderer().setPosition(playerRender->getPosition() + ((0, 1, 0) * 2) + (camForward * 5) + (camRight));
	}
}

AABB* Player::getAABB()
{
	return allAABB[0];
}