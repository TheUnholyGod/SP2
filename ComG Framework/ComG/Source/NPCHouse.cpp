#include "NPCHouse.h"

NPCHouse::NPCHouse() : Building("NPCHouse", 104, 100, NORMAL, true) {} // Change the ID
NPCHouse::~NPCHouse(){}
int NPCHouse::get_Health(){ return health_; }