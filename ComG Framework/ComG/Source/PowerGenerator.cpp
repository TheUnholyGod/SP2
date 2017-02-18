#include "PowerGenerator.h"

PowerGenerator::PowerGenerator() : Building(106, "PowerGenerator", "OBJ//Barn.obj", "", 100, DEFENCE, false) {} // Change the ID
PowerGenerator::~PowerGenerator(){}
int PowerGenerator::get_Health(){ return health_; }