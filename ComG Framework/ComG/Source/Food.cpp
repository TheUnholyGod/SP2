#include "Food.h"

<<<<<<< HEAD
Food::Food(int no,std::string name, FOODTYPE type, float nutrval, float shlv) :Item(no,"",name), TYPE(type), nutrition_(nutrval), shelf_life_(shlv)
=======
Food::Food(int no,std::string name, std::string source, FOODTYPE type, float nutrval, float shlv) :Item(no,name,source), TYPE(type), nutrition_(nutrval), shelf_life_(shlv)
>>>>>>> df0b89ed37dcdc725ae0ed602e193209e647493d
{

}

Food::~Food()
{

}