#include "Food.h"

Food::Food(std::string name, FOODTYPE type, float nutri, float life) :Item(name), TYPE(type), nutrition_(nutri), shelf_life_(life)
{
	
}

Food::~Food()
{

}