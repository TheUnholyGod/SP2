#ifndef _SAVELOAD_H
#define _SAVELOAD_H

#include <array>
#include <fstream>
#include <sstream>
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
	static void Save(int, std::string, std::list<Building*>&, std::vector<Enemy*>&);
	static bool Load(int, std::string, std::list<Building*>&, std::vector<Enemy*>&);
	static bool is_empty(int);
	static void NewGame(int);
	static void fuckthis(int);
	char* getBlank() { return &blank; }
	~SaveLoad();
};

#endif