#ifndef INIT_H
#define INIT_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <new>
#include <sstream>
#include "mcigraph.hpp"

namespace init{
    std::vector<int> loadm(std::string, size_t size_m = 90000);
}// namespace init

#endif
