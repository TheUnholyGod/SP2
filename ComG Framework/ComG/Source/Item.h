#ifndef _ITEM_H
#define _ITEM_H

#include "GameObject.h"
#include <string>
#include <map>

class Item : public GameObject
{
protected:
	const std::string kname_;
	std::string source_location_;
	std::string texture_location_;
	bool pickedup;
	typedef std::map<int, int> itemRecipe;
	itemRecipe defRecipe;
public:
	Item(int, std::string, std::string, std::string);
	void update();
	bool getpickedup();
	virtual ~Item();
	const std::string getName() { return kname_; }
	virtual itemRecipe getRecipe() { return defRecipe; }
};

#endif