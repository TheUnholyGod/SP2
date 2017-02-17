#include "InventoryWarehouse.h"

InventoryWarehouse::InventoryWarehouse() : Building(103, "InventoryWarehouse", "OBJ//Barn.obj", 100, NORMAL, true) {} // Change the ID
InventoryWarehouse::~InventoryWarehouse(){}
int InventoryWarehouse::get_Health(){ return health_; }