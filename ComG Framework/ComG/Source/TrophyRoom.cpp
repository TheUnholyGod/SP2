#include "TrophyRoom.h"

TrophyRoom::TrophyRoom() : Building(102, "TrophyRoom", "", 100, NORMAL, true) {} // Change the ID
TrophyRoom::~TrophyRoom(){}
int TrophyRoom::get_Health(){ return health_; }