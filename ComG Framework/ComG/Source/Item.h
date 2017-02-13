#ifndef _ITEM_H
#define _ITEM_H

#include "C:\Users\TheUnholyGod\Documents\School\Year 1 Semester 2\Studio Project 2\SP2\ComG Framework\ComG\GameObject.h"
#include <string>

class Item : public GameObject
{
protected:
	const std::string kname_;
public:
	Item(int,std::string);
	~Item();
};

#endif