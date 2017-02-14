#include "OreMines.h"

OreMines::OreMines() : Building("OreMines", 302, 100, RESOURCE, false) {} // Change the ID
OreMines::~OreMines(){}
int OreMines::get_Health(){ return health_; }