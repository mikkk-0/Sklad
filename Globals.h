#ifndef GLOBALS_H
#define GLOBALS_H
#include "storage.h"
namespace global {
    static Storage* st;
    static std::vector<Product*>* products;
    static int CURRENT_DAY;
    static const int delay = rnd() % 3 + 3;
}
#endif // GLOBALS_H
