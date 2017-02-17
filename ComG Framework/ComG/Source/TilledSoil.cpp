#include "TilledSoil.h"

TilledSoil::TilledSoil() : Building(109, "TilledSoil", "OBJ//Barn.obj", "", 100, RESOURCE, false) {} // Change the ID
TilledSoil::~TilledSoil(){}
int TilledSoil::get_Health(){ return health_; }