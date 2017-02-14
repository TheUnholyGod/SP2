#include "PowerGenerator.h"

PowerGenerator::PowerGenerator() : Building("PowerGenerator", 201, 100, DEFENCE, false) {} // Change the ID
PowerGenerator::~PowerGenerator(){}
int PowerGenerator::get_Health(){ return health_; }