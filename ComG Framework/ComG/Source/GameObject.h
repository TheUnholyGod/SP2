#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <string>
#include "Renderer.h"

class GameObject
{
protected:
	const int kID_;
	const std::string source_location_;
	Renderer* gameobjrenderer_;
public:
	GameObject(int, std::string);
	~GameObject();
	const int getID() { return kID_; }
	std::string getSourceLocation()  { return source_location_; }
	Renderer getRenderer() { return *gameobjrenderer_; }
};

#endif