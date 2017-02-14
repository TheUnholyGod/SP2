#include "FastTravelRoom.h"

FastTravelRoom::FastTravelRoom() : Building("FastTravelRoom", 105, 100, NORMAL, true) {} // Change the ID
FastTravelRoom::~FastTravelRoom(){}
int FastTravelRoom::get_Health(){ return health_; }