#ifndef INVENTORYWAREHOUSE_H
#define INVENTORYWAREHOUSE_H

#include "Building.h"
#include <string>

class InventoryWarehouse : public Building
{
protected:

	const std::string kName_;
	std::string source_location_;
	int health_;
	bool enter_;
public:
	InventoryWarehouse(Vector3 = (0, 0, 5));
	virtual ~InventoryWarehouse();

	int get_Health();
};

#endif