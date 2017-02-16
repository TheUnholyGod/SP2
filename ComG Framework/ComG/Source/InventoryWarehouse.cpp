#include "InventoryWarehouse.h"

InventoryWarehouse::InventoryWarehouse() : Building(103, "InventoryWarehouse", "", 100, NORMAL, true) {} // Change the ID
InventoryWarehouse::~InventoryWarehouse(){}
int InventoryWarehouse::get_Health(){ return health_; }