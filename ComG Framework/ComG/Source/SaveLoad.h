#ifndef _SAVELOAD_H
#define _SAVELOAD_H

#include <list>
#include <string>
#include "Building.h"
#include "Enemy.h"

class SaveLoad
{
private:
	SaveLoad();
	static SaveLoad* sl_instance;
	char blank;
public:
	static SaveLoad* getInstance()
	{
		if (!sl_instance)
		{
			sl_instance = new SaveLoad();
		}
		return sl_instance;
	}
	static void Save(int, std::string, std::list<Building*>&, std::list<Enemy*>&);
	static void Load(int, std::string, std::list<Building*>&, std::list<Enemy*>&);
	char* getBlank() { return &blank; }
	~SaveLoad();
};

#endif