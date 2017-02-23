#include "SaveLoad.h"
#include "BuildingFactory.h"
#include "EnemyFactory.h"
#include <array>
#include <fstream>
#include <sstream>

SaveLoad* SaveLoad::sl_instance;

SaveLoad::SaveLoad() : blank(',')
{
}

SaveLoad::~SaveLoad()
{
}

void SaveLoad::Save(int saveno, std::string area, std::list<Building*>& buildingslist, std::vector<Enemy*>& enemyslist)
{
	char blanker = *(SaveLoad::getInstance()->getBlank());
	std::stringstream filename;
	filename << "Saves//" << saveno << "//" << area << ".txt";
	std::string address;
	filename >> address;
	std::ofstream saver(address, std::ofstream::out);
	for (auto &i : buildingslist)
	{
		std::string temp;
		std::stringstream saveline;
		saveline << "B" << i->getID() << blanker << (int)(i->getRenderer().getForward().x * 10) << blanker << (int)(i->getRenderer().getForward().y * 10) << blanker << (int)(i->getRenderer().getForward().z * 10) << blanker << i->getRenderer().getPosition().x << blanker << i->getRenderer().getPosition().y << blanker << i->getRenderer().getPosition().z << ";;";
		saveline >> temp;
		saver << temp << std::endl;
	}
	for (auto &i : enemyslist)
	{
		std::string temp;
		std::stringstream saveline;
		saveline << "E" << i->getID() << blanker << (int)(i->getRenderer().getForward().x * 10) << blanker << (int)(i->getRenderer().getForward().y * 10) << blanker << (int)(i->getRenderer().getForward().z * 10) << blanker << (int)i->getRenderer().getPosition().x << blanker << (int)i->getRenderer().getPosition().y << blanker << (int)i->getRenderer().getPosition().z << ";;";
		saveline >> temp;
		saver << temp << std::endl;
	}
	saver.close();
}

void SaveLoad::Load(int saveno, std::string area, std::list<Building*>& buildingslist, std::vector<Enemy*>& enemyslist)
{
	const char* blanker = SaveLoad::getInstance()->getBlank();
	std::stringstream filename;
	filename << "Saves//" << saveno << "//" << area << ".txt";
	std::string address;
	filename >> address;
	std::ifstream loader(address, std::ofstream::in);
	while (!loader.eof())
	{
		char temparray[256];
		char entitytype;
		std::vector<float> tempstorage;
		loader.getline(temparray, 256);
		sscanf_s(temparray, "%d", &entitytype);
		entitytype = temparray[0];
		for (int i = 1; temparray[i] != ';';)
		{
			int temp;
			sscanf_s(temparray + i,"%d", &temp);
			tempstorage.push_back(temp);
			std::string sizestring = std::to_string(temp);
			i += sizestring.size() + 1;
		}
		if (entitytype == 'B')
		{
			Vector3 forward = Vector3(tempstorage[1] / 10.f, tempstorage[2] / 10.f, tempstorage[3] / 10.f);
			Vector3 position = Vector3(tempstorage[4], tempstorage[5], tempstorage[6]);
			Building* temp = BuildingFactory::getBuildingFactory()->generateBuilding(tempstorage[0], position);
			temp->getRenderer().setPosition(position);
			temp->getRenderer().setForward(forward);
			temp->getAABB(0)->setMinMax(position);
			buildingslist.push_back(temp);
		}
		else if (entitytype == 'E')
		{
			Vector3 forward = Vector3(tempstorage[1] / 10.f, tempstorage[2] / 10.f, tempstorage[3] / 10.f);
			Vector3 position = Vector3(tempstorage[4], tempstorage[5], tempstorage[6]);
			Enemy* temp = EnemyFactory::getEnemyFactory()->generateEnemy(tempstorage[0]);
			temp->getRenderer().setPosition(position);
			temp->getRenderer().setForward(forward);
			enemyslist.push_back(temp);
		}
	}
	loader.close();
}