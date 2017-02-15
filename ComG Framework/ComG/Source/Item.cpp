#include "Item.h"

Item::Item(int no, std::string name, std::string source) :GameObject(no, source), kname_(name) {}

Item::~Item() {}