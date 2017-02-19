#include "SaveLoad.h"
#include <fstream>
#include <sstream>

SaveLoad* SaveLoad::sl_instance;

SaveLoad::SaveLoad() : blank('-')
{
}

SaveLoad::~SaveLoad()
{
}

void SaveLoad::Save(int saveno, std::string area, std::list<Building*>& buildingslist, std::list<Enemy*>& enemyslist)
{
	std::stringstream filename;
	filename << "Saves//" << saveno << "//" << area;
	std::string address;
	filename >> address;
	std::ofstream saver(address, std::ofstream::out);
	for (auto &i : buildingslist)
	{
		std::string temp;
		std::stringstream saveline;
		saveline << "B-" << i->getID() << "-" << i->getRenderer().getPosition().x << "-" << i->getRenderer().getPosition().y << "-" << i->getRenderer().getPosition().z;
		saveline >> temp;
		saver << temp << "\n";
	}
	for (auto &i : enemyslist)
	{
		std::string temp;
		std::stringstream saveline;
		saveline << "E-" << i->getID() << "-" << i->getRenderer().getPosition().x << "-" << i->getRenderer().getPosition().y << "-" << i->getRenderer().getPosition().z;
		saveline >> temp;
		saver << temp << "\n";
	}
	saver.close();
}

void SaveLoad::Load(int saveno, std::string area, std::list<Building*>& buildingslist, std::list<Enemy*>& enemyslist)
{
	const char* blanker = SaveLoad::getInstance()->getBlank();
	std::stringstream filename;
	filename << "Saves//" << saveno << "//" << area;
	std::string address;
	filename >> address;
	std::ifstream loader(address, std::ofstream::in);
	while (!loader.eof())
	{
		std::string temp;
		scanf_s(blanker);
	}
	loader.close();
}