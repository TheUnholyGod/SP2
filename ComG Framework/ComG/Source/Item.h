#ifndef _ITEM_H
#define _ITEM_H

#include "GameObject.h"
#include <string>

class Item : public GameObject
{
protected:
	const std::string kname_;
	std::string source_location_;
public:
<<<<<<< HEAD
	Item(int,std::string,std::string);
=======
	Item(int,std::string, std::string);
>>>>>>> df0b89ed37dcdc725ae0ed602e193209e647493d
	virtual ~Item();
	const std::string getName() { return kname_; }
};

#endif