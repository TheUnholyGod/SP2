#include "Food.h"

Food::Food(std::string name, FOODTYPE type, float nutrval, float shlv) :Item(name), TYPE(type), nutrition_(nutrval), shelf_life_(shlv)
{

}

Food::~Food()
{

}