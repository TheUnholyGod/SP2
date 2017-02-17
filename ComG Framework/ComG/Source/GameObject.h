#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <string>
#include <vector>
#include "Vector3.h"
#include "Collision.h"
#include "Renderer.h"

class GameObject
{
protected:
	const int kID_;
	const std::string source_location_;
	const std::string texture_location_;
	Renderer* gameobjrenderer_;
	std::vector<Vector3> size;
	std::vector<AABB*> allAABB;
public:
	GameObject(int, std::string, std::string);
	~GameObject();
	const int getID() { return kID_; }
	std::string getSourceLocation()  { return source_location_; }
	std::string getTextureLocation()  { return texture_location_; }
	Renderer& getRenderer() { return *gameobjrenderer_; }
	AABB* getAABB(int no) { return allAABB[no]; }
};

#endif