#include "FastTravelRoom.h"

FastTravelRoom::FastTravelRoom() : Building(105, "FastTravelRoom", "OBJ//Garage.obj", "", 100, NORMAL, true) {} // Change the ID
FastTravelRoom::~FastTravelRoom(){}
int FastTravelRoom::get_Health(){ return health_; }