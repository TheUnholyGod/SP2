#ifndef _TREE_H
#define _TREE_H

#include "Building.h"

class Tree :public Building
{
private:
	
public:
	Tree();
	Tree(Vector3 position);
	~Tree();
	void Update();
};

#endif