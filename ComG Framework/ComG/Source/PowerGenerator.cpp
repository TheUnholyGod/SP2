#include "PowerGenerator.h"

PowerGenerator::PowerGenerator() : Building("PowerGenerator", 000, 100, DEFENCE, false) {} // Change the ID
PowerGenerator::~PowerGenerator(){}
int PowerGenerator::get_Health(){ return health_; }