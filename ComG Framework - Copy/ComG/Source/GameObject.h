#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

class GameObject
{
protected:
	const int kID_;
public:
	GameObject(int);
	~GameObject();
	const int getID() { return kID_; }
};

#endif