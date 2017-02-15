#include "TilledSoil.h"

TilledSoil::TilledSoil() : Building(301, "TilledSoil", "", 100, RESOURCE, false) {} // Change the ID
TilledSoil::~TilledSoil(){}
int TilledSoil::get_Health(){ return health_; }