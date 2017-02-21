#include "Food.h"

Food::Food(int no, std::string name, std::string source_, std::string texture, FOODTYPE type, float nutrval, float shlv) :Item(no, name, source_, texture), TYPE(type), nutrition_(nutrval), shelf_life_(shlv)
{

}

Food::~Food()
{

}