#include "TrophyRoom.h"

TrophyRoom::TrophyRoom() : Building(102, "TrophyRoom", "OBJ//Barn.obj", "", 100, NORMAL, true) {} // Change the ID
TrophyRoom::~TrophyRoom(){}
int TrophyRoom::get_Health(){ return health_; }