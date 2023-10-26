#ifndef INCLUDES_H
#define INCLUDES_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
#include <exception>
#include "Classes.h"

static std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());
#endif // INCLUDES_H
