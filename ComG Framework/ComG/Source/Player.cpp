#include "Player.h"
#include "Application.h"

Player* Player::player;

Player::Player() : GameObject(0)
{
	playerRender = new Renderer(Vector3(0,0,0),Vector3(1,0,0));
	Inventory::getinventory();
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

void Player::Update(Vector3 camForward, Vector3 camRight, double dt)
{
	if (playerRender->getForward() != camForward)
	{
		playerRender->setForward(camForward);
	}
	if (Application::IsKeyPressed('A'))
	{
		playerRender->translate(-camRight, 25 * dt);
	}
	else if (Application::IsKeyPressed('D'))
	{
		playerRender->translate(camRight, 25 * dt);
	}
	else if (Application::IsKeyPressed('S'))
	{
		playerRender->translate(-camForward, 25 * dt);
	}
	else if (Application::IsKeyPressed('W'))
	{
		playerRender->translate(camForward, 25 * dt);
	}
}