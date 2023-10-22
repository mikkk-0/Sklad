#ifndef GLOBALS_H
#define GLOBALS_H
#include "storage.h"

Storage* st;
std::vector<Product*> products;
int CURRENT_DAY;
const int delay = rnd() % 3 + 3;
#endif // GLOBALS_H
