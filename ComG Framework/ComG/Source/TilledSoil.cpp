#include "TilledSoil.h"

TilledSoil::TilledSoil() : Building("TilledSoil", 301, 100, RESOURCE, false) {} // Change the ID
TilledSoil::~TilledSoil(){}
int TilledSoil::get_Health(){ return health_; }