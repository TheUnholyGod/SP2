#include "InventoryWarehouse.h"

InventoryWarehouse::InventoryWarehouse() : Building("InventoryWarehouse", 103, 100, NORMAL, true) {} // Change the ID
InventoryWarehouse::~InventoryWarehouse(){}
int InventoryWarehouse::get_Health(){ return health_; }