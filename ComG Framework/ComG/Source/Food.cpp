#include "Food.h"

Food::Food(int no,std::string name, FOODTYPE type, float nutrval, float shlv) :Item(no,"",name), TYPE(type), nutrition_(nutrval), shelf_life_(shlv)
{

}

Food::~Food()
{

}