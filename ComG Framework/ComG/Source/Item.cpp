#include "Item.h"

Item::Item(int no, std::string name) :GameObject(no,""), kname_(name) {}

Item::~Item() {}