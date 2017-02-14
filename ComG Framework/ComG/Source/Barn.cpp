#include "Barn.h"

Barn::Barn() : Building("Barn", 101, 100, NORMAL, true) {} // Change the ID
Barn::~Barn(){}
int Barn::get_Health(){ return health_; }