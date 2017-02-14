#include "TrophyRoom.h"

TrophyRoom::TrophyRoom() : Building("TrophyRoom", 000, 100, NORMAL, true) {} // Change the ID
TrophyRoom::~TrophyRoom(){}
int TrophyRoom::get_Health(){ return health_; }