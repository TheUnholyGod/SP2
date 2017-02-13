#ifndef _PLAYER_H
#define _PLAYER_H

class Player
{
private:
	Player();
	static Player* player;

public:
	static Player* getplayer();
	~Player();
};

#endif